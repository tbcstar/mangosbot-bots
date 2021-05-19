/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ReviveFromCorpseAction.h"
#include "../Event.h"
#include "../../Playerbot.h"
#include "../../PlayerbotFactory.h"

bool ReviveFromCorpseAction::Execute(Event event)
{
    Corpse* corpse = bot->GetCorpse();
    if (!corpse)
        return false;

    time_t reclaimTime = corpse->GetGhostTime() + bot->GetCorpseReclaimDelay( corpse->GetType()==CORPSE_RESURRECTABLE_PVP );
    if (reclaimTime > time(0) || corpse->GetDistance(bot) > botAI->GetRange("spell"))
        return false;

    bot->ResurrectPlayer(0.5f);
    bot->SpawnCorpseBones();
    bot->SaveToDB(false, false);

    context->GetValue<Unit*>("current target")->Set(nullptr);
    bot->SetTarget(ObjectGuid::Empty);
    return true;
}

bool SpiritHealerAction::Execute(Event event)
{
    Corpse* corpse = bot->GetCorpse();
    if (!corpse)
    {
        botAI->TellError("I am not a spirit");
        return false;
    }

    GuidVector npcs = AI_VALUE(GuidVector, "nearest npcs");
    for (ObjectGuid const guid : npcs)
    {
        if (Unit* unit = botAI->GetUnit(guid))
            if (unit->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPIRITHEALER))
            {
                PlayerbotChatHandler ch(bot);
                bot->ResurrectPlayer(0.5f);
                bot->SpawnCorpseBones();
                bot->SaveToDB(false, false);
                context->GetValue<Unit*>("current target")->Set(nullptr);
                bot->SetTarget(ObjectGuid::Empty);
                botAI->TellMaster("Hello");
                return true;
            }
    }

    botAI->TellError("Cannot find any spirit healer nearby");
    return false;
}
