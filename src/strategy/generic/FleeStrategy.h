#pragma once

namespace ai
{
    class FleeStrategy : public Strategy
    {
    public:
        FleeStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "flee"; };
    };

    class FleeFromAddsStrategy : public Strategy
    {
    public:
        FleeFromAddsStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "flee from adds"; };
    };

}
