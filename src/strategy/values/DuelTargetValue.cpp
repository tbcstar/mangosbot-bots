#include "botpch.h"
#include "../../playerbot.h"
#include "DuelTargetValue.h"

using namespace botAI;

Unit* DuelTargetValue::Calculate()
{
    return bot->duel ? bot->duel->opponent : nullptr;
}
