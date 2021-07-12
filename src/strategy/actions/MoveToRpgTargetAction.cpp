/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "MoveToRpgTargetAction.h"
#include "ChatHelper.h"
#include "ChooseRpgTargetAction.h"
#include "Event.h"
#include "LastMovementValue.h"
#include "Playerbot.h"
#include "TravelMgr.h"

bool MoveToRpgTargetAction::Execute(Event event)
{
    Unit* unit = botAI->GetUnit(AI_VALUE(ObjectGuid, "rpg target"));
    GameObject* go = botAI->GetGameObject(AI_VALUE(ObjectGuid, "rpg target"));
    WorldObject* wo = nullptr;
    if (unit)
        wo = unit;
    else if (go)
        wo = go;
    else
        return false;

    if (botAI->HasStrategy("debug rpg", BOT_STATE_NON_COMBAT))
    {
        std::ostringstream out;
        out << "Heading to: ";
        out << chat->formatWorldobject(wo);
        botAI->TellMasterNoFacing(out);
    }

    if ((unit && unit->isMoving() && urand(1, 100) < 5) || !ChooseRpgTargetAction::isFollowValid(bot, wo))
    {
        context->GetValue<ObjectGuid>("rpg target")->Set(ObjectGuid::Empty);
        return false;
    }

    float x = wo->GetPositionX();
    float y = wo->GetPositionY();
    float z = wo->GetPositionZ();
    float mapId = wo->GetMapId();

    if (sPlayerbotAIConfig->randombotsWalkingRPG)
    {
        bot->m_movementInfo.AddMovementFlag(MOVEMENTFLAG_WALKING);
    }

    float angle = 0.f;
    if (bot->IsWithinLOS(x, y, z))
    {
        if (!unit || !unit->isMoving())
            angle = wo->GetAngle(bot) + (M_PI * irand(-25, 25) / 100.0); //Closest 45 degrees towards the target
        else
            angle = wo->GetOrientation() + (M_PI * irand(-25, 25) / 100.0); //45 degrees infront of target (leading it's movement)
    }
    else
        angle = 2 * M_PI * urand(0, 100) / 100.0; //A circle around the target.

    x += cos(angle) * sPlayerbotAIConfig->followDistance;
    y += sin(angle) * sPlayerbotAIConfig->followDistance;

    //WaitForReach(distance);

    if (bot->IsWithinLOS(x, y, z))
        return MoveNear(mapId, x, y, z, 0);
    else
        return MoveTo(mapId, x, y, z, false, false);
}

bool MoveToRpgTargetAction::isUseful()
{
    return context->GetValue<ObjectGuid>("rpg target")->Get()
        && !context->GetValue<TravelTarget*>("travel target")->Get()->isTraveling()
        && AI_VALUE2(float, "distance", "rpg target") > sPlayerbotAIConfig->followDistance
        && AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig->mediumHealth
        && (!AI_VALUE2(uint8, "mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig->mediumMana)
        && !bot->IsInCombat();
}
