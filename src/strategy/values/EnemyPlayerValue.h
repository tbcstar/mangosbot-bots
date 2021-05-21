#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace botAI
{
    class EnemyPlayerValue : public TargetValue
	{
	public:
        EnemyPlayerValue(PlayerbotAI* botAI) : TargetValue(botAI) { }

    public:
        Unit* Calculate();
    };
}
