/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "EquipAction.h"
#include "Event.h"
#include "ItemCountValue.h"
#include "Playerbot.h"

bool EquipAction::Execute(Event event)
{
    std::string const& text = event.getParam();
    ItemIds ids = chat->parseItems(text);
    EquipItems(ids);
    return true;
}

void EquipAction::EquipItems(ItemIds ids)
{
    for (ItemIds::iterator i =ids.begin(); i != ids.end(); i++)
    {
        FindItemByIdVisitor visitor(*i);
        EquipItem(&visitor);
    }
}

void EquipAction::EquipItem(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    std::vector<Item*> items = visitor->GetResult();
	if (!items.empty())
        EquipItem(**items.begin());
}

void EquipAction::EquipItem(Item* item)
{
    uint8 bagIndex = item->GetBagSlot();
    uint8 slot = item->GetSlot();
    uint32 itemId = item->GetTemplate()->ItemId;

    if (item->GetTemplate()->InventoryType == INVTYPE_AMMO)
    {
        bot->SetAmmo(itemId);
    }
    else
    {
        WorldPacket packet(CMSG_AUTOEQUIP_ITEM, 2);
        packet << bagIndex << slot;
        bot->GetSession()->HandleAutoEquipItemOpcode(packet);
    }

    std::ostringstream out;
    out << "equipping " << chat->formatItem(item->GetTemplate());
    botAI->TellMaster(out);
}
