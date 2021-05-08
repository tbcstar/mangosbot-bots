#include "../generic/NonCombatStrategy.h"
#pragma once

namespace ai
{
    class DpsAssistStrategy : public NonCombatStrategy
    {
    public:
        DpsAssistStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "dps assist"; }
		virtual int GetType() { return STRATEGY_TYPE_DPS; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class DpsAoeStrategy : public NonCombatStrategy
    {
    public:
        DpsAoeStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "dps aoe"; }
		virtual int GetType() { return STRATEGY_TYPE_DPS; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
