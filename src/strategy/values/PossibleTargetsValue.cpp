#include "botpch.h"
#include "../../playerbot.h"
#include "PossibleTargetsValue.h"

#include "../../ServerFacade.h"
#include "AttackersValue.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

void PossibleTargetsValue::FindUnits(list<Unit*> &targets)
{
    acore::AnyUnfriendlyUnitInObjectRangeCheck u_check(bot, range);
    acore::UnitListSearcher<acore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

bool PossibleTargetsValue::AcceptUnit(Unit* unit)
{
    return AttackersValue::IsPossibleTarget(unit, bot);
}
