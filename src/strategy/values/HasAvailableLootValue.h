#pragma once
#include "../Value.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class HasAvailableLootValue : public BoolCalculatedValue
	{
	public:
        HasAvailableLootValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) {}

    public:
        virtual bool Calculate()
        {
            return !AI_VALUE(bool, "can loot") &&
                    AI_VALUE(LootObjectStack*, "available loot")->CanLoot(sPlayerbotAIConfig->lootDistance);
        }
    };
}
