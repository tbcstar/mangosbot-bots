#include "botpch.h"
#include "../../playerbot.h"
#include "DebugAction.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

bool DebugAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    string text = event.getParam();
    string response = botAI->HandleRemoteCommand(text);
    botAI->TellMaster(response);
    return true;
}
