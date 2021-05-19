#pragma once
#include "../Value.h"

namespace ai
{
    class AoeHealValue : public Uint8CalculatedValue, public Qualified
	{
	public:
    	AoeHealValue() : Uint8CalculatedValue(botAI) {}

    public:
    	virtual uint8 Calculate();
    };
}
