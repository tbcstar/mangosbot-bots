#include "botpch.h"
#include "../../playerbot.h"
#include "RtiValue.h"

using namespace botAI;

RtiValue::RtiValue(PlayerbotAI* botAI)
    : ManualSetValue<string>(botAI, "skull")
{
}

RtiCcValue::RtiCcValue(PlayerbotAI* botAI)
    : ManualSetValue<string>(botAI, "moon")
{
}
