#include "../generic/NonCombatStrategy.h"
#pragma once

namespace ai
{
    class GuardStrategy : public NonCombatStrategy
    {
    public:
        GuardStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "guard"; }
        NextAction** getDefaultActions();

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };



}
