#pragma once

#include "../Strategy.h"
#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class PriestNonCombatStrategy : public NonCombatStrategy
    {
    public:
        PriestNonCombatStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "nc"; }
    };

    class PriestBuffStrategy : public NonCombatStrategy
    {
    public:
        PriestBuffStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "buff"; }
    };

    class PriestShadowResistanceStrategy : public NonCombatStrategy
    {
    public:
        PriestShadowResistanceStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "rshadow"; }
    };
}
