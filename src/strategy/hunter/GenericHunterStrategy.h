#pragma once

#include "../Strategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class AiObjectContext;

    class GenericHunterStrategy : public CombatStrategy
    {
    public:
        GenericHunterStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "hunter"; }
    };

    class HunterBoostStrategy : public Strategy
    {
    public:
        HunterBoostStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }
        std::string const& getName() override { return "boost"; }
        NextAction** getDefaultActions() override;

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

    class HunterCcStrategy : public Strategy
    {
    public:
        HunterCcStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "cc"; }
    };
}

