#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class CurrentCcTargetValue : public TargetValue, public Qualified
	{
	public:
        CurrentCcTargetValue(PlayerbotAI* botAI) : TargetValue(botAI) {}

    public:
        Unit* Calculate();
    };
}
