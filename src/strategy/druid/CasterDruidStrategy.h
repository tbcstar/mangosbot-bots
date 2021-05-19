#pragma once

#include "GenericDruidStrategy.h"
#include "../generic/CombatStrategy.h"

namespace ai
{
    class CasterDruidStrategy : public GenericDruidStrategy
    {
    public:
        CasterDruidStrategy();

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "caster"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
    };

    class CasterDruidAoeStrategy : public CombatStrategy
    {
    public:
        CasterDruidAoeStrategy() : CombatStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "caster aoe"; }
    };

    class CasterDruidDebuffStrategy : public CombatStrategy
    {
    public:
        CasterDruidDebuffStrategy() : CombatStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "caster debuff"; }
    };
}
