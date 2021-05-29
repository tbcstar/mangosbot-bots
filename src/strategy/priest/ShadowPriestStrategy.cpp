/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ShadowPriestStrategy.h"
#include "ShadowPriestStrategyActionNodeFactory.h"
#include "../../Playerbot.h"

ShadowPriestStrategy::ShadowPriestStrategy(PlayerbotAI* botAI) : GenericPriestStrategy(botAI)
{
    actionNodeFactories.Add(new ShadowPriestStrategyActionNodeFactory());
}

NextAction** ShadowPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("mind blast", 10.0f), nullptr);
}

void ShadowPriestStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("enemy out of spell", NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), nullptr)));
    triggers.push_back(new TriggerNode("shadowform", NextAction::array(0, new NextAction("shadowform", 15.0f), nullptr)));
    triggers.push_back(new TriggerNode("low mana", NextAction::array(0, new NextAction("dispersion", ACTION_EMERGENCY + 5), nullptr)));
    triggers.push_back(new TriggerNode("vampiric embrace", NextAction::array(0, new NextAction("vampiric embrace", 16.0f), nullptr)));
}

void ShadowPriestAoeStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("shadow word: pain on attacker", NextAction::array(0, new NextAction("shadow word: pain on attacker", 11.0f), nullptr)));
}

void ShadowPriestDebuffStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("devouring plague", NextAction::array(0, new NextAction("devouring plague", 13.0f), nullptr)));
    triggers.push_back(new TriggerNode("vampiric touch", NextAction::array(0, new NextAction("vampiric touch", 11.0f), nullptr)));
    triggers.push_back(new TriggerNode("shadow word: pain", NextAction::array(0, new NextAction("shadow word: pain", 12.0f), nullptr)));
}
