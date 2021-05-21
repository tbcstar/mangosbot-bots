#include "botpch.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockNonCombatStrategy.h"

using namespace botAI;

class GenericWarlockNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericWarlockNonCombatStrategyActionNodeFactory()
    {
        creators["fel armor"] = &fel_armor;
        creators["demon armor"] = &demon_armor;
    }
private:
    static ActionNode* fel_armor(PlayerbotAI* botAI)
    {
        return new ActionNode ("fel armor",
            /*P*/ nullptr,
            /*A*/ NextAction::array(0, new NextAction("demon armor"), nullptr),
            /*C*/ nullptr);
    }
    static ActionNode* demon_armor(PlayerbotAI* botAI)
    {
        return new ActionNode ("demon armor",
            /*P*/ nullptr,
            /*A*/ NextAction::array(0, new NextAction("demon skin"), nullptr),
            /*C*/ nullptr);
    }
};

GenericWarlockNonCombatStrategy::GenericWarlockNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI)
{
    actionNodeFactories.Add(new GenericWarlockNonCombatStrategyActionNodeFactory());
}

void GenericWarlockNonCombatStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demon armor",
        NextAction::array(0, new NextAction("fel armor", 21.0f), nullptr)));
}

void WarlockPetStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon voidwalker", 30.0f), nullptr)));
}
