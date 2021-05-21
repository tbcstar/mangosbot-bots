#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"

namespace botAI
{
    class NearestFriendlyPlayersValue : public NearestUnitsValue
	{
	public:
        NearestFriendlyPlayersValue(PlayerbotAI* botAI) :
          NearestUnitsValue(botAI, "nearest friendly players", sPlayerbotAIConfig->sightDistance) { }

    protected:
        void FindUnits(list<Unit*> &targets);
        virtual bool AcceptUnit(Unit* unit);
	};
}
