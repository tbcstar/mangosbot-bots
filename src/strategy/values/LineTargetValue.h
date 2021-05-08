#pragma once
#include "../Value.h"

namespace ai
{
    class LineTargetValue : public UnitCalculatedValue
	{
	public:
        LineTargetValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI) {}

    public:
        virtual Unit* Calculate();
	};
}
