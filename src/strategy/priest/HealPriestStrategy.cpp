#include "botpch.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"

using namespace botAI;

NextAction** HealPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 5.0f), nullptr);
}

void HealPriestStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), nullptr)));

	triggers.push_back(new TriggerNode(
		"medium aoe heal",
		NextAction::array(0, new NextAction("circle of healing", 27.0f), nullptr)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("renew", 15.0f), nullptr)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("renew on party", 10.0f), nullptr)));

    triggers.push_back(new TriggerNode(
        "enemy is close",
        NextAction::array(0, new NextAction("fade", 50.0f), nullptr)));

    triggers.push_back(new TriggerNode(
        "party member to heal out of spell range",
        NextAction::array(0, new NextAction("reach party member to heal", ACTION_CRITICAL_HEAL + 1), nullptr)));
}
