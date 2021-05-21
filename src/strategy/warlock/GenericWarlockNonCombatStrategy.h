#pragma once

#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class GenericWarlockNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericWarlockNonCombatStrategy(PlayerbotAI* botAI);
        std::string const& getName() override { return "nc"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

    class WarlockPetStrategy : public Strategy
    {
    public:
        WarlockPetStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }
        std::string const& getName() override { return "pet"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };
}
