#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class CcTargetValue : public TargetValue, public Qualified
	{
	public:
        CcTargetValue(PlayerbotAI* botAI) : TargetValue(botAI) {}

    public:
        Unit* Calculate();
    };
}
