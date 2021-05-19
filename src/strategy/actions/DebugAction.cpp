/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DebugAction.h"
#include "../Event.h"
#include "../../Playerbot.h"

bool DebugAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    std::string const& text = event.getParam();
    std::string const& response = botAI->HandleRemoteCommand(text);
    botAI->TellMaster(response);
    return true;
}
