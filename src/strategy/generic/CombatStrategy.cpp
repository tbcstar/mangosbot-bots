/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CombatStrategy.h"
#include "../../Playerbot.h"

void CombatStrategy::InitTriggers(std::vector<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode("enemy out of spell", NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), nullptr)));
    triggers.push_back(new TriggerNode("invalid target", NextAction::array(0, new NextAction("drop target", 55), nullptr)));
}
