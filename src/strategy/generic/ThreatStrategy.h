#pragma once

namespace ai
{
    class ThreatMultiplier : public Multiplier
    {
    public:
        ThreatMultiplier(PlayerbotAI* botAI) : Multiplier(ai, "threat") {}

    public:
        virtual float GetValue(Action* action);
    };

    class ThreatStrategy : public Strategy
    {
    public:
        ThreatStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "threat"; }
    };


}
