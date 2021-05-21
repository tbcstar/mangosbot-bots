#pragma once

#include "../Strategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class GenericWarlockStrategy : public CombatStrategy
    {
    public:
        GenericWarlockStrategy(PlayerbotAI* botAI);
        std::string const& getName() override { return "warlock"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        NextAction** getDefaultActions() override;
    };

    class WarlockBoostStrategy : public Strategy
    {
    public:
        WarlockBoostStrategy(PlayerbotAI* botAI) : Strategy(botAI) { };
        std::string const& getName() override { return "boost"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

    class WarlockCcStrategy : public Strategy
    {
    public:
        WarlockCcStrategy(PlayerbotAI* botAI) : Strategy(botAI) { };
        std::string const& getName() override { return "cc"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };
}
