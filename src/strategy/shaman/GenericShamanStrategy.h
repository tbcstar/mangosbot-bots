#pragma once

#include "../Strategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class GenericShamanStrategy : public CombatStrategy
    {
    public:
        GenericShamanStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;

    };

    class ShamanBuffDpsStrategy : public Strategy
    {
    public:
        ShamanBuffDpsStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "bdps"; }

    };

    class ShamanBuffManaStrategy : public Strategy
    {
    public:
        ShamanBuffManaStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "bmana"; }

    };

    class ShamanCureStrategy : public Strategy
    {
    public:
        ShamanCureStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "cure"; }

    };
}
