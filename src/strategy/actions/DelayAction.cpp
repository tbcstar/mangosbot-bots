/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DelayAction.h"
#include "Event.h"
#include "Playerbot.h"

bool DelayAction::Execute(Event event)
{
    if (!sRandomPlayerbotMgr->IsRandomBot(bot) || bot->GetGroup() || botAI->GetMaster())
        return false;

    if (bot->IsInCombat())
        return true;

    botAI->SetNextCheckDelay(sPlayerbotAIConfig->passiveDelay + sPlayerbotAIConfig->globalCoolDown);
    return true;
}
