#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"

namespace botAI
{
    class PartyMemberToDispel : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberToDispel(PlayerbotAI* botAI) :
          PartyMemberValue(botAI), Qualified() { }

    protected:
        virtual Unit* Calculate();
	};
}
