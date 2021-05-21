#pragma once

#include "GenericShamanStrategy.h"

namespace botAI
{
    class HealShamanStrategy : public GenericShamanStrategy
    {
    public:
        HealShamanStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "heal"; }
		uint32 GetType() const override { return STRATEGY_TYPE_HEAL; }
    };
}
