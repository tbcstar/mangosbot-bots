/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ChatCommandTrigger.h"

void ChatCommandTrigger::ExternalEvent(std::string const& paramName, Player* eventPlayer = nullptr)
{
    param = paramName;
    owner = eventPlayer;
    triggered = true;
}

Event ChatCommandTrigger::Check()
{
    if (!triggered)
        return Event();

    return Event(getName(), param, owner);
}

void ChatCommandTrigger::Reset()
{
    triggered = false;
}
