#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"
#include "PossibleTargetsValue.h"

namespace botAI
{
    class NearestAdsValue : public PossibleTargetsValue
	{
	public:
        NearestAdsValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->tooCloseDistance) :
            PossibleTargetsValue(botAI, "nearest ads", range) { }

    protected:
        bool AcceptUnit(Unit* unit);
	};
}
