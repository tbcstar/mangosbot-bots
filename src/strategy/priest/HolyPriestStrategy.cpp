/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "HolyPriestStrategy.h"
#include "Playerbot.h"

class HolyPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        HolyPriestStrategyActionNodeFactory()
        {
            creators["smite"] = &smite;
        }

    private:
        static ActionNode* smite(PlayerbotAI* botAI)
        {
            return new ActionNode ("smite",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("shoot"), nullptr),
                /*C*/ nullptr);
        }
};

HolyPriestStrategy::HolyPriestStrategy(PlayerbotAI* botAI) : HealPriestStrategy(botAI)
{
    actionNodeFactories.Add(new HolyPriestStrategyActionNodeFactory());
}

NextAction** HolyPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("holy fire", 10.0f), new NextAction("smite", 10.0f), nullptr);
}

void HolyPriestStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    HealPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("enemy out of spell", NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), nullptr)));

}
