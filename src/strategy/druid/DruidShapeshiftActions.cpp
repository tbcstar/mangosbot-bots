/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DruidShapeshiftActions.h"
#include "Playerbot.h"

bool CastBearFormAction::isPossible() const
{
    return CastBuffSpellAction::isPossible() && !botAI->HasAura("dire bear form", GetTarget());
}

bool CastBearFormAction::isUseful()
{
    return CastBuffSpellAction::isUseful() && !botAI->HasAura("dire bear form", GetTarget());
}

NextAction** CastDireBearFormAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("bear form"), nullptr), CastSpellAction::getAlternatives());
}

bool CastTravelFormAction::isUseful()
{
    bool firstmount = bot->getLevel() >= 20;

    // useful if no mount or with wsg flag
    return !bot->IsMounted() && (!firstmount || (bot->HasAura(23333) || bot->HasAura(23335))) && !ai->HasAura("dash", bot);
}

bool CastCasterFormAction::isUseful()
{
    return botAI->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form",
        "flight form", "swift flight form", "moonkin form", "tree of life", nullptr);
}

bool CastCasterFormAction::Execute(Event event)
{
    botAI->RemoveShapeshift();
    return true;
}
