#include "botpch.h"
#include "../../playerbot.h"
#include "GenericWarriorStrategy.h"
#include "WarriorAiObjectContext.h"

using namespace botAI;

GenericWarriorStrategy::GenericWarriorStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI)
{
}

void GenericWarriorStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "battle shout",
        NextAction::array(0, new NextAction("battle shout", ACTION_NORMAL + 5), nullptr)));

    triggers.push_back(new TriggerNode(
        "bloodrage",
        NextAction::array(0, new NextAction("bloodrage", ACTION_HIGH + 1), nullptr)));

    triggers.push_back(new TriggerNode(
        "shield bash",
        NextAction::array(0, new NextAction("shield bash", ACTION_INTERRUPT + 4), nullptr)));

    triggers.push_back(new TriggerNode(
        "shield bash on enemy healer",
        NextAction::array(0, new NextAction("shield bash on enemy healer", ACTION_INTERRUPT + 3), nullptr)));

	triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("intimidating shout", ACTION_EMERGENCY), nullptr)));
}
