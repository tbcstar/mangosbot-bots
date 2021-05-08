#include "botpch.h"
#include "../../playerbot.h"
#include "ChangeStrategyAction.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

bool ChangeCombatStrategyAction::Execute(Event event)
{
    string text = event.getParam();
    botAI->ChangeStrategy(text.empty() ? getName() : text, BOT_STATE_COMBAT);
    return true;
}

bool ChangeNonCombatStrategyAction::Execute(Event event)
{
    string text = event.getParam();

    uint32 account = sObjectMgr->GetPlayerAccountIdByGUID(bot->GetGUID());
    if (sPlayerbotAIConfig->IsInRandomAccountList(account) && botAI->GetMaster() && botAI->GetMaster()->GetSession()->GetSecurity() < SEC_GAMEMASTER)
    {
        if (text.find("loot") != string::npos || text.find("gather") != string::npos)
        {
            botAI->TellError("You can change any strategy except loot and gather");
            return false;
        }
    }

    botAI->ChangeStrategy(text, BOT_STATE_NON_COMBAT);
    return true;
}

bool ChangeDeadStrategyAction::Execute(Event event)
{
    string text = event.getParam();
    botAI->ChangeStrategy(text, BOT_STATE_DEAD);
    return true;
}
