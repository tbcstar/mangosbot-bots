#pragma once

#include "../Strategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class GenericPriestStrategy : public CombatStrategy
    {
    public:
        GenericPriestStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;

    };

    class PriestCureStrategy : public Strategy
    {
    public:
        PriestCureStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "cure"; }
    };

    class PriestBoostStrategy : public Strategy
    {
    public:
        PriestBoostStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "boost"; }
    };

    class PriestCcStrategy : public Strategy
    {
    public:
        PriestCcStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "cc"; }
    };
}
