#include "../generic/NonCombatStrategy.h"
#pragma once

namespace ai
{
    class AttackEnemyPlayersStrategy : public NonCombatStrategy
    {
    public:
        AttackEnemyPlayersStrategy() : NonCombatStrategy(botAI) {}
        virtual string getName() { return "pvp"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

}
