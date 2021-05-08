#pragma once

#include "../Strategy.h"
#include "../generic/CombatStrategy.h"

namespace ai
{
    class GenericShamanStrategy : public CombatStrategy
    {
    public:
        GenericShamanStrategy(PlayerbotAI* botAI);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);

    };

    class ShamanBuffDpsStrategy : public Strategy
    {
    public:
        ShamanBuffDpsStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "bdps"; }

    };

    class ShamanBuffManaStrategy : public Strategy
    {
    public:
        ShamanBuffManaStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "bmana"; }

    };

    class ShamanCureStrategy : public Strategy
    {
    public:
        ShamanCureStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "cure"; }

    };
}
