#pragma once
#include "../Value.h"
#include "RtiTargetValue.h"
#include "TargetValue.h"

namespace botAI
{
    class DpsTargetValue : public RtiTargetValue
	{
	public:
        DpsTargetValue(PlayerbotAI* botAI) : RtiTargetValue(botAI) { }

    public:
        Unit* Calculate();
    };

    class DpsAoeTargetValue : public RtiTargetValue
	{
	public:
        DpsAoeTargetValue(PlayerbotAI* botAI) : RtiTargetValue(botAI) { }

    public:
        Unit* Calculate();
    };
}
