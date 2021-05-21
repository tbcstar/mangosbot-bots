#pragma once

#include "GenericPaladinStrategy.h"

namespace botAI
{
    class HealPaladinStrategy : public GenericPaladinStrategy
    {
    public:
        HealPaladinStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "heal"; }
        NextAction** getDefaultActions() override;
		uint32 GetType() const override { return STRATEGY_TYPE_HEAL | STRATEGY_TYPE_MELEE; }
    };
}
