#pragma once
#include "../Value.h"

namespace ai
{
    class PetTargetValue : public UnitCalculatedValue
	{
	public:
        PetTargetValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI) {}

        virtual Unit* Calculate() { return (Unit*)(botAI->GetBot()->GetPet()); }
    };
}
