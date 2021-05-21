#pragma once
#include "../Value.h"

namespace botAI
{
    class SnareTargetValue : public UnitCalculatedValue, public Qualified
	{
	public:
        SnareTargetValue(PlayerbotAI* botAI) :
            UnitCalculatedValue(botAI, "snare target") { }

    protected:
        virtual Unit* Calculate();
	};
}
