/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "TellMasterAction.h"
#include "Event.h"
#include "Playerbot.h"

bool TellMasterAction::Execute(Event event)
{
    botAI->TellMaster(text);
    return true;
}

bool OutOfReactRangeAction::Execute(Event event)
{
    bool canFollow = Follow(AI_VALUE(Unit*, "master target"));
    if (!canFollow)
    {
        botAI->SetNextCheckDelay(5000);
        return false;
    }

    botAI->TellMaster("Wait for me!");
    return true;
}

