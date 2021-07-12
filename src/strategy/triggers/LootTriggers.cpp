/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "LootTriggers.h"
#include "ServerFacade.h"

bool LootAvailableTrigger::IsActive()
{
    return AI_VALUE(bool, "has available loot") && /*AI_VALUE(uint8, "bag space") < 80 &&*/
        (sServerFacade->IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "loot target"), INTERACTION_DISTANCE) || AI_VALUE(GuidVector, "all targets").empty()) &&
        !AI_VALUE2(bool, "combat", "self target") && !AI_VALUE2(bool, "mounted", "self target");
}

bool FarFromCurrentLootTrigger::IsActive()
{
    return AI_VALUE2(float, "distance", "loot target") > INTERACTION_DISTANCE;
}

bool CanLootTrigger::IsActive()
{
    return AI_VALUE(bool, "can loot");
}
