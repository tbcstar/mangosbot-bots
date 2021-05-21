#pragma once

#include "../Strategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class DpsRogueStrategy : public CombatStrategy
    {
    public:
        DpsRogueStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "dps"; }
        NextAction** getDefaultActions() override;
    };

    class RogueAoeStrategy : public Strategy
    {
    public:
        RogueAoeStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "aoe"; }
    };

    class RogueBoostStrategy : public Strategy
    {
    public:
        RogueBoostStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "boost"; }
    };
}
