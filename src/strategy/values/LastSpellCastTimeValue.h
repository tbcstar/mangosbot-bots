#pragma once
#include "../Value.h"

namespace ai
{
    class LastSpellCastTimeValue : public ManualSetValue<time_t>, public Qualified
	{
	public:
        LastSpellCastTimeValue(PlayerbotAI* botAI) : ManualSetValue<time_t>(ai, 0), Qualified() {}
    };
}
