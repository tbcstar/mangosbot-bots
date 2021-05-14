/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ExternalEventHelper.h"
#include "Trigger.h"
#include "../ChatHelper.h"
#include "../Playerbot.h"

bool ExternalEventHelper::ParseChatCommand(std::string const& command, Player* owner)
{
    if (HandleCommand(command, "", owner))
        return true;

    size_t i = string::npos;
    while (true)
    {
        size_t found = command.rfind(" ", i);
        if (found == string::npos || !found)
            break;

        std::string const& name = command.substr(0, found);
        std::string const& param = command.substr(found + 1);

        i = found - 1;

        if (HandleCommand(name, param, owner))
            return true;
    }

    if (!ChatHelper::parseable(command))
        return false;

    HandleCommand("c", command, owner);
    HandleCommand("t", command, owner);

    return true;
}

void ExternalEventHelperHandlePacket(std::map<uint16, std::string>& handlers, WorldPacket const& packet, Player* owner)
{
    uint16 opcode = packet.GetOpcode();
    string name = handlers[opcode];
    if (name.empty())
        return;

    Trigger* trigger = aiObjectContext->GetTrigger(name);
    if (!trigger)
        return;

    WorldPacket p(packet);
    trigger->ExternalEvent(p, owner);
}

bool ExternalEventHelperHandleCommand(std::string const& name, std::string const& param, Player* owner)
{
    Trigger* trigger = aiObjectContext->GetTrigger(name);
    if (!trigger)
        return false;

    trigger->ExternalEvent(param, owner);

    return true;
}
