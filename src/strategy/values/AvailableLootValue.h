#pragma once
#include "../Value.h"
#include "../../LootObjectStack.h"
#include "../../ServerFacade.h"

namespace ai
{

    class AvailableLootValue : public ManualSetValue<LootObjectStack*>
	{
	public:
        AvailableLootValue(PlayerbotAI* botAI) : ManualSetValue<LootObjectStack*>(ai, NULL)
        {
            value = new LootObjectStack(botAI->GetBot());
        }

        virtual ~AvailableLootValue()
        {
            if (value)
                delete value;
        }
    };

    class LootTargetValue : public ManualSetValue<LootObject>
    {
    public:
        LootTargetValue(PlayerbotAI* botAI) : ManualSetValue<LootObject>(ai, LootObject()) {}
    };

    class CanLootValue : public BoolCalculatedValue
    {
    public:
        CanLootValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) {}

        virtual bool Calculate()
        {
            LootObject loot = AI_VALUE(LootObject, "loot target");
            return !loot.IsEmpty() &&
                    loot.GetWorldObject(bot) &&
                    sServerFacade->IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "loot target"), INTERACTION_DISTANCE);
        }
    };
}
