#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"

namespace botAI
{
    class PartyMemberToHeal : public PartyMemberValue
	{
	public:
        PartyMemberToHeal(PlayerbotAI* botAI) :
          PartyMemberValue(botAI) { }

    protected:
        virtual Unit* Calculate();
        bool CanHealPet(Pet* pet);
        virtual bool Check(Unit* player);
	};
}
