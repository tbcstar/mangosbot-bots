#pragma once

#include "HealPriestStrategy.h"

namespace botAI
{
    class ShadowPriestStrategy : public GenericPriestStrategy
    {
    public:
        ShadowPriestStrategy(PlayerbotAI* botAI);

    public:
        NextAction** getDefaultActions() override;
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "shadow"; }
        uint32 GetType() const override { return STRATEGY_TYPE_DPS|STRATEGY_TYPE_RANGED; }
    };

    class ShadowPriestAoeStrategy : public CombatStrategy
    {
    public:
        ShadowPriestAoeStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "shadow aoe"; }
    };

    class ShadowPriestDebuffStrategy : public CombatStrategy
    {
    public:
        ShadowPriestDebuffStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "shadow debuff"; }
    };
}
