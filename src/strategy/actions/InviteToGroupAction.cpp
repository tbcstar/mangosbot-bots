/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "InviteToGroupAction.h"
#include "Event.h"
#include "Playerbot.h"
#include "ServerFacade.h"

bool InviteToGroupAction::Execute(Event event)
{
    Player* master = event.getOwner();
    if (!master)
        return false;

    return Invite(master);
}

bool InviteToGroupAction::Invite(Player* player)
{
    if (!player)
        return false;

    if (!player->GetPlayerbotAI() && !botAI->GetSecurity()->CheckLevelFor(PLAYERBOT_SECURITY_INVITE, false, player))
        return false;

    WorldPacket p;
    uint32 roles_mask = 0;
    p << player->GetName();
    p << roles_mask;
    bot->GetSession()->HandleGroupInviteOpcode(p);

    return true;
}

bool InviteNearbyToGroupAction::Execute(Event event)
{
    GuidVector nearGuids = botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest friendly players")->Get();
    for (auto& i : nearGuids)
    {
        Player* player = ObjectAccessor::FindPlayer(i);
        if (!player)
            continue;

        if (player->GetGroup())
            continue;

        PlayerbotAI* botAI = player->GetPlayerbotAI();
        if (!botAI) //Only invite bots. Maybe change later.
            continue;

        if (botAI->GetGrouperType() == SOLO)
            return false;

        if (botAI->GetMaster())
            if (!botAI->GetMaster()->GetPlayerbotAI() || botAI->GetMaster()->GetPlayerbotAI()->IsRealPlayer()) //Do not invite bots with a player master.
                if (!botAI->IsRealPlayer()) //Unless the bot is really a player
                    continue;

        if (abs(int32(player->getLevel() - bot->getLevel())) > 2)
            continue;

        if (sServerFacade->GetDistance2d(bot, player) > sPlayerbotAIConfig->sightDistance)
            continue;

        return Invite(player);
    }

    return false;
}

bool InviteNearbyToGroupAction::isUseful()
{
    if (!sPlayerbotAIConfig->randomBotGroupNearby)
        return false;

    if (bot->InBattleground())
        return false;

    if (bot->InBattlegroundQueue())
        return false;

    GrouperType grouperType = botAI->GetGrouperType();
    if (grouperType == SOLO || grouperType == MEMBER)
        return false;

    if (Group* group = bot->GetGroup())
    {
        if (group->IsFull())
            return false;

        if (botAI->GetGroupMaster() != bot)
            return false;

        uint32 memberCount = group->GetMembersCount();
        if (memberCount > 1 && grouperType == LEADER_2)
            return false;

        if (memberCount > 2 && grouperType == LEADER_3)
            return false;

        if (memberCount > 3 && grouperType == LEADER_4)
            return false;
    }

    if (botAI->GetMaster())
        if (!botAI->GetMaster()->GetPlayerbotAI() || botAI->GetMaster()->GetPlayerbotAI()->IsRealPlayer()) //Alts do not invite.
            if (!botAI->IsRealPlayer()) //Unless the bot is really a player
                return false;

    return true;
}
