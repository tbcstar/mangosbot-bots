#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"

namespace botAI
{
    class NearestNpcsValue : public NearestUnitsValue
	{
	public:
        NearestNpcsValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) :
          NearestUnitsValue(botAI, "nearest npcs", range) { }

    protected:
        void FindUnits(list<Unit*> &targets);
        bool AcceptUnit(Unit* unit);
	};
}
