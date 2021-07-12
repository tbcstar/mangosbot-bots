/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Item.h"
#include "NamedObjectContext.h"
#include "Value.h"
#include "InventoryAction.h"
class InventoryItemValueBase : public InventoryAction
{
    public:
        InventoryItemValueBase(PlayerbotAI* botAI) : InventoryAction(botAI, "empty") { }

        bool Execute(Event event) override { return false; }

    protected:
        std::vector<Item*> Find(std::string const& qualifier);
};

class ItemCountValue : public Uint8CalculatedValue, public Qualified, InventoryItemValueBase
{
	public:
        ItemCountValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI), InventoryItemValueBase(botAI) { }

        uint8 Calculate() override;
};

class InventoryItemValue : public CalculatedValue<std::vector<Item*>>, public Qualified, InventoryItemValueBase
{
    public:
        InventoryItemValue(PlayerbotAI* botAI) : CalculatedValue<std::vector<Item*>>(botAI), InventoryItemValueBase(botAI) { }

        std::vector<Item*> Calculate() override;
};
