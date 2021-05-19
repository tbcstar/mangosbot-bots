#include "botpch.h"
#include "../../playerbot.h"
#include "WarriorMultipliers.h"
#include "DpsWarriorStrategy.h"

using namespace ai;

class DpsWarriorStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsWarriorStrategyActionNodeFactory()
    {
        creators["charge"] = &charge;
        creators["bloodthirst"] = &bloodthirst;
        creators["death wish"] = &death_wish;
    }
private:
    static ActionNode* charge(PlayerbotAI* botAI)
    {
        return new ActionNode ("charge",
            /*P*/ nullptr,
            /*A*/ NextAction::array(0, new NextAction("reach melee"), nullptr),
            /*C*/ nullptr);
    }
    static ActionNode* bloodthirst(PlayerbotAI* botAI)
    {
        return new ActionNode ("bloodthirst",
            /*P*/ nullptr,
            /*A*/ NextAction::array(0, new NextAction("heroic strike"), nullptr),
            /*C*/ nullptr);
    }
    static ActionNode* death_wish(PlayerbotAI* botAI)
    {
        return new ActionNode ("death wish",
            /*P*/ nullptr,
            /*A*/ NextAction::array(0, new NextAction("berserker rage"), nullptr),
            /*C*/ nullptr);
    }
};

DpsWarriorStrategy::DpsWarriorStrategy(PlayerbotAI* botAI) : GenericWarriorStrategy(botAI)
{
    actionNodeFactories.Add(new DpsWarriorStrategyActionNodeFactory());
}

NextAction** DpsWarriorStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("bloodthirst", ACTION_NORMAL + 1), new NextAction("melee", ACTION_NORMAL), nullptr);
}

void DpsWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("charge", ACTION_NORMAL + 9), nullptr)));

    triggers.push_back(new TriggerNode(
        "battle stance",
        NextAction::array(0, new NextAction("battle stance", ACTION_HIGH + 9), nullptr)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("execute", ACTION_HIGH + 4), nullptr)));

	triggers.push_back(new TriggerNode(
		"hamstring",
		NextAction::array(0, new NextAction("hamstring", ACTION_HIGH), nullptr)));

	triggers.push_back(new TriggerNode(
		"victory rush",
		NextAction::array(0, new NextAction("victory rush", ACTION_HIGH + 3), nullptr)));

    triggers.push_back(new TriggerNode(
        "death wish",
        NextAction::array(0, new NextAction("death wish", ACTION_HIGH + 2), nullptr)));

    triggers.push_back(new TriggerNode(
        "rend",
        NextAction::array(0, new NextAction("rend", ACTION_NORMAL + 1), nullptr)));
}


void DpsWarrirorAoeStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "rend on attacker",
        NextAction::array(0, new NextAction("rend on attacker", ACTION_HIGH + 1), nullptr)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("thunder clap", ACTION_HIGH + 2), new NextAction("demoralizing shout", ACTION_HIGH + 2), nullptr)));

    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("cleave", ACTION_HIGH + 3), nullptr)));
}
