/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "MoveToRpgTargetAction.h"
#include "../Event.h"
#include "../values/LastMovementValue.h"
#include "../../Playerbot.h"

bool MoveToRpgTargetAction::Execute(Event event)
{
    Unit* target = botAI->GetUnit(AI_VALUE(ObjectGuid, "rpg target"));
    if (!target)
        return false;

    float distance = AI_VALUE2(float, "distance", "rpg target");
    if (distance > 180.0f)
    {
        context->GetValue<ObjectGuid>("rpg target")->Set(ObjectGuid::Empty);
        return false;
    }

    float x = target->GetPositionX();
    float y = target->GetPositionY();
    float z = target->GetPositionZ();
    float mapId = target->GetMapId();

    bot->m_movementInfo.AddMovementFlag(MOVEMENTFLAG_WALKING);
    if (bot->IsWithinLOS(x, y, z))
        return MoveNear(target, sPlayerbotAIConfig->followDistance);

    WaitForReach(distance);

    if (bot->IsSitState())
        bot->SetStandState(UNIT_STAND_STATE_STAND);

    if (bot->IsNonMeleeSpellCast(true))
    {
        bot->CastStop();
        botAI->InterruptSpell();
    }

    bool generatePath = !bot->IsFlying() && !bot->IsUnderWater();
    bot->GetMotionMaster()->MovePoint(mapId, x, y, z, generatePath);

    AI_VALUE(LastMovement&, "last movement").Set(x, y, z, bot->GetOrientation());
    return true;
}

bool MoveToRpgTargetAction::isUseful()
{
    return context->GetValue<ObjectGuid>("rpg target")->Get() && AI_VALUE2(float, "distance", "rpg target") > sPlayerbotAIConfig->followDistance;
}
