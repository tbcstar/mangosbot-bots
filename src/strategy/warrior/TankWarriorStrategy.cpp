/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "TankWarriorStrategy.h"
#include "Playerbot.h"

TankWarriorStrategy::TankWarriorStrategy(PlayerbotAI* botAI) : GenericWarriorStrategy(botAI)
{
}

NextAction** TankWarriorStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("sunder armor", ACTION_NORMAL + 1), new NextAction("melee", ACTION_NORMAL), nullptr);
}

void TankWarriorStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("defensive stance", NextAction::array(0, new NextAction("defensive stance", ACTION_HIGH + 9), nullptr)));
    triggers.push_back(new TriggerNode("medium rage available", NextAction::array(0, new NextAction("shield slam", ACTION_NORMAL + 2), new NextAction("heroic strike", ACTION_NORMAL + 2), nullptr)));
    triggers.push_back(new TriggerNode("shield block", NextAction::array(0, new NextAction("shield block", ACTION_NORMAL + 3), nullptr)));
    triggers.push_back(new TriggerNode("revenge", NextAction::array(0, new NextAction("revenge", ACTION_NORMAL + 4), nullptr)));
    triggers.push_back(new TriggerNode("lose aggro", NextAction::array(0, new NextAction("taunt", ACTION_HIGH + 8), nullptr)));
    triggers.push_back(new TriggerNode("low health", NextAction::array(0, new NextAction("shield wall", ACTION_MEDIUM_HEAL), nullptr)));
	triggers.push_back(new TriggerNode("critical health", NextAction::array(0, new NextAction("last stand", ACTION_EMERGENCY + 3), nullptr)));
	triggers.push_back(new TriggerNode("light aoe", NextAction::array(0, new NextAction("demoralizing shout", ACTION_HIGH + 2), new NextAction("cleave", ACTION_HIGH + 1), nullptr)));
	triggers.push_back(new TriggerNode("medium aoe", NextAction::array(0, new NextAction("battle shout taunt", ACTION_HIGH + 3), nullptr)));
    triggers.push_back(new TriggerNode("high aoe", NextAction::array(0, new NextAction("challenging shout", ACTION_HIGH + 3), nullptr)));
	triggers.push_back(new TriggerNode("concussion blow", NextAction::array(0, new NextAction("concussion blow", ACTION_INTERRUPT), nullptr)));
    triggers.push_back(new TriggerNode("sword and board", NextAction::array(0, new NextAction("shield slam", ACTION_HIGH + 3), nullptr)));
}
