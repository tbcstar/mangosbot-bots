#pragma once

#include "GenericShamanStrategy.h"
#include "MeleeShamanStrategy.h"

namespace botAI
{
    class CasterShamanStrategy : public GenericShamanStrategy
    {
    public:
        CasterShamanStrategy();

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        NextAction** getDefaultActions() override;
        std::string const& getName() override { return "caster"; }
        uint32 GetType() const override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
    };

    class CasterAoeShamanStrategy : public CombatStrategy
    {
    public:
        CasterAoeShamanStrategy() : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "caster aoe"; }
    };
}
