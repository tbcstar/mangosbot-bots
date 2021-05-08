#include "../../botpch.h"
#include "../playerbot.h"
#include "AiObject.h"

AiObject::AiObject(PlayerbotAI* botAI) :
    PlayerbotAIAware(botAI),
    bot(botAI->GetBot()),
    context(botAI->GetAiObjectContext()),
    chat(botAI->GetChatHelper())
{
}

Player* AiObject::GetMaster()
{
    return botAI->GetMaster();
}
