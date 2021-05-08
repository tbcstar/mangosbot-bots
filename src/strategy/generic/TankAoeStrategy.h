#include "../generic/NonCombatStrategy.h"
#pragma once

namespace ai
{
    class TankAoeStrategy : public NonCombatStrategy
    {
    public:
        TankAoeStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "tank aoe"; }
        virtual int GetType() { return STRATEGY_TYPE_TANK; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };


}
