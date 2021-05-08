#pragma once

namespace ai
{
    class SayStrategy : public Strategy
    {
    public:
        SayStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "say"; }
    };


}
