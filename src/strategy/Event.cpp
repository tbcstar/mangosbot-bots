/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Event.h"

ObjectGuid Event::getObject()
{
    if (packet.empty())
        return ObjectGuid::Empty;

    WorldPacket p(packet);
    p.rpos(0);

    ObjectGuid guid;
    p >> guid;

    return guid;
}
