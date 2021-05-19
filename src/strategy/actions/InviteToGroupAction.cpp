/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "InviteToGroupAction.h"
#include "../Event.h"
#include "../../Playerbot.h"

bool InviteToGroupAction::Execute(Event event)
{
    Player* master = event.getOwner();
    if (!master)
        return false;

    WorldPacket p;
    uint32 roles_mask = 0;
    p << master->GetName();
    p << roles_mask;
    bot->GetSession()->HandleGroupInviteOpcode(p);

    return true;
}
