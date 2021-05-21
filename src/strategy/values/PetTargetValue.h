#pragma once
#include "../Value.h"

namespace botAI
{
    class PetTargetValue : public UnitCalculatedValue
	{
	public:
        PetTargetValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI) { }

        virtual Unit* Calculate() { return (Unit*)(botAI->GetBot()->GetPet()); }
    };
}
