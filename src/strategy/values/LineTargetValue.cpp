#include "botpch.h"
#include "../../playerbot.h"
#include "LineTargetValue.h"

#include "../../ServerFacade.h"
using namespace botAI;

Unit* LineTargetValue::Calculate()
{
    Player* master = GetMaster();
    if (!master)
        return nullptr;

    Group* group = master->GetGroup();
    if (!group)
        return nullptr;

    Player *prev = master;
    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        Player *player = ObjectAccessor::FindPlayer(itr->guid);
        if (!player || !sServerFacade->IsAlive(player) || player == master)
            continue;

        if (player == bot)
            return prev;

        prev = player;
    }

    return master;
}

