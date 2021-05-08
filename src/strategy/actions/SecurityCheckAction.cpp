#include "botpch.h"
#include "../../playerbot.h"
#include "../../RandomPlayerbotMgr.h"
#include "SecurityCheckAction.h"

using namespace ai;


bool SecurityCheckAction::isUseful()
{
    return sRandomPlayerbotMgr->IsRandomBot(bot) && botAI->GetMaster() && botAI->GetMaster()->GetSession()->GetSecurity() < SEC_GAMEMASTER;
}

bool SecurityCheckAction::Execute(Event event)
{
    Group* group = bot->GetGroup();
    if (group)
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
