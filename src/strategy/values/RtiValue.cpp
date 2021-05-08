#include "botpch.h"
#include "../../playerbot.h"
#include "RtiValue.h"

using namespace ai;

RtiValue::RtiValue(PlayerbotAI* botAI)
    : ManualSetValue<string>(ai, "skull")
{
}

RtiCcValue::RtiCcValue(PlayerbotAI* botAI)
    : ManualSetValue<string>(ai, "moon")
{
}
