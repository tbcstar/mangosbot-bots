#include "botpch.h"
#include "../../playerbot.h"
#include "NearestFriendlyPlayersValue.h"

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

void NearestFriendlyPlayersValue::FindUnits(list<Unit*> &targets)
{
    acore::AnyFriendlyUnitInObjectRangeCheck u_check(bot, range);
    acore::UnitListSearcher<acore::AnyFriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

bool NearestFriendlyPlayersValue::AcceptUnit(Unit* unit)
{
    ObjectGuid guid = unit->GetGUID();
    return guid.IsPlayer() && guid != ai->GetBot()->GetGUID();
}
