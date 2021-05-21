#include "botpch.h"
#include "../../playerbot.h"
#include "NewPlayerNearbyValue.h"

using namespace botAI;

ObjectGuid NewPlayerNearbyValue::Calculate()
{
    GuidVector players = botAI->GetAiObjectContext()->GetValue<GuidVector >("nearest friendly players")->Get();
    set<ObjectGuid>& alreadySeenPlayers = botAI->GetAiObjectContext()->GetValue<set<ObjectGuid>& >("already seen players")->Get();
    for (GuidVector::iterator i = players.begin(); i != players.end(); ++i)
    {
        ObjectGuid guid = *i;
        if (alreadySeenPlayers.find(guid) == alreadySeenPlayers.end())
            return guid;
    }

    return ObjectGuid::Empty;
}
