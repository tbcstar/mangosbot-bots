#pragma once

#include "GenericWarlockStrategy.h"

namespace botAI
{
    class TankWarlockStrategy : public GenericWarlockStrategy
    {
    public:
        TankWarlockStrategy(PlayerbotAI* botAI);
        std::string const& getName() override { return "tank"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        NextAction** getDefaultActions() override;
    };
}
