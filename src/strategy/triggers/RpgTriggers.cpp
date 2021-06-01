/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RpgTriggers.h"
#include "Playerbot.h"

bool NoRpgTargetTrigger::IsActive()
{
    return !context->GetValue<ObjectGuid>("rpg target")->Get() && !AI_VALUE(GuidVector, "possible rpg targets").empty();
}

bool FarFromRpgTargetTrigger::IsActive()
{
    ObjectGuid unit = context->GetValue<ObjectGuid>("rpg target")->Get();
    if (!unit)
        return false;

    float distance = AI_VALUE2(float, "distance", "rpg target");
    return distance > sPlayerbotAIConfig->followDistance;
}
