#pragma once

#include "GenericShamanStrategy.h"

namespace botAI
{
    class MeleeShamanStrategy : public GenericShamanStrategy
    {
    public:
        MeleeShamanStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        NextAction** getDefaultActions() override;
        std::string const& getName() override { return "melee"; }
        uint32 GetType() const override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
    };

    class MeleeAoeShamanStrategy : public CombatStrategy
    {
    public:
        MeleeAoeShamanStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "melee aoe"; }
    };
}
