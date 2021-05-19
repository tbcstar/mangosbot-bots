/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ReleaseSpiritAction.h"
#include "../Event.h"
#include "../../Playerbot.h"

bool ReleaseSpiritAction::Execute(Event event)
{
    if (bot->IsAlive() || bot->GetCorpse())
    {
        botAI->TellError("I am not dead");
        return false;
    }

    botAI->ChangeStrategy("-follow,+stay", BOT_STATE_NON_COMBAT);

    bot->SetBotDeathTimer();
    bot->BuildPlayerRepop();

    bot->RepopAtGraveyard();
    botAI->TellMaster("Meet me at the graveyard");
    return true;
}
