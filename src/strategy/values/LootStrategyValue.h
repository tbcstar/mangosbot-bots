#pragma once
#include "../../LootObjectStack.h"
#include "../Value.h"

namespace botAI
{
    class LootStrategyValue : public ManualSetValue<LootStrategy*>
	{
	public:
        LootStrategyValue(PlayerbotAI* botAI) : ManualSetValue<LootStrategy*>(botAI, normal) { }
        virtual ~LootStrategyValue() { delete defaultValue; }

        virtual string Save();
        virtual bool Load(string value);

        static LootStrategy *normal, *gray, *all, *disenchant;
        static LootStrategy* instance(string name);
    };
}
