#pragma once
#include "../Value.h"
#include "TargetValue.h"
#include "../../LootObjectStack.h"

namespace botAI
{
    class HasTotemValue : public BoolCalculatedValue, public Qualified
	{
	public:
        HasTotemValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

    public:
        bool Calculate()
        {
            GuidVector units = *context->GetValue<GuidVector >("nearest npcs");
            for (GuidVector::iterator i = units.begin(); i != units.end(); i++)
            {
                Unit* unit = botAI->GetUnit(*i);
                if (!unit)
                    continue;

                Creature* creature = dynamic_cast<Creature*>(unit);
                if (!creature || !creature->IsTotem())
                    continue;

                if (strstri(creature->GetName(), qualifier.c_str()) && bot->GetDistance(creature) <= botAI->GetRange("spell"))
                    return true;
            }

            return false;
        }
    };
}
