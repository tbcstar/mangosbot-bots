#pragma once

#include "HealPriestStrategy.h"

namespace botAI
{
    class HolyPriestStrategy : public HealPriestStrategy
    {
    public:
        HolyPriestStrategy(PlayerbotAI* botAI);

    public:
        NextAction** getDefaultActions() override;
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "holy"; }
        uint32 GetType() const override { return STRATEGY_TYPE_DPS|STRATEGY_TYPE_RANGED; }
    };
}
