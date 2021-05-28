/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CollisionValue.h"
#include "../../Playerbot.h"
#include "../../ServerFacade.h"

bool CollisionValue::Calculate()
{
    Unit* target = AI_VALUE(Unit*, qualifier);
    if (!target)
        return false;

    std::list<Unit*> targets;
    float range = sPlayerbotAIConfig->contactDistance;
    acore::AnyUnitInObjectRangeCheck u_check(bot, range);
    acore::UnitListSearcher<acore::AnyUnitInObjectRangeCheck> searcher(bot, targets, u_check);
    bot->VisitNearbyObject(range, searcher);

    for (Unit* target : targets)
    {
        if (bot == target)
            continue;

        float dist = sServerFacade->GetDistance2d(bot, target->GetPositionX(), target->GetPositionY());
        if (sServerFacade->IsDistanceLessThan(dist, target->GetCombatReach()))
            return true;
    }

    return false;
}
