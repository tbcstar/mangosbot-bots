#pragma once
#include "../Value.h"

namespace botAI
{
    class LastSaidValue : public ManualSetValue<time_t>, public Qualified
	{
	public:
        LastSaidValue(PlayerbotAI* botAI) : ManualSetValue<time_t>(botAI, time(0) - 120, "last said") { }
    };

    class LastEmoteValue : public ManualSetValue<time_t>, public Qualified
	{
	public:
        LastEmoteValue(PlayerbotAI* botAI) : ManualSetValue<time_t>(botAI, time(0) - 120, "last emote") { }
    };
}
