#pragma once
#include "../Value.h"

namespace ai
{
    class LogLevelValue : public ManualSetValue<LogLevel>
	{
	public:
        LogLevelValue(PlayerbotAI* botAI) :
            ManualSetValue<LogLevel>(ai, LOG_LVL_DEBUG) {}
	};
}
