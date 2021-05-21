#pragma once

#include "GenericMageStrategy.h"
#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class GenericMageNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericMageNonCombatStrategy(PlayerbotAI* botAI);
        std::string const& getName() override { return "nc"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

    class MageBuffManaStrategy : public Strategy
    {
    public:
        MageBuffManaStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "bmana"; }
    };

    class MageBuffDpsStrategy : public Strategy
    {
    public:
        MageBuffDpsStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "bdps"; }
    };

    class MageBuffStrategy : public Strategy
    {
    public:
        MageBuffStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "buff"; }
    };
}
