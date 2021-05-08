#pragma once

namespace ai
{
    class PassiveStrategy : public Strategy
    {
    public:
        PassiveStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "passive"; }
    };


}
