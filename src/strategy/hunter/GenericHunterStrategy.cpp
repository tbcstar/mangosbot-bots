/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericHunterStrategy.h"
#include "../../Playerbot.h"

class GenericHunterStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        GenericHunterStrategyActionNodeFactory()
        {
            creators["rapid fire"] = &rapid_fire;
            creators["boost"] = &rapid_fire;
            creators["aspect of the pack"] = &aspect_of_the_pack;
            creators["feign death"] = &feign_death;
        }

    private:
        static ActionNode* rapid_fire(PlayerbotAI* botAI)
        {
            return new ActionNode ("rapid fire",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("readiness"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* aspect_of_the_pack(PlayerbotAI* botAI)
        {
            return new ActionNode ("aspect of the pack",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("aspect of the cheetah"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* feign_death(PlayerbotAI* botAI)
        {
            return new ActionNode ("feign death",
                /*P*/ nullptr,
                /*A*/ nullptr,
                /*C*/ nullptr);
        }
};

GenericHunterStrategy::GenericHunterStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI)
{
    actionNodeFactories.Add(new GenericHunterStrategyActionNodeFactory());
}

void GenericHunterStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("enemy is close", NextAction::array(0, new NextAction("wing clip", 50.0f), nullptr)));
    triggers.push_back(new TriggerNode("medium threat", NextAction::array(0, new NextAction("feign death", 32.0f), nullptr)));
    triggers.push_back(new TriggerNode("hunters pet low health", NextAction::array(0, new NextAction("mend pet", 20.0f), nullptr)));
}

NextAction** HunterBoostStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("bestial wrath", 15.0f), nullptr);
}

void HunterBoostStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("rapid fire", NextAction::array(0, new NextAction("rapid fire", 16.0f), nullptr)));
}

void HunterCcStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("scare beast", NextAction::array(0, new NextAction("scare beast on cc", ACTION_HIGH + 3), nullptr)));
}
