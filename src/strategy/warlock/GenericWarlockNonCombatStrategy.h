#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericWarlockNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericWarlockNonCombatStrategy(PlayerbotAI* botAI);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class WarlockPetStrategy : public Strategy
    {
    public:
        WarlockPetStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}
        virtual string getName() { return "pet"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
