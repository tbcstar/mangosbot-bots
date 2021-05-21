#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"

namespace botAI
{
    class PartyMemberToResurrect : public PartyMemberValue
	{
	public:
        PartyMemberToResurrect(PlayerbotAI* botAI) : 
          PartyMemberValue(botAI) { }
    
    protected:
        virtual Unit* Calculate();
	};
}
