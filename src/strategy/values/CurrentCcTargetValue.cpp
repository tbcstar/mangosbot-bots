#include "botpch.h"
#include "../../playerbot.h"
#include "CurrentCcTargetValue.h"

using namespace botAI;

class FindCurrentCcTargetStrategy : public FindTargetStrategy
{
public:
    FindCurrentCcTargetStrategy(PlayerbotAI* botAI, std::string const& spell) : FindTargetStrategy(botAI)
    {
        this->spell = spell;
    }

public:
    virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager)
    {
        if (botAI->HasAura(spell, attacker))
            result = attacker;
    }

private:
    string spell;
};


Unit* CurrentCcTargetValue::Calculate()
{
    FindCurrentCcTargetStrategy strategy(botAI, qualifier);
    return FindTarget(&strategy);
}
