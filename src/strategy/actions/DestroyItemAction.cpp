/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DestroyItemAction.h"
#include "../Event.h"
#include "../values/ItemCountValue.h"
#include "../../Playerbot.h"

bool DestroyItemAction::Execute(Event event)
{
    std::string const& text = event.getParam();
    ItemIds ids = chat->parseItems(text);

    for (ItemIds::iterator i = ids.begin(); i != ids.end(); i++)
    {
        FindItemByIdVisitor visitor(*i);
        DestroyItem(&visitor);
    }

    return true;
}

void DestroyItemAction::DestroyItem(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    std::vector<Item*> items = visitor->GetResult();
	for (Item* item : items)
    {
        bot->DestroyItem(item->GetBagSlot(),item->GetSlot(), true);

        std::ostringstream out;
        out << chat->formatItem(item->GetTemplate()) << " destroyed";
        botAI->TellMaster(out);
    }
}
