/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PriestTriggers.h"
#include "Playerbot.h"

bool PowerWordFortitudeOnPartyTrigger::IsActive()
{
    return BuffOnPartyTrigger::IsActive() && !botAI->HasAura("prayer of fortitude", GetTarget());
}

bool PowerWordFortitudeTrigger::IsActive()
{
    return BuffTrigger::IsActive() && !botAI->HasAura("prayer of fortitude", GetTarget());
}

bool DivineSpiritOnPartyTrigger::IsActive()
{
    return BuffOnPartyTrigger::IsActive() && !botAI->HasAura("prayer of spirit", GetTarget());
}

bool DivineSpiritTrigger::IsActive()
{
    return BuffTrigger::IsActive() && !botAI->HasAura("prayer of spirit", GetTarget());
}

bool InnerFireTrigger::IsActive()
{
    Unit* target = GetTarget();
    return SpellTrigger::IsActive() && !botAI->HasAura(spell, target);
}

bool ShadowformTrigger::IsActive()
{
    return !botAI->HasAura("shadowform", bot);
}
