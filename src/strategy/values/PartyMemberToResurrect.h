#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    class PartyMemberToResurrect : public PartyMemberValue
	{
	public:
        PartyMemberToResurrect(PlayerbotAI* botAI) : 
          PartyMemberValue(botAI) {}
    
    protected:
        virtual Unit* Calculate();
	};
}
