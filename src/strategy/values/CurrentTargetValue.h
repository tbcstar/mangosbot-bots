#pragma once
#include "../Value.h"

namespace botAI
{
    class CurrentTargetValue : public UnitManualSetValue
	{
	public:
        CurrentTargetValue(PlayerbotAI* botAI) : UnitManualSetValue(botAI, nullptr) { }

        virtual Unit* Get();
        virtual void Set(Unit* unit);

    private:
        ObjectGuid selection;
    };
}
