/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RepairAllAction.h"
#include "Event.h"
#include "ChatHelper.h"
#include "Playerbot.h"

bool RepairAllAction::Execute(Event event)
{
    GuidVector npcs = AI_VALUE(GuidVector, "nearest npcs");
    for (ObjectGuid const guid : npcs)
    {
        Creature* unit = bot->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_REPAIR);
        if (!unit)
            continue;

        if (bot->HasUnitState(UNIT_STATE_DIED))
            bot->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

        bot->SetFacingToObject(unit);
        float discountMod = bot->GetReputationPriceDiscount(unit);
        uint32 totalCost = bot->DurabilityRepairAll(true, discountMod, false);

        std::ostringstream out;
        out << "Repair: " << chat->formatMoney(totalCost) << " (" << unit->GetName() << ")";
        botAI->TellMasterNoFacing(out.str());

        return true;
    }

    botAI->TellError("Cannot find any npc to repair at");
    return false;
}
