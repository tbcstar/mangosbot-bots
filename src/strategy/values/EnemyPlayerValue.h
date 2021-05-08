#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{
    class EnemyPlayerValue : public TargetValue
	{
	public:
        EnemyPlayerValue(PlayerbotAI* botAI) : TargetValue(botAI) {}

    public:
        Unit* Calculate();
    };
}
