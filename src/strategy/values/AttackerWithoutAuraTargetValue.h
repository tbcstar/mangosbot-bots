#pragma once
#include "../Value.h"

namespace ai
{
    class AttackerWithoutAuraTargetValue : public UnitCalculatedValue, public Qualified
	{
	public:
        AttackerWithoutAuraTargetValue() :
            UnitCalculatedValue(ai, "attacker without aura") {}

    protected:
        virtual Unit* Calculate();
	};
}
