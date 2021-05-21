#pragma once
#include "../Value.h"
#include "../../PlayerbotAIConfig.h"
#include "../../ServerFacade.h"

namespace botAI
{
    class NearestUnitsValue : public ObjectGuidListCalculatedValue
	{
	public:
        NearestUnitsValue(PlayerbotAI* botAI, std::string const& name, float range = sPlayerbotAIConfig->sightDistance, bool ignoreLos = false) :
            ObjectGuidListCalculatedValue(botAI, name, 2), range(range), ignoreLos(ignoreLos) { }

	public:
        GuidVector Calculate()
        {
            list<Unit*> targets;
            FindUnits(targets);

            GuidVector results;
            for(list<Unit *>::iterator i = targets.begin(); i!= targets.end(); ++i)
            {
                Unit* unit = *i;
                if ((ignoreLos || sServerFacade->IsWithinLOSInMap(bot, unit)) && AcceptUnit(unit))
                    results.push_back(unit->GetGUID());
            }
            return results;
        }

    protected:
        virtual void FindUnits(list<Unit*> &targets) = 0;
        virtual bool AcceptUnit(Unit* unit) = 0;

    protected:
        float range;
        bool ignoreLos;
	};
}
