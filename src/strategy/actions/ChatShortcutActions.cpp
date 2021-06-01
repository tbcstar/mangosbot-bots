/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ChatShortcutActions.h"
#include "Event.h"
#include "PositionValue.h"
#include "Playerbot.h"

void ReturnPositionResetAction::ResetReturnPosition()
{
    PositionMap& posMap = context->GetValue<PositionMap&>("position")->Get();
    PositionInfo pos = posMap["return"];
    pos.Reset();
    posMap["return"] = pos;
}

void ReturnPositionResetAction::SetReturnPosition(float x, float y, float z)
{
    PositionMap& posMap = context->GetValue<PositionMap&>("position")->Get();
    PositionInfo pos = posMap["return"];
    pos.Set(x, y, z, botAI->GetBot()->GetMapId());
    posMap["return"] = pos;
}

bool FollowChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    botAI->Reset();
    botAI->ChangeStrategy("+follow,-passive", BOT_STATE_NON_COMBAT);
    botAI->ChangeStrategy("-follow,-passive", BOT_STATE_COMBAT);

    ResetReturnPosition();

    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig->sightDistance)
    {
        botAI->TellError("I will not follow you - too far away");
        return true;
    }

    botAI->TellMaster("Following");
    return true;
}

bool StayChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    botAI->Reset();
    botAI->ChangeStrategy("+stay,-passive", BOT_STATE_NON_COMBAT);
    botAI->ChangeStrategy("-follow,-passive", BOT_STATE_COMBAT);

    SetReturnPosition(bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ());

    botAI->TellMaster("Staying");
    return true;
}

bool FleeChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    botAI->Reset();
    botAI->ChangeStrategy("+follow,+passive", BOT_STATE_NON_COMBAT);
    botAI->ChangeStrategy("+follow,+passive", BOT_STATE_COMBAT);

    ResetReturnPosition();

    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig->sightDistance)
    {
        botAI->TellError("I will not flee with you - too far away");
        return true;
    }

    botAI->TellMaster("Fleeing");
    return true;
}

bool GoawayChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    botAI->Reset();
    botAI->ChangeStrategy("+runaway", BOT_STATE_NON_COMBAT);
    botAI->ChangeStrategy("+runaway", BOT_STATE_COMBAT);

    ResetReturnPosition();

    botAI->TellMaster("Running away");
    return true;
}

bool GrindChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    botAI->Reset();
    botAI->ChangeStrategy("+grind,-passive", BOT_STATE_NON_COMBAT);

    ResetReturnPosition();

    botAI->TellMaster("Grinding");
    return true;
}

bool TankAttackChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    if (!botAI->IsTank(bot))
        return false;

    botAI->Reset();
    botAI->ChangeStrategy("-passive", BOT_STATE_NON_COMBAT);
    botAI->ChangeStrategy("-passive", BOT_STATE_COMBAT);

    ResetReturnPosition();

    botAI->TellMaster("Attacking");
    return true;
}

bool MaxDpsChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    botAI->Reset();
    botAI->ChangeStrategy("-threat,-conserve mana,-cast time,+dps debuff", BOT_STATE_COMBAT);

    botAI->TellMaster("Max DPS");
    return true;
}
