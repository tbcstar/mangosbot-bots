/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RpgAction.h"
#include "EmoteAction.h"
#include "GossipDef.h"
#include "Event.h"
#include "PossibleRpgTargetsValue.h"
#include "Playerbot.h"

bool RpgAction::Execute(Event event)
{
    Unit* target = botAI->GetUnit(AI_VALUE(ObjectGuid, "rpg target"));
    if (!target)
        return false;

    if (bot->isMoving())
        return false;

    if (bot->GetMapId() != target->GetMapId())
    {
        context->GetValue<ObjectGuid>("rpg target")->Set(ObjectGuid::Empty);
        return false;
    }

    if (!bot->IsInFront(target, sPlayerbotAIConfig->sightDistance, CAST_ANGLE_IN_FRONT) && !bot->HasUnitState(UNIT_STATE_IN_FLIGHT) && !bot->IsFlying())
    {
        bot->SetFacingToObject(target);
        botAI->SetNextCheckDelay(sPlayerbotAIConfig->globalCoolDown);
        return false;
    }

    if (!bot->GetNPCIfCanInteractWith(target->GetGUID(), UNIT_NPC_FLAG_NONE))
        return false;

    if (target->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_FLIGHTMASTER))
    {
        taxi(target);
        return true;
    }

    std::vector<RpgElement> elements;
    elements.push_back(&RpgAction::cancel);
    elements.push_back(&RpgAction::emote);
    elements.push_back(&RpgAction::stay);
    elements.push_back(&RpgAction::work);

    RpgElement element = elements[urand(0, elements.size() - 1)];
    (this->*element)(target);
    return true;
}

void RpgAction::stay(Unit* unit)
{
    if (bot->PlayerTalkClass)
        bot->PlayerTalkClass->SendCloseGossip();

    botAI->SetNextCheckDelay(sPlayerbotAIConfig->rpgDelay);
}

void RpgAction::work(Unit* unit)
{
    bot->HandleEmoteCommand(EMOTE_STATE_USE_STANDING);
    botAI->SetNextCheckDelay(sPlayerbotAIConfig->rpgDelay);
}

void RpgAction::emote(Unit* unit)
{
    uint32 type = TalkAction::GetRandomEmote(unit);

    ObjectGuid oldSelection = bot->GetTarget();

    bot->SetTarget(unit->GetGUID());

    WorldPacket p1;
    p1 << unit->GetGUID();
    bot->GetSession()->HandleGossipHelloOpcode(p1);

    bot->HandleEmoteCommand(type);
    unit->SetFacingTo(unit->GetAngle(bot));

    if (oldSelection)
        bot->SetTarget(oldSelection);

    botAI->SetNextCheckDelay(sPlayerbotAIConfig->rpgDelay);
}

void RpgAction::cancel(Unit* unit)
{
    context->GetValue<ObjectGuid>("rpg target")->Set(ObjectGuid::Empty);
}

void RpgAction::taxi(Unit* unit)
{
    uint32 curloc = sObjectMgr->GetNearestTaxiNode(unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), unit->GetMapId(), bot->GetTeamId());

    std::vector<uint32> nodes;
    for (uint32 i = 0; i < sTaxiPathStore.GetNumRows(); ++i)
    {
        if (TaxiPathEntry const* entry = sTaxiPathStore.LookupEntry(i))
            if (entry->from == curloc)
            {
                uint8  field = uint8((i - 1) / 32);
                if (field < TaxiMaskSize)
                    nodes.push_back(i);
            }
    }

    if (nodes.empty())
    {
        sLog->outDetail("Bot %s - No flight paths available", bot->GetName());
        return;
    }

    context->GetValue<ObjectGuid>("rpg target")->Set(ObjectGuid::Empty);

    uint32 path = nodes[urand(0, nodes.size() - 1)];
    bot->m_taxi.SetTaximaskNode(path);
    uint32 money = bot->GetMoney();
    bot->SetMoney(money + 10000);

    TaxiPathEntry const* entry = sTaxiPathStore.LookupEntry(path);
    if (!entry)
        return;

    Creature* flightMaster = bot->GetNPCIfCanInteractWith(unit->GetGUID(), UNIT_NPC_FLAG_FLIGHTMASTER);
    if (!flightMaster)
    {
        sLog->outDetail("Bot %s cannot talk to flightmaster (%d location available)", bot->GetName(), nodes.size());
        return;
    }

    if (!bot->ActivateTaxiPathTo({ entry->from, entry->to }, flightMaster, 0))
    {
        sLog->outDetail("Bot %s cannot fly (%d location available)", bot->GetName(), nodes.size());
        return;
    }

    sLog->outDetail("Bot %s is flying to %u (%d location available)", bot->GetName(), path, nodes.size());
    bot->SetMoney(money);
}

bool RpgAction::isUseful()
{
    return context->GetValue<ObjectGuid>("rpg target")->Get();
}
