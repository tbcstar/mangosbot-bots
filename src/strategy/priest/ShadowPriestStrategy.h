#pragma once

#include "HealPriestStrategy.h"

namespace ai
{
    class ShadowPriestStrategy : public GenericPriestStrategy
    {
    public:
        ShadowPriestStrategy(PlayerbotAI* botAI);

    public:
        virtual NextAction** getDefaultActions();
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "shadow"; }
        virtual int GetType() { return STRATEGY_TYPE_DPS|STRATEGY_TYPE_RANGED; }
    };

    class ShadowPriestAoeStrategy : public CombatStrategy
    {
    public:
        ShadowPriestAoeStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "shadow aoe"; }
    };

    class ShadowPriestDebuffStrategy : public CombatStrategy
    {
    public:
        ShadowPriestDebuffStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "shadow debuff"; }
    };
}
