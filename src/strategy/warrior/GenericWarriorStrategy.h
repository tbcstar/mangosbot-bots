#pragma once

#include "../Strategy.h"
#include "../generic/CombatStrategy.h"

namespace botAI
{
    class AiObjectContext;

    class GenericWarriorStrategy : public CombatStrategy
    {
    public:
        GenericWarriorStrategy(PlayerbotAI* botAI);

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "warrior"; }
    };
}
