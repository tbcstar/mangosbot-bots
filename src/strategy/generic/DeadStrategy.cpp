/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DeadStrategy.h"
#include "Playerbot.h"

void DeadStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    PassTroughStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("often", NextAction::array(0, new NextAction("auto release", relevance), nullptr)));
    triggers.push_back(new TriggerNode("bg active", NextAction::array(0, new NextAction("auto release", relevance), nullptr)));
    triggers.push_back(new TriggerNode("often", NextAction::array(0, new NextAction("leave far away", relevance), nullptr))); //If partyleader just walks away without reviving. Leave group.
    triggers.push_back(new TriggerNode("dead", NextAction::array(0, new NextAction("find corpse", relevance), nullptr)));
    triggers.push_back(new TriggerNode("corpse near", NextAction::array(0, new NextAction("revive from corpse", relevance), nullptr)));
    triggers.push_back(new TriggerNode("resurrect request", NextAction::array(0, new NextAction("accept resurrect", relevance), nullptr)));
    triggers.push_back(new TriggerNode("falling far", NextAction::array(0, new NextAction("repop", relevance), nullptr)));
}

DeadStrategy::DeadStrategy(PlayerbotAI* botAI) : PassTroughStrategy(botAI)
{
}
