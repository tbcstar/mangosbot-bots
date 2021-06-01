/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Value.h"

class ObjectGuid;
class PlayerbotAI;
class Unit;

class LastMovement
{
    public:
        LastMovement() : lastMoveToX(0.f), lastMoveToY(0.f), lastMoveToZ(0.f), lastMoveToOri(0.f), lastFollow(nullptr) { }
        LastMovement(LastMovement& other) : taxiNodes(other.taxiNodes), taxiMaster(other.taxiMaster), lastFollow(other.lastFollow), lastAreaTrigger(other.lastAreaTrigger),
            lastMoveToX(other.lastMoveToX), lastMoveToY(other.lastMoveToY), lastMoveToZ(other.lastMoveToZ), lastMoveToOri(other.lastMoveToOri) { }

        void Set(Unit* follow);
        void Set(float x, float y, float z, float ori);

        std::vector<uint32> taxiNodes;
        ObjectGuid taxiMaster;
        Unit* lastFollow;
        uint32 lastAreaTrigger;
        float lastMoveToX;
        float lastMoveToY;
        float lastMoveToZ;
        float lastMoveToOri;
};

class LastMovementValue : public ManualSetValue<LastMovement&>
{
	public:
        LastMovementValue(PlayerbotAI* botAI) : ManualSetValue<LastMovement&>(botAI, data) { }

    private:
        LastMovement data;
};

class StayTimeValue : public ManualSetValue<time_t>
{
	public:
        StayTimeValue(PlayerbotAI* botAI) : ManualSetValue<time_t>(botAI, 0) { }
};
