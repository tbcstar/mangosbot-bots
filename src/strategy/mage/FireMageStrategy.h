#pragma once

#include "GenericMageStrategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class FireMageStrategy : public GenericMageStrategy
    {
    public:
        FireMageStrategy(PlayerbotAI* botAI) : GenericMageStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "fire"; }
        NextAction** getDefaultActions() override;
    };

    class FireMageAoeStrategy : public CombatStrategy
    {
    public:
        FireMageAoeStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "fire aoe"; }
    };
}
