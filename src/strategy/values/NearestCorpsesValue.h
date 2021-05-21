#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"

namespace botAI
{
    class NearestCorpsesValue : public NearestUnitsValue
	{
	public:
        NearestCorpsesValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) :
          NearestUnitsValue(botAI, "nearest corpses", range) { }

    protected:
        void FindUnits(list<Unit*> &targets);
        bool AcceptUnit(Unit* unit);

	};
}
