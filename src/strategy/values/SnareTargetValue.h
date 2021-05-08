#pragma once
#include "../Value.h"

namespace ai
{
    class SnareTargetValue : public UnitCalculatedValue, public Qualified
	{
	public:
        SnareTargetValue(PlayerbotAI* botAI) :
            UnitCalculatedValue(ai, "snare target") {}

    protected:
        virtual Unit* Calculate();
	};
}
