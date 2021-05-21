#pragma once

#include "GenericMageStrategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class FrostMageStrategy : public GenericMageStrategy
    {
    public:
        FrostMageStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "frost"; }
        NextAction** getDefaultActions() override;
    };

    class FrostMageAoeStrategy : public CombatStrategy
    {
    public:
        FrostMageAoeStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "frost aoe"; }
    };
}
