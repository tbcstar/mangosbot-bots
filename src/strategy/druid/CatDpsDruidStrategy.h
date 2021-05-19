#pragma once

#include "FeralDruidStrategy.h"
#include "../generic/CombatStrategy.h"

namespace ai
{
    class CatDpsDruidStrategy : public FeralDruidStrategy
    {
    public:
        CatDpsDruidStrategy();

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "cat"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_MELEE; }
    };

    class CatAoeDruidStrategy : public CombatStrategy
    {
    public:
        CatAoeDruidStrategy() : CombatStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "cat aoe"; }
    };
}
