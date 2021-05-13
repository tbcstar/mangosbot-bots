#include "botpch.h"
#include "../../playerbot.h"
#include "CurrentTargetValue.h"

#include "../../ServerFacade.h"
using namespace ai;

Unit* CurrentTargetValue::Get()
{
    if (selection.IsEmpty())
        return NULL;

    Unit* unit = ObjectAccessor::GetUnit(*bot, selection);
    if (unit && !sServerFacade->IsWithinLOSInMap(bot, unit))
        return NULL;

    return unit;
}

void CurrentTargetValue::Set(Unit* target)
{
    selection = target ? target->GetGUID() : ObjectGuid::Empty;
}
