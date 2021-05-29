/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ShamanActions.h"
#include "../../Playerbot.h"

bool CastTotemAction::isUseful() const
{
    return CastBuffSpellAction::isUseful() && !AI_VALUE2(bool, "has totem", name);
}

bool CastManaSpringTotemAction::isUseful() const
{
    return CastTotemAction::isUseful() && !AI_VALUE2(bool, "has totem", "healing stream totem");
}

bool CastFlametongueTotemAction::isUseful() const
{
    return CastTotemAction::isUseful() && !AI_VALUE2(bool, "has totem", "magma totem");
}

bool CastSearingTotemAction::isUseful() const
{
    return CastTotemAction::isUseful() && !AI_VALUE2(bool, "has totem", "flametongue totem");
}

bool CastMagmaTotemAction::isUseful() const
{
    return CastMeleeSpellAction::isUseful() && !AI_VALUE2(bool, "has totem", name);
}
