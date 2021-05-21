#pragma once

#include "../Strategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class GenericMageStrategy : public CombatStrategy
    {
    public:
        GenericMageStrategy(PlayerbotAI* botAI);
        std::string const& getName() override { return "mage"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

    class MageCureStrategy : public Strategy
    {
    public:
        MageCureStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "cure"; }
    };

    class MageBoostStrategy : public Strategy
    {
    public:
        MageBoostStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "boost"; }
    };

    class MageCcStrategy : public Strategy
    {
    public:
        MageCcStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "cc"; }
    };
}
