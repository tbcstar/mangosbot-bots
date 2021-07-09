/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PriestNonCombatStrategy.h"
#include "PriestNonCombatStrategyActionNodeFactory.h"
#include "Playerbot.h"

PriestNonCombatStrategy::PriestNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI)
{
    actionNodeFactories.Add(new PriestNonCombatStrategyActionNodeFactory());
}

void PriestNonCombatStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("power word: fortitude", NextAction::array(0, new NextAction("power word: fortitude", 12.0f), nullptr)));
    triggers.push_back(new TriggerNode("divine spirit", NextAction::array(0, new NextAction("divine spirit", 14.0f), nullptr)));
    triggers.push_back(new TriggerNode("inner fire", NextAction::array(0, new NextAction("inner fire", 10.0f), nullptr)));
	triggers.push_back(new TriggerNode("party member dead", NextAction::array(0, new NextAction("resurrection", 30.0f), nullptr)));
}

void PriestBuffStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("prayer of fortitude on party", NextAction::array(0, new NextAction("prayer of fortitude on party", 10.0f), nullptr)));
    triggers.push_back(new TriggerNode("prayer of spirit on party", NextAction::array(0, new NextAction("prayer of spirit on party", 10.0f), nullptr)));
    triggers.push_back(new TriggerNode("power word: fortitude on party", NextAction::array(0, new NextAction("power word: fortitude on party", 11.0f), nullptr)));
    triggers.push_back(new TriggerNode("divine spirit on party", NextAction::array(0, new NextAction("divine spirit on party", 13.0f), nullptr)));
}

void PriestShadowResistanceStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("shadow protection", NextAction::array(0, new NextAction("shadow protection", 12.0f), nullptr)));
    triggers.push_back(new TriggerNode("shadow protection on party", NextAction::array(0, new NextAction("shadow protection on party", 11.0f), nullptr)));
}
