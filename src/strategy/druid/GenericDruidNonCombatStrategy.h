#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericDruidNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericDruidNonCombatStrategy(PlayerbotAI* botAI);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class GenericDruidBuffStrategy : public NonCombatStrategy
    {
    public:
        GenericDruidBuffStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "buff"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
