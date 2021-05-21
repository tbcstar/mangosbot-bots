#pragma once
#include "../Value.h"

namespace botAI
{
    class ThreatValue : public Uint8CalculatedValue, public Qualified
	{
	public:
        ThreatValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

    public:
    	virtual uint8 Calculate();

    protected:
    	uint8 Calculate(Unit* target);
    };
}
