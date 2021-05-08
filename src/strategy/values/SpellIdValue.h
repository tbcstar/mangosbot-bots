#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{

    class SpellIdValue : public CalculatedValue<uint32>, public Qualified
	{
	public:
        SpellIdValue(PlayerbotAI* botAI);

    public:
        virtual uint32 Calculate();

    };
}
