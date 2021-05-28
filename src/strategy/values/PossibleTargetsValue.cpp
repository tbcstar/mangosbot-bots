/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PossibleTargetsValue.h"
#include "AttackersValue.h"
#include "../../Playerbot.h"

void PossibleTargetsValue::FindUnits(std::list<Unit*>& targets)
{
    acore::AnyUnfriendlyUnitInObjectRangeCheck u_check(bot, bot, range);
    acore::UnitListSearcher<acore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(bot, targets, u_check);
    bot->VisitNearbyObject(range, searcher);
}

bool PossibleTargetsValue::AcceptUnit(Unit* unit)
{
    return AttackersValue::IsPossibleTarget(unit, bot);
}
