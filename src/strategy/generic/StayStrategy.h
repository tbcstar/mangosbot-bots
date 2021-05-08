#include "../generic/NonCombatStrategy.h"
#pragma once

namespace ai
{
    class StayStrategy : public NonCombatStrategy
    {
    public:
        StayStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "stay"; }
        virtual NextAction** getDefaultActions();
    };

    class SitStrategy : public NonCombatStrategy
    {
    public:
        SitStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "sit"; }
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

}
