/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NonCombatStrategy.h"
#include "Playerbot.h"

void NonCombatStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("timer", NextAction::array(0, new NextAction("check mount state", 1.0f), new NextAction("check values", 1.0f), nullptr)));
}

void LfgStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("no possible targets", NextAction::array(0, new NextAction("lfg join", 1.0f), nullptr)));
    triggers.push_back(new TriggerNode("lfg proposal", NextAction::array(0, new NextAction("lfg accept", 1.0f), nullptr)));
    triggers.push_back(new TriggerNode("lfg proposal active", NextAction::array(0, new NextAction("lfg accept", 1.0f), nullptr)));
}

void CollisionStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("collision", NextAction::array(0, new NextAction("move out of collision", 2.0f), nullptr)));
}
