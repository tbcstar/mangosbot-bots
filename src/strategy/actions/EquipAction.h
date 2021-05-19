/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "../../ChatHelper.h"
#include "InventoryAction.h"

class Event;
class FindItemVisitor;
class Item;
class PlayerbotAI;

class EquipAction : public InventoryAction
{
    public:
        EquipAction(PlayerbotAI* botAI, std::string const& name = "equip") : InventoryAction(botAI, name) { }

        bool Execute(Event event) override;

    protected:
        void EquipItems(ItemIds ids);

    private:
        void EquipItem(FindItemVisitor* visitor);
        void EquipItem(Item* item);
};
