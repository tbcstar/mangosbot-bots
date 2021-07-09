/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RangeTriggers.h"
#include "Playerbot.h"
#include "ServerFacade.h"

bool EnemyTooCloseForSpellTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    return target && sServerFacade->IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "current target"), botAI->GetRange("spell") / 2);
}

bool EnemyTooCloseForShootTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    return target && sServerFacade->IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "current target"), botAI->GetRange("shoot") / 2);
}

bool EnemyTooCloseForMeleeTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    return target && AI_VALUE2(bool, "inside target", "current target");
}

bool EnemyIsCloseTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    return target && sServerFacade->IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "current target"), sPlayerbotAIConfig->tooCloseDistance);
}

bool OutOfRangeTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, GetTargetName());
    return target && sServerFacade->IsDistanceGreaterThan(AI_VALUE2(float, "distance", GetTargetName()), distance);
}

bool FarFromMasterTrigger::IsActive()
{
    return sServerFacade->IsDistanceGreaterThan(AI_VALUE2(float, "distance", "master target"), distance);
}

bool HearthIsFasterTrigger::IsActive()
{
    if (!bot->HasItemCount(6948, 1, false))
        return false;

    if (!sServerFacade.IsSpellReady(bot, 8690))
        return false;

    WorldPosition longMove = AI_VALUE(WorldPosition, "last long move");

    if (!longMove)
        return false;

    WorldPosition hearthBind = AI_VALUE(WorldPosition, "home bind");

    return AI_VALUE2(float, "distance", "last long move") > hearthBind.distance(longMove) + 200;
}
