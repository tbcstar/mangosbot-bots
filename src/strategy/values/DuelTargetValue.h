#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace botAI
{
    class DuelTargetValue : public TargetValue
	{
	public:
        DuelTargetValue(PlayerbotAI* botAI) : TargetValue(botAI) { }

    public:
        Unit* Calculate();
    };
}
