#include "botpch.h"
#include "../../playerbot.h"
#include "NewPlayerNearbyValue.h"

using namespace ai;

ObjectGuid NewPlayerNearbyValue::Calculate()
{
    list<ObjectGuid> players = botAI->GetAiObjectContext()->GetValue<list<ObjectGuid> >("nearest friendly players")->Get();
    set<ObjectGuid>& alreadySeenPlayers = botAI->GetAiObjectContext()->GetValue<set<ObjectGuid>& >("already seen players")->Get();
    for (list<ObjectGuid>::iterator i = players.begin(); i != players.end(); ++i)
    {
        ObjectGuid guid = *i;
        if (alreadySeenPlayers.find(guid) == alreadySeenPlayers.end())
            return guid;
    }

    return ObjectGuid::Empty;
}
