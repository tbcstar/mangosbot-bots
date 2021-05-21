#pragma once
#include "../Value.h"

namespace botAI
{
    class LogLevelValue : public ManualSetValue<LogLevel>
	{
	public:
        LogLevelValue(PlayerbotAI* botAI) :
            ManualSetValue<LogLevel>(botAI, LOG_LVL_DEBUG) { }
	};
}
