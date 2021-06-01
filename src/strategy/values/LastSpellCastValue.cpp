/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "LastSpellCastValue.h"
#include "Playerbot.h"

void LastSpellCast::Set(uint32 newId, ObjectGuid newTarget, time_t newTime)
{
    id = newId;
    target = newTarget;
    time = newTime;
}

void LastSpellCast::Reset()
{
    id = 0;
    target.Clear();
    time = 0;
}
