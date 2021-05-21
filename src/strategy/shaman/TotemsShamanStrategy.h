#pragma once

#include "GenericShamanStrategy.h"

namespace botAI
{
    class TotemsShamanStrategy : public GenericShamanStrategy
    {
    public:
        TotemsShamanStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "totems"; }
    };
}
