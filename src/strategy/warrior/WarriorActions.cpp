/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "WarriorActions.h"
#include "../../Playerbot.h"

bool CastSunderArmorAction::isUseful() const
{
    return CastSpellAction::isUseful();
}

bool CastBattleShoutAction::isUseful() const
{
    return CastSpellAction::isUseful();
}

bool CastBattleShoutTauntAction::isUseful() const
{
    return CastSpellAction::isUseful();
}
