#pragma once

#include "../Strategy.h"
#include "PaladinAiObjectContext.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class GenericPaladinStrategy : public CombatStrategy
    {
    public:
        GenericPaladinStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "paladin"; }
    };

    class PaladinCureStrategy : public Strategy
    {
    public:
        PaladinCureStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "cure"; }
    };

    class PaladinBoostStrategy : public Strategy
    {
    public:
        PaladinBoostStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "boost"; }
    };

    class PaladinCcStrategy : public Strategy
    {
    public:
        PaladinCcStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "cc"; }
    };
}
