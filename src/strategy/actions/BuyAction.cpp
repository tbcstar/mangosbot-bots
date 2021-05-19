/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "BuyAction.h"
#include "../Event.h"
#include "../ItemVisitors.h"
#include "../values/ItemCountValue.h"
#include "../../Playerbot.h"

bool BuyAction::Execute(Event event)
{
    std::string const& link = event.getParam();

    ItemIds itemIds = chat->parseItems(link);
    if (itemIds.empty())
        return false;

    Player* master = GetMaster();
    if (!master)
        return false;

    GuidVector vendors = botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest npcs")->Get();

    bool vendored = false;
    bool result = false;
    for (GuidVector::iterator i = vendors.begin(); i != vendors.end(); ++i)
    {
        ObjectGuid vendorguid = *i;
        Creature* pCreature = bot->GetNPCIfCanInteractWith(vendorguid, UNIT_NPC_FLAG_VENDOR);
        if (!pCreature)
            continue;

        vendored = true;

        for (ItemIds::iterator i = itemIds.begin(); i != itemIds.end(); i++)
        {
            uint32 itemId = *i;
            ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
            if (!proto)
                continue;

            VendorItemData const* tItems = pCreature->GetVendorItems();
            result |= BuyItem(pCreature->GetVendorItems(), vendorguid, proto);

            if (!result)
            {
                std::ostringstream out;
                out << "Nobody sells " << ChatHelper::formatItem(proto) << " nearby";
                botAI->TellMaster(out.str());
            }
        }
    }

    if (!vendored)
    {
        botAI->TellError("There are no vendors nearby");
        return false;
    }

    return true;
}

bool BuyAction::BuyItem(VendorItemData const* tItems, ObjectGuid vendorguid, ItemTemplate const* proto)
{
    if (!tItems)
        return false;

    uint32 itemId = proto->ItemId;
    for (uint32 slot = 0; slot < tItems->GetItemCount(); slot++)
    {
        if (tItems->GetItem(slot)->item == itemId)
        {
            bot->BuyItemFromVendor(vendorguid, itemId, 1, NULL_BAG, NULL_SLOT);

            std::ostringstream out;
            out << "Buying " << ChatHelper::formatItem(proto);
            botAI->TellMaster(out.str());
            return true;
        }
    }

    return false;
}
