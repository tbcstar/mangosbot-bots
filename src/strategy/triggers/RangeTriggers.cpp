/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RangeTriggers.h"
#include "../../Playerbot.h"

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

virtual bool EnemyIsCloseTrigger::IsActive()
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

