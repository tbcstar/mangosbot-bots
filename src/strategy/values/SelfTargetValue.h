#pragma once
#include "../Value.h"

namespace ai
{
    class SelfTargetValue : public UnitCalculatedValue
	{
	public:
        SelfTargetValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI) {}

        virtual Unit* Calculate() { return botAI->GetBot(); }
    };
}
