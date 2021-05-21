#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"
#include "../../PlayerbotAIConfig.h"

namespace botAI
{
    class PartyMemberWithoutAuraValue : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberWithoutAuraValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) :
          PartyMemberValue(botAI) { }

    protected:
        virtual Unit* Calculate();
	};
}
