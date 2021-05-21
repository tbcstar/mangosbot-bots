#pragma once

#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class GenericPaladinNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericPaladinNonCombatStrategy(PlayerbotAI* botAI);
        std::string const& getName() override { return "nc"; }
    
    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
   };
}
