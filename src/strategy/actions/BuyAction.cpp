#include "botpch.h"
#include "../../playerbot.h"
#include "BuyAction.h"
#include "../ItemVisitors.h"
#include "../values/ItemCountValue.h"

using namespace ai;

bool BuyAction::Execute(Event event)
{
    string link = event.getParam();

    ItemIds itemIds = chat->parseItems(link);
    if (itemIds.empty())
        return false;

    Player* master = GetMaster();

    if (!master)
        return false;

    list<ObjectGuid> vendors = botAI->GetAiObjectContext()->GetValue<list<ObjectGuid> >("nearest npcs")->Get();
    bool vendored = false, result = false;
    for (list<ObjectGuid>::iterator i = vendors.begin(); i != vendors.end(); ++i)
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
                ostringstream out; out << "Nobody sells " << ChatHelper::formatItem(proto) << " nearby";
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
            ostringstream out; out << "Buying " << ChatHelper::formatItem(proto);
            botAI->TellMaster(out.str());
            return true;
        }
    }

    return false;
}
