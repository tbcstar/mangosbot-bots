/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "SecurityCheckAction.h"
#include "Event.h"
#include "Playerbot.h"

bool SecurityCheckAction::isUseful()
{
    return sRandomPlayerbotMgr.IsRandomBot(bot) && botAI->GetMaster() && botAI->GetMaster()->GetSession()->GetSecurity() < SEC_GAMEMASTER && !botAI->GetMaster()->GetPlayerbotAI();
}

bool SecurityCheckAction::Execute(Event event)
{
    if (Group* group = bot->GetGroup())
    {
        LootMethod method = group->GetLootMethod();
        ItemQualities threshold = group->GetLootThreshold();
        if (method == MASTER_LOOT || method == FREE_FOR_ALL || threshold > ITEM_QUALITY_UNCOMMON)
        {
            botAI->TellError("I won't do anything until you change loot type to group loot with green threshold");
            botAI->ChangeStrategy("+passive,+stay", BOT_STATE_NON_COMBAT);
            botAI->ChangeStrategy("+passive,+stay", BOT_STATE_COMBAT);
            return true;
        }
    }

    return false;
}
