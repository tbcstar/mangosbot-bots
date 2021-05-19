/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "LeaveGroupAction.h"
#include "../Event.h"
#include "../../Playerbot.h"

bool LeaveGroupAction::Execute(Event event)
{
    if (!bot->GetGroup())
        return false;

    botAI->TellMaster("Goodbye!", PLAYERBOT_SECURITY_TALK);

    WorldPacket p;
    string member = bot->GetName();
    p << uint32(PARTY_OP_LEAVE) << member << uint32(0);
    bot->GetSession()->HandleGroupDisbandOpcode(p);

    bool randomBot = sRandomPlayerbotMgr->IsRandomBot(bot);
    if (randomBot)
    {
        bot->GetPlayerbotAI()->SetMaster(nullptr);
        sRandomPlayerbotMgr->ScheduleTeleport(bot->GetGUID());
    }

    botAI->ResetStrategies(!randomBot);
    return true;
}

bool PartyCommandAction::Execute(Event event)
{
    WorldPacket& p = event.getPacket();
    p.rpos(0);
    uint32 operation;
    string member;

    p >> operation >> member;

    if (operation != PARTY_OP_LEAVE)
        return false;

    Player* master = GetMaster();
    if (master && member == master->GetName())
        return LeaveGroupAction::Execute(event);

    return false;
}

bool UninviteAction::Execute(Event event)
{
    WorldPacket& p = event.getPacket();
    p.rpos(0);
    ObjectGuid guid;

    p >> guid;

    if (bot->GetGUID() == guid)
        return LeaveGroupAction::Execute(event);

    return false;
}
