/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "TankPaladinStrategy.h"
#include "Playerbot.h"

TankPaladinStrategy::TankPaladinStrategy(PlayerbotAI* botAI) : GenericPaladinStrategy(botAI)
{
}

NextAction** TankPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_NORMAL), nullptr);
}

void TankPaladinStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("seal", NextAction::array(0, new NextAction("seal of light", 90.0f), nullptr)));
    triggers.push_back(new TriggerNode("judgement of light", NextAction::array(0, new NextAction("judgement of light", ACTION_NORMAL + 2), nullptr)));
    triggers.push_back(new TriggerNode("medium mana", NextAction::array(0, new NextAction("judgement of wisdom", ACTION_NORMAL + 3), nullptr)));
    triggers.push_back(new TriggerNode("light aoe", NextAction::array(0, new NextAction("hammer of the righteous", ACTION_HIGH + 6), new NextAction("avenger's shield", ACTION_HIGH + 6), nullptr)));
    triggers.push_back(new TriggerNode("medium aoe", NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 6), nullptr)));
    triggers.push_back(new TriggerNode("lose aggro", NextAction::array(0, new NextAction("hand of reckoning", ACTION_HIGH + 7), nullptr)));
	triggers.push_back(new TriggerNode("holy shield", NextAction::array(0, new NextAction("holy shield", ACTION_HIGH + 7), nullptr)));
    triggers.push_back(new TriggerNode("blessing", NextAction::array(0, new NextAction("blessing of sanctuary", ACTION_HIGH + 9), nullptr)));
}
