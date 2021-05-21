#pragma once

#include "GenericWarriorStrategy.h"

namespace botAI
{
    class TankWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        TankWarriorStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "tank"; }
        NextAction** getDefaultActions() override;
        uint32 GetType() const override { return STRATEGY_TYPE_TANK | STRATEGY_TYPE_MELEE; }
    };
}
