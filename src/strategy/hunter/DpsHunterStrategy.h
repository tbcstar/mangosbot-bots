#pragma once

#include "GenericHunterStrategy.h"
#include "../generic/CombatStrategy.h"

namespace ai
{
    class DpsHunterStrategy : public GenericHunterStrategy
    {
    public:
        DpsHunterStrategy(PlayerbotAI* botAI);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "dps"; }
        virtual NextAction** getDefaultActions();

    };

    class DpsAoeHunterStrategy : public CombatStrategy
    {
    public:
        DpsAoeHunterStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "aoe"; }
    };

    class DpsHunterDebuffStrategy : public CombatStrategy
    {
    public:
        DpsHunterDebuffStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "dps debuff"; }
    };
}
