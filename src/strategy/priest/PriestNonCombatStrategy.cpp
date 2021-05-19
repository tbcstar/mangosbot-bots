#include "botpch.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "PriestNonCombatStrategy.h"
#include "PriestNonCombatStrategyActionNodeFactory.h"

using namespace ai;

PriestNonCombatStrategy::PriestNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI)
{
    actionNodeFactories.Add(new PriestNonCombatStrategyActionNodeFactory());
}

void PriestNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "power word: fortitude",
        NextAction::array(0, new NextAction("power word: fortitude", 12.0f), nullptr)));

    triggers.push_back(new TriggerNode(
        "divine spirit",
        NextAction::array(0, new NextAction("divine spirit", 14.0f), nullptr)));


    triggers.push_back(new TriggerNode(
        "inner fire",
        NextAction::array(0, new NextAction("inner fire", 10.0f), nullptr)));


	triggers.push_back(new TriggerNode(
		"party member dead",
		NextAction::array(0, new NextAction("resurrection", 30.0f), nullptr)));
}

void PriestBuffStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "power word: fortitude on party",
        NextAction::array(0, new NextAction("power word: fortitude on party", 11.0f), nullptr)));

    triggers.push_back(new TriggerNode(
        "divine spirit on party",
        NextAction::array(0, new NextAction("divine spirit on party", 13.0f), nullptr)));
}

void PriestShadowResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadow protection",
        NextAction::array(0, new NextAction("shadow protection", 12.0f), nullptr)));

    triggers.push_back(new TriggerNode(
        "shadow protection on party",
        NextAction::array(0, new NextAction("shadow protection on party", 11.0f), nullptr)));
}