#pragma once
#include "../Value.h"

namespace botAI
{
    class FindTargetStrategy
    {
    public:
        FindTargetStrategy(PlayerbotAI* botAI)
        {
            result = nullptr;
            this->botAI = botAI;
        }

    public:
        Unit* GetResult() { return result; }

    public:
        virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager) = 0;
        void GetPlayerCount(Unit* creature, int* tankCount, int* dpsCount);

    protected:
        Unit* result;
        PlayerbotAI* botAI;

    protected:
        map<Unit*, int> tankCountCache;
        map<Unit*, int> dpsCountCache;
    };

    class FindNonCcTargetStrategy : public FindTargetStrategy
    {
    public:
        FindNonCcTargetStrategy(PlayerbotAI* botAI) : FindTargetStrategy(botAI) { }

    protected:
        virtual bool IsCcTarget(Unit* attacker);

    };

    class TargetValue : public UnitCalculatedValue
	{
	public:
        TargetValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI) { }

    protected:
        Unit* FindTarget(FindTargetStrategy* strategy);
    };

    class RpgTargetValue : public ManualSetValue<ObjectGuid>
    {
    public:
        RpgTargetValue(PlayerbotAI* botAI) : ManualSetValue<ObjectGuid>(botAI, ObjectGuid::Empty) { }
    };

    class TalkTargetValue : public ManualSetValue<ObjectGuid>
    {
    public:
        TalkTargetValue(PlayerbotAI* botAI) : ManualSetValue<ObjectGuid>(botAI, ObjectGuid::Empty) { }
    };

    class PullTargetValue : public ManualSetValue<ObjectGuid>
    {
    public:
        PullTargetValue(PlayerbotAI* botAI) : ManualSetValue<ObjectGuid>(botAI, ObjectGuid::Empty) { }
    };
}
