#pragma once
#include "../Value.h"

namespace ai
{
    class ActiveSpellValue : public CalculatedValue<uint32>
	{
	public:
        ActiveSpellValue(PlayerbotAI* botAI) : CalculatedValue<uint32>(botAI) {}

        virtual uint32 Calculate();
    };
}
