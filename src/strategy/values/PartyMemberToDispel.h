#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    class PartyMemberToDispel : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberToDispel(PlayerbotAI* botAI) :
          PartyMemberValue(botAI), Qualified() {}

    protected:
        virtual Unit* Calculate();
	};
}
