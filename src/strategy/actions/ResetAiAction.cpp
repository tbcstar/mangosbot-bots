#include "botpch.h"
#include "../../playerbot.h"
#include "ResetAiAction.h"
#include "../../PlayerbotDbStore.h"

using namespace ai;

bool ResetAiAction::Execute(Event event)
{
    sPlayerbotDbStore.Reset(botAI);
    botAI->ResetStrategies(false);
    botAI->TellMaster("AI was reset to defaults");
    return true;
}
