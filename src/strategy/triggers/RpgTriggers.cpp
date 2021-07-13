/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RpgTriggers.h"
#include "Playerbot.h"

bool NoRpgTargetTrigger::IsActive()
{
    return !context->GetValue<ObjectGuid>("rpg target")->Get();
}

bool FarFromRpgTargetTrigger::IsActive()
{
    ObjectGuid unit = context->GetValue<ObjectGuid>("rpg target")->Get();
    if (!unit)
        return false;

    float distance = AI_VALUE2(float, "distance", "rpg target");

    if (sPlayerbotAIConfig->RandombotsWalkingRPGInDoors)
    {
        if (!bot->IsOutdoors())
        {
            bot->m_movementInfo.AddMovementFlag(MOVEMENTFLAG_WALKING);
        }
    }

    return distance > sPlayerbotAIConfig->followDistance;
}
