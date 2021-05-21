#pragma once
#include "../Value.h"
#include "../../LootObjectStack.h"
#include "../../ServerFacade.h"

namespace botAI
{

    class AvailableLootValue : public ManualSetValue<LootObjectStack*>
	{
	public:
        AvailableLootValue() : ManualSetValue<LootObjectStack*>(botAI, nullptr)
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
        LootTargetValue() : ManualSetValue<LootObject>(botAI, LootObject()) { }
    };

    class CanLootValue : public BoolCalculatedValue
    {
    public:
        CanLootValue() : BoolCalculatedValue(botAI) { }

        virtual bool Calculate()
        {
            LootObject loot = AI_VALUE(LootObject, "loot target");
            return !loot.IsEmpty() &&
                    loot.GetWorldObject(bot) &&
                    sServerFacade->IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "loot target"), INTERACTION_DISTANCE);
        }
    };
}
