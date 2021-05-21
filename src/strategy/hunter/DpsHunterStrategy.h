#pragma once

#include "GenericHunterStrategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class DpsHunterStrategy : public GenericHunterStrategy
    {
    public:
        DpsHunterStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "dps"; }
        NextAction** getDefaultActions() override;

    };

    class DpsAoeHunterStrategy : public CombatStrategy
    {
    public:
        DpsAoeHunterStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "aoe"; }
    };

    class DpsHunterDebuffStrategy : public CombatStrategy
    {
    public:
        DpsHunterDebuffStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "dps debuff"; }
    };
}
