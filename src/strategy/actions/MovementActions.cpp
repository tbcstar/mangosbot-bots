/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "MovementActions.h"
#include "MovementGenerator.h"
#include "TargetedMovementGenerator.h"
#include "../Event.h"
#include "../values/LastMovementValue.h"
#include "../values/PositionValue.h"
#include "../values/Stances.h"
#include "../../FleeManager.h"
#include "../../LootObjectStack.h"
#include "../../Playerbot.h"
#include "../../ServerFacade.h"

MovementAction::MovementAction(PlayerbotAI* botAI, std::string const& name) : Action(botAI, name)
{
    bot = botAI->GetBot();
}

bool MovementAction::MoveNear(uint32 mapId, float x, float y, float z, float distance)
{
    float angle = GetFollowAngle();
    return MoveTo(mapId, x + cos(angle) * distance, y + sin(angle) * distance, z);
}

bool MovementAction::MoveNear(WorldObject* target, float distance)
{
    if (!target)
        return false;

    distance += target->GetCombatReach();

    float x = target->GetPositionX();
    float y = target->GetPositionY();
    float z = target->GetPositionZ();
    float followAngle = GetFollowAngle();

    for (float angle = followAngle; angle <= followAngle + 2 * M_PI; angle += M_PI / 4)
    {
        float x = target->GetPositionX() + cos(angle) * distance;
        float y = target->GetPositionY() + sin(angle) * distance;
        float z = target->GetPositionZ();

        if (!bot->IsWithinLOS(x, y, z))
            continue;

        bool moved = MoveTo(target->GetMapId(), x, y, z);
        if (moved)
            return true;
    }

    botAI->TellError("All paths not in LOS");
    return false;
}

bool MovementAction::MoveTo(uint32 mapId, float x, float y, float z, bool idle)
{
    UpdateMovementState();

    bool generatePath = !bot->IsFlying() && !bot->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING) && !bot->IsInWater() && !bot->IsUnderWater();
    if (generatePath)
    {
        z += CONTACT_DISTANCE;
        bot->UpdateAllowedPositionZ(x, y, z);
    }

    if (!IsMovingAllowed(mapId, x, y, z))
    {
        botAI->TellError("I am stuck");
        return false;
    }

    float distance = sServerFacade->GetDistance2d(bot, x, y);
    if (sServerFacade->IsDistanceGreaterThan(distance, sPlayerbotAIConfig->targetPosRecalcDistance))
    {
        WaitForReach(distance);

        bot->HandleEmoteCommand(0);
        if (bot->IsSitState())
            bot->SetStandState(UNIT_STAND_STATE_STAND);

        if (bot->IsNonMeleeSpellCast(true))
        {
            bot->CastStop();
            botAI->InterruptSpell();
        }

        bot->GetMotionMaster()->MovePoint(mapId, x, y, z, generatePath);

        AI_VALUE(LastMovement&, "last movement").Set(x, y, z, bot->GetOrientation());
        if (!idle)
            ClearIdleState();

        return true;
    }

    return false;
}

bool MovementAction::MoveTo(Unit* target, float distance)
{
    if (!IsMovingAllowed(target))
    {
        botAI->TellError("Seems I am stuck");
        return false;
    }

    float bx = bot->GetPositionX(), by = bot->GetPositionY(), bz = bot->GetPositionZ();
    float tx = target->GetPositionX(), ty = target->GetPositionY(), tz = target->GetPositionZ();

    if (bot->IsHostileTo(target))
    {
        Stance* stance = AI_VALUE(Stance*, "stance");

        WorldLocation const& loc = stance->GetLocation();
        if (Formation::IsNullLocation(loc) || loc.GetMapId() == -1)
        {
            botAI->TellError("Nowhere to move");
            return false;
        }

        tx = loc.GetPositionX();
        ty = loc.GetPositionY();
        tz = loc.GetPositionZ();
    }

    float distanceToTarget = sServerFacade->GetDistance2d(bot, tx, ty);
    if (sServerFacade->IsDistanceGreaterThan(distanceToTarget, sPlayerbotAIConfig->targetPosRecalcDistance))
    {
        float angle = bot->GetAngle(tx, ty);
        float needToGo = distanceToTarget - distance;

        float maxDistance = botAI->GetRange("spell");
        if (needToGo > 0 && needToGo > maxDistance)
            needToGo = maxDistance;
        else if (needToGo < 0 && needToGo < -maxDistance)
            needToGo = -maxDistance;

        float dx = cos(angle) * needToGo + bx;
        float dy = sin(angle) * needToGo + by;
        float dz = bz + (tz - bz) * needToGo / distanceToTarget;

        return MoveTo(target->GetMapId(), dx, dy, dz);
    }

    return true;
}

float MovementAction::GetFollowAngle()
{
    Player* master = GetMaster();
    Group* group = master ? master->GetGroup() : bot->GetGroup();
    if (!group)
        return 0.0f;

    uint32 index = 1;
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        if (ref->GetSource() == master)
            continue;

        if (ref->GetSource() == bot)
            return 2 * M_PI / (group->GetMembersCount() -1) * index;

        index++;
    }

    return 0;
}

bool MovementAction::IsMovingAllowed(Unit* target)
{
    if (!target)
        return false;

    if (bot->GetMapId() != target->GetMapId())
        return false;

    float distance = bot->GetDistance(target);
    if (distance > sPlayerbotAIConfig->reactDistance)
        return false;

    return IsMovingAllowed();
}

bool MovementAction::IsMovingAllowed(uint32 mapId, float x, float y, float z)
{
    float distance = bot->GetDistance(x, y, z);
    if (distance > sPlayerbotAIConfig->reactDistance)
        return false;

    return IsMovingAllowed();
}

bool MovementAction::IsMovingAllowed()
{
    if (bot->isFrozen() || bot->IsPolymorphed() || (bot->isDead() && !bot->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST)) || bot->IsBeingTeleported() ||
        bot->isInRoots() || bot->HasAuraType(SPELL_AURA_MOD_CONFUSE) || bot->IsCharmed() || bot->HasAuraType(SPELL_AURA_MOD_STUN) || bot->IsFlying())
        return false;

    return bot->GetMotionMaster()->GetCurrentMovementGeneratorType() != FLIGHT_MOTION_TYPE;
}

bool MovementAction::Follow(Unit* target, float distance)
{
    return Follow(target, distance, GetFollowAngle());
}

void MovementAction::UpdateMovementState()
{
    if (bot->IsInWater() || bot->IsUnderWater())
    {
        bot->m_movementInfo.AddMovementFlag(MOVEMENTFLAG_SWIMMING);
        bot->UpdateSpeed(MOVE_SWIM, true);
    }
    else
    {
        bot->m_movementInfo.RemoveMovementFlag(MOVEMENTFLAG_SWIMMING);
        bot->UpdateSpeed(MOVE_SWIM, true);
    }
}

bool MovementAction::Follow(Unit* target, float distance, float angle)
{
    UpdateMovementState();

    if (!target)
        return false;

    if (sServerFacade->IsDistanceLessOrEqualThan(sServerFacade->GetDistance2d(bot, target->GetPositionX(), target->GetPositionY()), sPlayerbotAIConfig->sightDistance) &&
            abs(bot->GetPositionZ() - target->GetPositionZ()) >= sPlayerbotAIConfig->spellDistance)
    {
        bot->StopMoving();

        float x = bot->GetPositionX();
        float y = bot->GetPositionY();
        float z = target->GetPositionZ();
        if (target->GetMapId() && bot->GetMapId() != target->GetMapId())
        {
            bot->TeleportTo(target->GetMapId(), x, y, z, bot->GetOrientation());
        }
        else
        {
            bot->Relocate(x, y, z, bot->GetOrientation());
        }

        AI_VALUE(LastMovement&, "last movement").Set(target);
        ClearIdleState();
        return true;
    }

    if (!IsMovingAllowed(target))
    {
        botAI->TellError("I am stuck while following");
        return false;
    }

    if (target->IsFriendlyTo(bot) && bot->IsMounted() && AI_VALUE(GuidVector, "all targets").empty())
        distance += angle;

    if (sServerFacade->IsDistanceLessOrEqualThan(sServerFacade->GetDistance2d(bot, target), sPlayerbotAIConfig->followDistance))
    {
        botAI->TellError("No need to follow");
        return false;
    }

    bot->HandleEmoteCommand(0);

    if (bot->IsSitState())
        bot->SetStandState(UNIT_STAND_STATE_STAND);

    if (bot->IsNonMeleeSpellCast(true))
    {
        bot->CastStop();
        botAI->InterruptSpell();
    }

    if (bot->isMoving())
        return false;

    AI_VALUE(LastMovement&, "last movement").Set(target);
    ClearIdleState();

    if (bot->GetMotionMaster()->GetCurrentMovementGeneratorType() == FOLLOW_MOTION_TYPE)
    {
        Unit *currentTarget = sServerFacade->GetChaseTarget(bot);
        if (currentTarget && currentTarget->GetGUID() == target->GetGUID()) return false;
    }

    bot->GetMotionMaster()->MoveFollow(target, distance, angle);
    return true;
}

void MovementAction::WaitForReach(float distance)
{
    float delay = 1000.0f * distance / bot->GetSpeed(MOVE_RUN) + sPlayerbotAIConfig->reactDelay;
    if (delay > sPlayerbotAIConfig->maxWaitForMove)
        delay = sPlayerbotAIConfig->maxWaitForMove;

    Unit* target = *botAI->GetAiObjectContext()->GetValue<Unit*>("current target");
    Unit* player = *botAI->GetAiObjectContext()->GetValue<Unit*>("enemy player target");
    if ((player || target) && delay > sPlayerbotAIConfig->globalCoolDown)
        delay = sPlayerbotAIConfig->globalCoolDown;

    botAI->SetNextCheckDelay((uint32)delay);
}

bool MovementAction::Flee(Unit *target)
{
    Player* master = GetMaster();
    if (!target)
        target = master;

    if (!target)
        return false;

    if (!sPlayerbotAIConfig->fleeingEnabled)
        return false;

    if (!IsMovingAllowed())
    {
        botAI->TellError("I am stuck while fleeing");
        return false;
    }

    if (HostileReference* ref = target->getThreatManager().getCurrentVictim())
        if (ref->getTarget() == bot)
        {
            if (Group* group = bot->GetGroup())
            {
                for (GroupReference* gref = group->GetFirstMember(); gref; gref = gref->next())
                {
                    Player* player = gref->GetSource();
                    if (!player || player == bot)
                        continue;

                    if (botAI->IsTank(player))
                    {
                        float distanceToTank = sServerFacade->GetDistance2d(bot, player);
                        float distanceToTarget = sServerFacade->GetDistance2d(bot, target);
                        if (sServerFacade->IsDistanceGreaterThan(distanceToTank, distanceToTarget))
                        {
                            if (MoveTo(player, sPlayerbotAIConfig->followDistance))
                                return true;
                        }
                    }
                }
            }
        }

    FleeManager manager(bot, botAI->GetRange("flee"), bot->GetAngle(target) + M_PI);
    if (!manager.isUseful())
        return false;

    float rx, ry, rz;
    if (!manager.CalculateDestination(&rx, &ry, &rz))
    {
        botAI->TellError("Nowhere to flee");
        return false;
    }

    bool result = MoveTo(target->GetMapId(), rx, ry, rz);
    if (result && !urand(0, 25))
    {
        std::vector<uint32> sounds;
        sounds.push_back(304); // guard
        sounds.push_back(306); // flee
        botAI->PlaySound(sounds[urand(0, sounds.size() - 1)]);
    }

    return result;
}

void MovementAction::ClearIdleState()
{
    context->GetValue<time_t>("stay time")->Set(0);
    context->GetValue<ai::PositionMap&>("position")->Get()["random"].Reset();
}

bool FleeAction::Execute(Event event)
{
    return Flee(AI_VALUE(Unit*, "current target"));
}

bool FleeWithPetAction::Execute(Event event)
{
    if (Pet* pet = bot->GetPet())
    {
        if (CreatureAI* creatureAI = ((Creature*)pet)->AI())
        {
            pet->SetReactState(REACT_PASSIVE);
            pet->GetCharmInfo()->SetCommandState(COMMAND_FOLLOW);
            pet->AttackStop();
        }
    }

    return Flee(AI_VALUE(Unit*, "current target"));
}

bool RunAwayAction::Execute(Event event)
{
    return Flee(AI_VALUE(Unit*, "master target"));
}

bool MoveToLootAction::Execute(Event event)
{
    LootObject loot = AI_VALUE(LootObject, "loot target");
    if (!loot.IsLootPossible(bot) || AI_VALUE(bool, "possible ads"))
        return false;

    return MoveNear(loot.GetWorldObject(bot), sPlayerbotAIConfig->contactDistance);
}

bool MoveOutOfEnemyContactAction::Execute(Event event)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    return MoveTo(target, sPlayerbotAIConfig->contactDistance);
}

bool MoveOutOfEnemyContactAction::isUseful()
{
    return AI_VALUE2(bool, "inside target", "current target");
}

bool SetFacingTargetAction::Execute(Event event)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    if (bot->HasUnitState(UNIT_STATE_IN_FLIGHT) || bot->IsFlying())
        return true;

    sServerFacade->SetFacingTo(bot, target);
    botAI->SetNextCheckDelay(sPlayerbotAIConfig->globalCoolDown);
    return true;
}

bool SetFacingTargetAction::isUseful()
{
    return !AI_VALUE2(bool, "facing", "current target");
}

bool SetBehindTargetAction::Execute(Event event)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    float angle = GetFollowAngle() / 3 + target->GetOrientation() + M_PI;

    float distance = sPlayerbotAIConfig->contactDistance;
    float x = target->GetPositionX() + cos(angle) * distance;
    float y = target->GetPositionY() + sin(angle) * distance;
    float z = target->GetPositionZ();
    bot->UpdateGroundPositionZ(x, y, z);

    return MoveTo(bot->GetMapId(), x, y, z);
}

bool SetBehindTargetAction::isUseful()
{
    return !AI_VALUE2(bool, "behind", "current target");
}

bool MoveOutOfCollisionAction::Execute(Event event)
{
    float angle = M_PI * 2000 / frand(1.f, 1000.f);
    float distance = sPlayerbotAIConfig->followDistance;
    return MoveTo(bot->GetMapId(), bot->GetPositionX() + cos(angle) * distance, bot->GetPositionY() + sin(angle) * distance, bot->GetPositionZ());
}

bool MoveOutOfCollisionAction::isUseful()
{
    return AI_VALUE2(bool, "collision", "self target");
}

