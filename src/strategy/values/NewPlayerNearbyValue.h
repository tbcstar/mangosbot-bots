/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Value.h"
class NewPlayerNearbyValue : public CalculatedValue<ObjectGuid>
{
	public:
        NewPlayerNearbyValue(PlayerbotAI* botAI) : CalculatedValue<ObjectGuid>(botAI, "new player nearby") { }

        ObjectGuid Calculate() override;
};

class AlreadySeenPlayersValue : public ManualSetValue<std::set<ObjectGuid>& >
{
	public:
        AlreadySeenPlayersValue(PlayerbotAI* botAI) : ManualSetValue<std::set<ObjectGuid>& >(botAI, data, "already seen players") { }

        GuidSet data;
};
