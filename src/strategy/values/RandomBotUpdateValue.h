#pragma once
#include "../Value.h"

namespace botAI
{
    class RandomBotUpdateValue : public ManualSetValue<bool>
	{
	public:
        RandomBotUpdateValue(PlayerbotAI* botAI) : ManualSetValue<bool>(botAI, false) { }
    };
}
