#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace botAI
{
    class LeastHpTargetValue : public TargetValue
	{
	public:
        LeastHpTargetValue(PlayerbotAI* botAI) : TargetValue(botAI) { }

    public:
        Unit* Calculate();
    };
}
