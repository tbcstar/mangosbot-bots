/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericDruidNonCombatStrategy.h"
#include "Playerbot.h"

class GenericDruidNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        GenericDruidNonCombatStrategyActionNodeFactory()
        {
            creators["mark of the wild"] = &mark_of_the_wild;
            creators["mark of the wild on party"] = &mark_of_the_wild_on_party;
            creators["innervate"] = &innervate;
        }

    private:
        static ActionNode* mark_of_the_wild(PlayerbotAI* botAI)
        {
            return new ActionNode ("mark of the wild",
                /*P*/ NextAction::array(0, new NextAction("caster form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* mark_of_the_wild_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode ("mark of the wild on party",
                /*P*/ NextAction::array(0, new NextAction("caster form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* innervate(PlayerbotAI* botAI)
        {
            return new ActionNode ("innervate",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("drink"), nullptr),
                /*C*/ nullptr);
        }
};

GenericDruidNonCombatStrategy::GenericDruidNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI)
{
    actionNodeFactories.Add(new GenericDruidNonCombatStrategyActionNodeFactory());
}

void GenericDruidNonCombatStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("mark of the wild", NextAction::array(0, new NextAction("mark of the wild", 12.0f), nullptr)));
    triggers.push_back(new TriggerNode("cure poison", NextAction::array(0, new NextAction("abolish poison", 21.0f), nullptr)));
    triggers.push_back(new TriggerNode("party member cure poison", NextAction::array(0, new NextAction("abolish poison on party", 20.0f), nullptr)));
	triggers.push_back(new TriggerNode("party member dead", NextAction::array(0, new NextAction("revive", 22.0f), nullptr)));
    triggers.push_back(new TriggerNode("low mana", NextAction::array(0, new NextAction("innervate", ACTION_EMERGENCY + 5), nullptr)));
}

void GenericDruidBuffStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("mark of the wild on party", NextAction::array(0, new NextAction("mark of the wild on party", 11.0f), nullptr)));
}
