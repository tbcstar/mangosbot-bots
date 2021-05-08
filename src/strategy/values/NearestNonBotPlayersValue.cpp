#include "botpch.h"
#include "../../playerbot.h"
#include "NearestNonBotPlayersValue.h"

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

void NearestNonBotPlayersValue::FindUnits(list<Unit*> &targets)
{
    AnyUnitInObjectRangeCheck u_check(bot, range);
    UnitListSearcher<AnyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

bool NearestNonBotPlayersValue::AcceptUnit(Unit* unit)
{
    ObjectGuid guid = unit->GetGUID();
    return guid.IsPlayer() && !((Player*)unit)->GetPlayerbotAI();
}
