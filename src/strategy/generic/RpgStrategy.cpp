/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RpgStrategy.h"

RpgStrategy::RpgStrategy(PlayerbotAI* botAI) : Strategy(botAI)
{
}

NextAction** RpgStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("rpg", 1.1f), nullptr);
}

void RpgStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("no rpg target", NextAction::array(0, new NextAction("choose rpg target", 5.0f), nullptr)));
    triggers.push_back(new TriggerNode("far from rpg target", NextAction::array(0, new NextAction("move to rpg target", 5.0f), nullptr)));
}
