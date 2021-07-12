/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AvailableLootValue.h"
#include "LootObjectStack.h"

AvailableLootValue::AvailableLootValue(PlayerbotAI* botAI) : ManualSetValue<LootObjectStack*>(botAI, nullptr)
{
    value = new LootObjectStack(botAI->GetBot());
}

~AvailableLootValue::AvailableLootValue()
{
    delete value;
}

LootTargetValue::LootTargetValue(PlayerbotAI* botAI) : ManualSetValue<LootObject>(botAI, LootObject())
{
}

bool CanLootValue::Calculate()
{
    LootObject loot = AI_VALUE(LootObject, "loot target");
    return !loot.IsEmpty() && loot.GetWorldObject(bot) && loot.IsLootPossible(bot) &&
        sServerFacade->IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "loot target"), INTERACTION_DISTANCE);
}
