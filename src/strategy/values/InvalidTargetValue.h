#pragma once
#include "../Value.h"

namespace botAI
{
    class InvalidTargetValue : public BoolCalculatedValue, public Qualified
	{
	public:
        InvalidTargetValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

	public:
        virtual bool Calculate();
    };
}
