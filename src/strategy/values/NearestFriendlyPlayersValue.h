/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NearestUnitsValue.h"
#include "PlayerbotAIConfig.h"

class PlayerbotAI;

class NearestFriendlyPlayersValue : public NearestUnitsValue
{
	public:
        NearestFriendlyPlayersValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) :
            NearestUnitsValue(botAI, "nearest friendly players", range) { }

    protected:
        void FindUnits(std::list<Unit*> &targets) override;
        bool AcceptUnit(Unit* unit) override;
};