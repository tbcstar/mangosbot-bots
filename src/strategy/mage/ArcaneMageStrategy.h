#pragma once

#include "GenericMageStrategy.h"

namespace botAI
{
    class ArcaneMageStrategy : public GenericMageStrategy
    {
    public:
        ArcaneMageStrategy();

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "arcane"; }
        NextAction** getDefaultActions() override;
    };

}
