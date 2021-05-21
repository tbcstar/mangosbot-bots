#pragma once
#include "../Value.h"

namespace botAI
{
    class MasterTargetValue : public UnitCalculatedValue
	{
	public:
        MasterTargetValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI) { }

        virtual Unit* Calculate() { return botAI->GetMaster(); }
    };
}
