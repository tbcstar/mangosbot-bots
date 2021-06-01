/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "InvalidTargetValue.h"
#include "AttackersValue.h"
#include "Playerbot.h"

bool InvalidTargetValue::Calculate()
{
    Unit* target = AI_VALUE(Unit*, qualifier);
    if (qualifier == "current target")
    {
        return !AttackersValue::IsValidTarget(target, bot);
    }

    return !target;
}
