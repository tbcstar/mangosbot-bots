#include "botpch.h"
#include "../../playerbot.h"
#include "AttackerWithoutAuraTargetValue.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

Unit* AttackerWithoutAuraTargetValue::Calculate()
{
    list<ObjectGuid> attackers = botAI->GetAiObjectContext()->GetValue<list<ObjectGuid> >("attackers")->Get();
    Unit* target = botAI->GetAiObjectContext()->GetValue<Unit*>("current target")->Get();
    for (list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* unit = botAI->GetUnit(*i);
        if (!unit || unit == target)
            continue;

        if (bot->GetDistance(unit) > botAI->GetRange("spell"))
            continue;

        if (!botAI->HasAura(qualifier, unit))
            return unit;
    }

    return nullptr;
}
