#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class TankTargetValue : public TargetValue
	{
	public:
        TankTargetValue(PlayerbotAI* botAI) : TargetValue(botAI) {}

    public:
        Unit* Calculate();
    };
}
