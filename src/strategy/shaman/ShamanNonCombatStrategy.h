#pragma once

#include "../Strategy.h"
#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class ShamanNonCombatStrategy : public NonCombatStrategy
    {
    public:
        ShamanNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        void InitMultipliers(std::vector<Multiplier*>& multipliers) override;
        std::string const& getName() override { return "nc"; }

    };
}
