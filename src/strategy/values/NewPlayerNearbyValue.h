#pragma once
#include "../Value.h"

namespace botAI
{
    class NewPlayerNearbyValue : public CalculatedValue<ObjectGuid>
	{
	public:
        NewPlayerNearbyValue(PlayerbotAI* botAI) : CalculatedValue<ObjectGuid>(botAI, "new player nearby") { }
        virtual ObjectGuid Calculate();
    };

    class AlreadySeenPlayersValue : public ManualSetValue<set<ObjectGuid>& >
	{
	public:
        AlreadySeenPlayersValue(PlayerbotAI* botAI) : ManualSetValue<set<ObjectGuid>& >(botAI, data, "already seen players") { }

    private:
        set<ObjectGuid> data;
    };
}
