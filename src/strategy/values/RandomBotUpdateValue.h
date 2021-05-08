#pragma once
#include "../Value.h"

namespace ai
{
    class RandomBotUpdateValue : public ManualSetValue<bool>
	{
	public:
        RandomBotUpdateValue(PlayerbotAI* botAI) : ManualSetValue<bool>(ai, false) {}
    };
}
