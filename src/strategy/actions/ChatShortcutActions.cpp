#include "botpch.h"
#include "../../playerbot.h"
#include "ChatShortcutActions.h"
#include "../../PlayerbotAIConfig.h"
#include "../values/PositionValue.h"

using namespace ai;

void ReturnPositionResetAction::ResetReturnPosition()
{
    ai::PositionMap& posMap = context->GetValue<ai::PositionMap&>("position")->Get();
    ai::Position pos = posMap["return"];
    pos.Reset();
    posMap["return"] = pos;
}

void ReturnPositionResetAction::SetReturnPosition(float x, float y, float z)
{
    ai::PositionMap& posMap = context->GetValue<ai::PositionMap&>("position")->Get();
    ai::Position pos = posMap["return"];
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
