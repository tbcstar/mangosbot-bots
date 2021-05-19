/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ChooseRpgTargetAction.h"
#include "../Event.h"
#include "../values/PossibleRpgTargetsValue.h"
#include "../../Playerbot.h"

bool ChooseRpgTargetAction::Execute(Event event)
{
    GuidVector possibleTargets = AI_VALUE(GuidVector, "possible rpg targets");
    if (possibleTargets.empty())
        return false;

    std::vector<Unit*> units;
    for (GuidVector::iterator i = possibleTargets.begin(); i != possibleTargets.end(); ++i)
    {
        if (Unit* unit = botAI->GetUnit(*i))
            units.push_back(unit);
    }

    if (units.empty())
    {
        sLog->outDetail("%s can't choose RPG target: all %d are not available", bot->GetName(), possibleTargets.size());
        return false;
    }

    Unit* target = units[urand(0, units.size() - 1)];
    if (!target)
        return false;

    context->GetValue<ObjectGuid>("rpg target")->Set(target->GetGUID());
    return true;
}

bool ChooseRpgTargetAction::isUseful()
{
    return !context->GetValue<ObjectGuid>("rpg target")->Get();
}
