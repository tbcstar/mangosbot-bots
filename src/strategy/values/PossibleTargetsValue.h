#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"

namespace botAI
{
    class PossibleTargetsValue : public NearestUnitsValue
	{
	public:
        PossibleTargetsValue(PlayerbotAI* botAI, std::string const& name = "possible targets", float range = sPlayerbotAIConfig->sightDistance, bool ignoreLos = false) :
          NearestUnitsValue(botAI, name, range, ignoreLos) { }

    protected:
        virtual void FindUnits(list<Unit*> &targets);
        virtual bool AcceptUnit(Unit* unit);

	};

    class AllTargetsValue : public PossibleTargetsValue
	{
	public:
        AllTargetsValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) :
            PossibleTargetsValue(botAI, "all targets", range, true) { }
	};
}
