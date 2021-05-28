/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Unit.h"
#include "../Value.h"

class PlayerbotAI;
class ThreatManager;

class FindTargetStrategy
{
    public:
        FindTargetStrategy(PlayerbotAI* botAI) : result(nullptr), botAI(botAI) { }

        Unit* GetResult();
        virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager) = 0;
        void GetPlayerCount(Unit* creature, uint32* tankCount, uint32* dpsCount);

    protected:
        Unit* result;
        PlayerbotAI* botAI;
        std::map<Unit*, uint32> tankCountCache;
        std::map<Unit*, uint32> dpsCountCache;
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
