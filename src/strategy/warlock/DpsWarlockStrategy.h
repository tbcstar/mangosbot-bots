#pragma once

#include "GenericWarlockStrategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class DpsWarlockStrategy : public GenericWarlockStrategy
    {
    public:
        DpsWarlockStrategy(PlayerbotAI* botAI);
        std::string const& getName() override { return "dps"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        NextAction** getDefaultActions() override;
    };

    class DpsAoeWarlockStrategy : public CombatStrategy
    {
    public:
        DpsAoeWarlockStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "aoe"; }
    };

    class DpsWarlockDebuffStrategy : public CombatStrategy
    {
    public:
        DpsWarlockDebuffStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "dps debuff"; }
    };

}
