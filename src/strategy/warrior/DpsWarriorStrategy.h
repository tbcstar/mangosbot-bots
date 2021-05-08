#pragma once

#include "GenericWarriorStrategy.h"

namespace ai
{
    class DpsWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        DpsWarriorStrategy(PlayerbotAI* botAI);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "dps"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
    };

    class DpsWarrirorAoeStrategy : public CombatStrategy
    {
    public:
        DpsWarrirorAoeStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "aoe"; }
    };
}
