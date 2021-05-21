#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"

namespace botAI
{
    class NearestNonBotPlayersValue : public NearestUnitsValue
	{
	public:
        NearestNonBotPlayersValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->grindDistance) :
          NearestUnitsValue(botAI, "nearest non bot players", range, true) { }

    protected:
        void FindUnits(list<Unit*> &targets);
        bool AcceptUnit(Unit* unit);
	};
}
