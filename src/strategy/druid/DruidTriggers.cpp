/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DruidTriggers.h"
#include "Playerbot.h"

bool MarkOfTheWildOnPartyTrigger::IsActive()
{
    return BuffOnPartyTrigger::IsActive() && !botAI->HasAura("gift of the wild", GetTarget());
}

bool MarkOfTheWildTrigger::IsActive()
{
    return BuffTrigger::IsActive() && !botAI->HasAura("gift of the wild", GetTarget());
}

bool ThornsOnPartyTrigger::IsActive()
{
    return BuffOnPartyTrigger::IsActive() && !botAI->HasAura("thorns", GetTarget());
}

bool ThornsTrigger::IsActive()
{
    return BuffTrigger::IsActive() && !botAI->HasAura("thorns", GetTarget());
}

bool BearFormTrigger::IsActive()
{
    return !botAI->HasAnyAuraOf(bot, "bear form", "dire bear form", nullptr);
}

bool TreeFormTrigger::IsActive()
{
    return !botAI->HasAura("tree of life", bot);
}

bool CatFormTrigger::IsActive()
{
    return !botAI->HasAura("cat form", bot);
}