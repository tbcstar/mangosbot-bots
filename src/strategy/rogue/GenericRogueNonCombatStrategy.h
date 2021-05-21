#pragma once

#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class GenericRogueNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericRogueNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }
        std::string const& getName() override { return "nc"; }
    
    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };
}