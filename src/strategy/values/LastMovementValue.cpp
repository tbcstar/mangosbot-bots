/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "LastMovementValue.h"
#include "Playerbot.h"

void LastMovement::Set(Unit* follow)
{
    Set(0.0f, 0.0f, 0.0f, 0.0f);
    lastFollow = follow;
}

void LastMovement::Set(float x, float y, float z, float ori)
{
    lastMoveToX = x;
    lastMoveToY = y;
    lastMoveToZ = z;
    lastMoveToOri = ori;
    lastFollow = nullptr;
}
