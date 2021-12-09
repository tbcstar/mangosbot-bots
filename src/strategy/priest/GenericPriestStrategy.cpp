/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericPriestStrategy.h"
#include "GenericPriestStrategyActionNodeFactory.h"
#include "HealPriestStrategy.h"
#include "Playerbot.h"

GenericPriestStrategy::GenericPriestStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI)
{
    actionNodeFactories.Add(new GenericPriestStrategyActionNodeFactory());
}

void GenericPriestStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("medium health", NextAction::array(0, new NextAction("flash heal", 25.0f), nullptr)));
    triggers.push_back(new TriggerNode("party member medium health", NextAction::array(0, new NextAction("flash heal on party", 20.0f), nullptr)));
    triggers.push_back(new TriggerNode("critical health", NextAction::array(0, new NextAction("power word: shield", 70.0f), new NextAction("flash heal", 70.0f), nullptr)));
    triggers.push_back(new TriggerNode("party member critical health", NextAction::array(0, new NextAction("power word: shield on party", 60.0f), new NextAction("flash heal on party", 60.0f), nullptr)));
    triggers.push_back(new TriggerNode("low health", NextAction::array(0, new NextAction("power word: shield", 60.0f), new NextAction("greater heal", 60.0f), nullptr)));
    triggers.push_back(new TriggerNode("party member low health", NextAction::array(0, new NextAction("power word: shield on party", 50.0f), new NextAction("greater heal on party", 50.0f), nullptr)));
    triggers.push_back(new TriggerNode("medium threat", NextAction::array(0, new NextAction("psychic scream", 50.0f), nullptr)));
    triggers.push_back(new TriggerNode("often", NextAction::array(0, new NextAction("apply oil", 1.0f), nullptr)));
}

void PriestCureStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("dispel magic", NextAction::array(0, new NextAction("dispel magic", 41.0f), nullptr)));
    triggers.push_back(new TriggerNode("dispel magic on party", NextAction::array(0, new NextAction("dispel magic on party", 40.0f), nullptr)));
    triggers.push_back(new TriggerNode("cure disease", NextAction::array(0, new NextAction("abolish disease", 31.0f), nullptr)));
    triggers.push_back(new TriggerNode("party member cure disease", NextAction::array(0, new NextAction("abolish disease on party", 30.0f), nullptr)));
}

void PriestBoostStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("inner focus", NextAction::array(0, new NextAction("inner focus", 42.0f), nullptr)));
    triggers.push_back(new TriggerNode("power infusion", NextAction::array(0, new NextAction("power infusion", 41.0f), nullptr)));
}

void PriestCcStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("shackle undead", NextAction::array(0, new NextAction("shackle undead", 31.0f), nullptr)));
}