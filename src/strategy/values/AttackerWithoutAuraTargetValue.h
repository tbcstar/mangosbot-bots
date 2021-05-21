#pragma once
#include "../Value.h"

namespace botAI
{
    class AttackerWithoutAuraTargetValue : public UnitCalculatedValue, public Qualified
	{
	public:
        AttackerWithoutAuraTargetValue() :
            UnitCalculatedValue(botAI, "attacker without aura") { }

    protected:
        virtual Unit* Calculate();
	};
}
