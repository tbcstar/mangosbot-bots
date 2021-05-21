#pragma once

#include "GenericWarriorStrategy.h"

namespace botAI
{
    class DpsWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        DpsWarriorStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "dps"; }
        NextAction** getDefaultActions() override;
        uint32 GetType() const override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
    };

    class DpsWarrirorAoeStrategy : public CombatStrategy
    {
    public:
        DpsWarrirorAoeStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "aoe"; }
    };
}
