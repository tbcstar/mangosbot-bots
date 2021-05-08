#include "../generic/NonCombatStrategy.h"
#pragma once

namespace ai
{
    class RunawayStrategy : public NonCombatStrategy
       {
       public:
           RunawayStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
           virtual string getName() { return "runaway"; }
           virtual void InitTriggers(std::list<TriggerNode*> &triggers);
       };


}
