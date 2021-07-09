/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "LfgStrategy.h"
#include "Playerbot.h"

void LfgStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode("random", NextAction::array(0, new NextAction("lfg join", relevance), NULL)));
    triggers.push_back(new TriggerNode("seldom", NextAction::array(0, new NextAction("lfg leave", relevance), NULL)));
}

LfgStrategy::LfgStrategy(PlayerbotAI* ai) : PassTroughStrategy(ai)
{
}
