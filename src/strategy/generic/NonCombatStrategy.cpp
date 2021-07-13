/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NonCombatStrategy.h"
#include "Playerbot.h"

void NonCombatStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("timer", NextAction::array(0, new NextAction("check mount state", 1.0f), new NextAction("check values", 1.0f), nullptr)));
    //triggers.push_back(new TriggerNode("no non bot players around", NextAction::array(0, new NextAction("move random", 0.5f), nullptr)));
    triggers.push_back(new TriggerNode("random", NextAction::array(0, new NextAction("clean quest log", 6.0f), nullptr)));
    triggers.push_back(new TriggerNode("often", NextAction::array(0, new NextAction("invite nearby", 4.0f), nullptr)));
    triggers.push_back(new TriggerNode("often", NextAction::array(0, new NextAction("leader", 2.0f), nullptr)));
    triggers.push_back(new TriggerNode("seldom", NextAction::array(0, new NextAction("leave far away", 4.0f), nullptr)));
    triggers.push_back(new TriggerNode("near dark portal", NextAction::array(0, new NextAction("move to dark portal", 1.0f), nullptr)));
    triggers.push_back(new TriggerNode("at dark portal azeroth", NextAction::array(0, new NextAction("use dark portal azeroth", 1.0f), nullptr)));
    triggers.push_back(new TriggerNode("at dark portal outland", NextAction::array(0, new NextAction("move from dark portal", 1.0f), nullptr)));
    triggers.push_back(new TriggerNode("need world buff", NextAction::array(0, new NextAction("world buff", 1.0f), nullptr)));
    triggers.push_back(new TriggerNode("hearth is faster", NextAction::array(0, new NextAction("hearthstone", 1.1f), nullptr)));
    triggers.push_back(new TriggerNode("often", NextAction::array(0, new NextAction("use random recipe", 1.0f), nullptr)));

    /*AiObjectContext* context = botAI->GetAiObjectContext();
    triggers.push_back(new TriggerNode("has continue action", NextAction::array(0, new NextAction("continue action", AI_VALUE(MoveTarget*, "move target")->getRelevance()), nullptr)));
    triggers.push_back(new TriggerNode("wants in bg", NextAction::array(0, new NextAction("queue at bm", 20.0f), nullptr)));*/
}

void CollisionStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("collision", NextAction::array(0, new NextAction("move out of collision", 2.0f), nullptr)));
}

void MountStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    /*triggers.push_back(new TriggerNode("no possible targets", NextAction::array(0, new NextAction("mount", 1.0f), nullptr)));
    triggers.push_back(new TriggerNode("no rpg target", NextAction::array(0, new NextAction("mount", 1.0f), nullptr)));*/
    /*triggers.push_back(new TriggerNode("often", NextAction::array(0, new NextAction("mount", 4.0f), nullptr)));*/
}
