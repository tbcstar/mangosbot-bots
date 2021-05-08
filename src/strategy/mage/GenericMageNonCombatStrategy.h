#pragma once

#include "GenericMageStrategy.h"
#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericMageNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericMageNonCombatStrategy(PlayerbotAI* botAI);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class MageBuffManaStrategy : public Strategy
    {
    public:
        MageBuffManaStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "bmana"; }
    };

    class MageBuffDpsStrategy : public Strategy
    {
    public:
        MageBuffDpsStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "bdps"; }
    };

    class MageBuffStrategy : public Strategy
    {
    public:
        MageBuffStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "buff"; }
    };
}
