#include "botpch.h"
#include "../../playerbot.h"
#include "CurrentTargetValue.h"

#include "../../ServerFacade.h"
using namespace botAI;

Unit* CurrentTargetValue::Get()
{
    if (selection.IsEmpty())
        return nullptr;

    Unit* unit = ObjectAccessor::GetUnit(*bot, selection);
    if (unit && !sServerFacade->IsWithinLOSInMap(bot, unit))
        return nullptr;

    return unit;
}

void CurrentTargetValue::Set(Unit* target)
{
    selection = target ? target->GetGUID() : ObjectGuid::Empty;
}
