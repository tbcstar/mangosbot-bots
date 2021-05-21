#pragma once

#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class GenericWarriorNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericWarriorNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }
        std::string const& getName() override { return "nc"; }
   };
}