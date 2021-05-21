#pragma once

#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class GenericHunterNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericHunterNonCombatStrategy(PlayerbotAI* botAI);
        std::string const& getName() override { return "nc"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

    class HunterPetStrategy : public Strategy
    {
    public:
        HunterPetStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }
        std::string const& getName() override { return "pet"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

}
