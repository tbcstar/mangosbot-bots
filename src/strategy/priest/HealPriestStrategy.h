#pragma once

#include "GenericPriestStrategy.h"

namespace botAI
{
    class HealPriestStrategy : public GenericPriestStrategy
    {
    public:
        HealPriestStrategy(PlayerbotAI* botAI) : GenericPriestStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        NextAction** getDefaultActions() override;
        std::string const& getName() override { return "heal"; }
		uint32 GetType() const override { return STRATEGY_TYPE_HEAL; }
    };
}
