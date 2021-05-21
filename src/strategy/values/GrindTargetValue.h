#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace botAI
{
   
    class GrindTargetValue : public TargetValue
	{
	public:
        GrindTargetValue(PlayerbotAI* botAI) : TargetValue(botAI) { }

    public:
        Unit* Calculate();

    private:
        int GetTargetingPlayerCount(Unit* unit);
        Unit* FindTargetForGrinding(int assistCount);
    };
}
