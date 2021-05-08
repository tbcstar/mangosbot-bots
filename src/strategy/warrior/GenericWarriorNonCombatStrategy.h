#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericWarriorNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericWarriorNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "nc"; }
   };
}