/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NearestNonBotPlayersValue.h"
#include "../../Playerbot.h"

void NearestNonBotPlayersValue::FindUnits(list<Unit*> &targets)
{
    acore::AnyUnitInObjectRangeCheck u_check(bot, range);
    acore::UnitListSearcher<acore::AnyUnitInObjectRangeCheck> searcher(bot, targets, u_check);
    bot->VisiNearbyObject(range, searcher);
}

bool NearestNonBotPlayersValue::AcceptUnit(Unit* unit)
{
    ObjectGuid guid = unit->GetGUID();
    return guid.IsPlayer() && !((Player*)unit)->GetPlayerbotAI();
}
