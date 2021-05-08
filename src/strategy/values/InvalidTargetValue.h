#pragma once
#include "../Value.h"

namespace ai
{
    class InvalidTargetValue : public BoolCalculatedValue, public Qualified
	{
	public:
        InvalidTargetValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) {}

	public:
        virtual bool Calculate();
    };
}
