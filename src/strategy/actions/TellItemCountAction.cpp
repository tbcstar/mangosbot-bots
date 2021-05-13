#include "botpch.h"
#include "../../playerbot.h"
#include "TellItemCountAction.h"
#include "../values/ItemCountValue.h"

using namespace ai;

bool TellItemCountAction::Execute(Event event)
{
    string text = event.getParam();
    list<Item*> found = parseItems(text);
    map<uint32, uint32> itemMap;
    map<uint32, bool> soulbound;
    for (list<Item*>::iterator i = found.begin(); i != found.end(); i++)
    {
        ItemTemplate const* proto = (*i)->GetProto();
        itemMap[proto->ItemId] += (*i)->GetCount();
        soulbound[proto->ItemId] = (*i)->IsSoulBound();
    }

    botAI->TellMaster("=== Inventory ===");
    for (map<uint32, uint32>::iterator i = itemMap.begin(); i != itemMap.end(); ++i)
    {
        ItemTemplate const* proto = sItemStorage.LookupEntry<ItemTemplate>(i->first);
        TellItem(proto, i->second, soulbound[i->first]);
    }

    return true;
}
