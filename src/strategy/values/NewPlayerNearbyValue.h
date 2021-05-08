#pragma once
#include "../Value.h"

namespace ai
{
    class NewPlayerNearbyValue : public CalculatedValue<ObjectGuid>
	{
	public:
        NewPlayerNearbyValue(PlayerbotAI* botAI) : CalculatedValue<ObjectGuid>(ai, "new player nearby") {}
        virtual ObjectGuid Calculate();
    };

    class AlreadySeenPlayersValue : public ManualSetValue<set<ObjectGuid>& >
	{
	public:
        AlreadySeenPlayersValue(PlayerbotAI* botAI) : ManualSetValue<set<ObjectGuid>& >(ai, data, "already seen players") {}

    private:
        set<ObjectGuid> data;
    };
}
