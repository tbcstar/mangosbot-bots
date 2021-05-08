#pragma once

namespace ai
{
    class LootNonCombatStrategy : public Strategy
    {
    public:
        LootNonCombatStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "loot"; }
    };

    class GatherStrategy : public Strategy
    {
    public:
        GatherStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "gather"; }
    };

    class RevealStrategy : public Strategy
    {
    public:
        RevealStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "reveal"; }
    };
}
