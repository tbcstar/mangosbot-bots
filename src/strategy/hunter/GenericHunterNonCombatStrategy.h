#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericHunterNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericHunterNonCombatStrategy(PlayerbotAI* botAI);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class HunterPetStrategy : public Strategy
    {
    public:
        HunterPetStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}
        virtual string getName() { return "pet"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

}
