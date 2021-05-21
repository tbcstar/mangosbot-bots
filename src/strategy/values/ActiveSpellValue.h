#pragma once
#include "../Value.h"

namespace botAI
{
    class ActiveSpellValue : public CalculatedValue<uint32>
	{
	public:
        ActiveSpellValue() : CalculatedValue<uint32>(botAI) { }

        virtual uint32 Calculate();
    };
}
