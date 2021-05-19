#pragma once
#include "../Value.h"
#include "../ItemVisitors.h"
#include "../actions/InventoryAction.h"

namespace ai
{
    class InventoryItemValueBase : public InventoryAction
    {
    public:
        InventoryItemValueBase(PlayerbotAI* botAI) : InventoryAction(botAI, "empty") {}
        virtual bool Execute(Event event) { return false; }

    protected:
        list<Item*> Find(string qualifier);
    };

    class ItemCountValue : public Uint8CalculatedValue, public Qualified, InventoryItemValueBase
	{
	public:
        ItemCountValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI), InventoryItemValueBase(botAI) {}

    public:
        virtual uint8 Calculate();
	};

    class InventoryItemValue : public CalculatedValue<list<Item*> >, public Qualified, InventoryItemValueBase
    {
    public:
        InventoryItemValue(PlayerbotAI* botAI) : CalculatedValue<list<Item*> >(botAI), InventoryItemValueBase(botAI) {}

    public:
        virtual list<Item*> Calculate();
    };
}
