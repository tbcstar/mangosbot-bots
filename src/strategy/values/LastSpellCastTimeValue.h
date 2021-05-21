#pragma once
#include "../Value.h"

namespace botAI
{
    class LastSpellCastTimeValue : public ManualSetValue<time_t>, public Qualified
	{
	public:
        LastSpellCastTimeValue(PlayerbotAI* botAI) : ManualSetValue<time_t>(botAI, 0), Qualified() { }
    };
}
