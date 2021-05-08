#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{

    class ItemForSpellValue : public CalculatedValue<Item*>, public Qualified
	{
	public:
        ItemForSpellValue(PlayerbotAI* botAI) : CalculatedValue<Item*>(botAI) {}

    public:
        virtual Item* Calculate();

    private:
        Item* GetItemFitsToSpellRequirements(uint8 slot, SpellEntry const *spellInfo);

    };
}
