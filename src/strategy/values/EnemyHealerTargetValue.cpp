#include "botpch.h"
#include "../../playerbot.h"
#include "EnemyHealerTargetValue.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

Unit* EnemyHealerTargetValue::Calculate()
{
    string spell = qualifier;

    list<ObjectGuid> attackers = botAI->GetAiObjectContext()->GetValue<list<ObjectGuid> >("attackers")->Get();
    Unit* target = botAI->GetAiObjectContext()->GetValue<Unit*>("current target")->Get();
    for (list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* unit = botAI->GetUnit(*i);
        if (!unit || unit == target)
            continue;

        if (bot->GetDistance(unit) > botAI->GetRange("spell"))
            continue;

        if (!botAI->IsInterruptableSpellCasting(unit, spell))
            continue;

        Spell* spell = unit->GetCurrentSpell(CURRENT_GENERIC_SPELL);
        if (spell && IsPositiveSpell(spell->m_spellInfo))
            return unit;

        spell = unit->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
        if (spell && IsPositiveSpell(spell->m_spellInfo))
            return unit;
    }

    return NULL;
}
