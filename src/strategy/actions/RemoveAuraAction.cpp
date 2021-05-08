#include "botpch.h"
#include "../../playerbot.h"
#include "RemoveAuraAction.h"

#include "../../PlayerbotAIConfig.h"
#include "../../ServerFacade.h"
using namespace ai;

RemoveAuraAction::RemoveAuraAction(PlayerbotAI* botAI) : Action(ai, "ra")
{
}

bool RemoveAuraAction::Execute(Event event)
{
    string text = event.getParam();
    botAI->RemoveAura(text);
    return true;
}
