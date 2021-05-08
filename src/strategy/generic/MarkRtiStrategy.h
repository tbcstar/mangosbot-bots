#pragma once

namespace ai
{
    class MarkRtiStrategy : public Strategy
    {
    public:
        MarkRtiStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}
        virtual string getName() { return "mark rti"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

}
