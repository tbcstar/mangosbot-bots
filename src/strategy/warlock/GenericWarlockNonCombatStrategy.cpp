/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericWarlockNonCombatStrategy.h"
#include "Playerbot.h"

class GenericWarlockNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        GenericWarlockNonCombatStrategyActionNodeFactory()
        {
            creators["fel armor"] = &fel_armor;
            creators["demon armor"] = &demon_armor;
        }

    private:
        static ActionNode* fel_armor(PlayerbotAI* botAI)
        {
            return new ActionNode ("fel armor",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("demon armor"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* demon_armor(PlayerbotAI* botAI)
        {
            return new ActionNode ("demon armor",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("demon skin"), nullptr),
                /*C*/ nullptr);
        }
};

GenericWarlockNonCombatStrategy::GenericWarlockNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI)
{
    actionNodeFactories.Add(new GenericWarlockNonCombatStrategyActionNodeFactory());
}

void GenericWarlockNonCombatStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("demon armor", NextAction::array(0, new NextAction("fel armor", 21.0f), nullptr)));
}

void WarlockPetStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("no pet", NextAction::array(0, new NextAction("summon voidwalker", 30.0f), nullptr)));
}
