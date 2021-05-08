#pragma once

namespace ai
{

    class CastTimeMultiplier : public Multiplier
    {
    public:
        CastTimeMultiplier(PlayerbotAI* botAI) : Multiplier(ai, "cast time") {}

    public:
        virtual float GetValue(Action* action);
    };

    class CastTimeStrategy : public Strategy
    {
    public:
        CastTimeStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "cast time"; }
    };


}
