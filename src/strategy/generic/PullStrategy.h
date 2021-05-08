#pragma once

#include "CombatStrategy.h"

namespace ai
{
    class PullStrategy : public CombatStrategy
    {
    public:
        PullStrategy(PlayerbotAI* botAI, string action) : CombatStrategy(botAI)
        {
            this->action = action;
        }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "pull"; }
        virtual NextAction** getDefaultActions();

    private:
        string action;
    };

    class PossibleAdsStrategy : public Strategy
    {
    public:
        PossibleAdsStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "ads"; }
    };
}
