/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ReachTargetActions.h"
#include "Event.h"
#include "Playerbot.h"
#include "ServerFacade.h"

bool ReachTargetAction::Execute(Event event)
{
    return MoveTo(AI_VALUE(Unit*, GetTargetName()), distance);
}

bool ReachTargetAction::isUseful()
{
    return sServerFacade->IsDistanceGreaterThan(AI_VALUE2(float, "distance", GetTargetName()), (distance + sPlayerbotAIConfig->contactDistance));
}

std::string const& ReachTargetAction::GetTargetName()
{
    return "current target";
}

bool CastReachTargetSpellAction::isUseful()
{
    return sServerFacade->IsDistanceGreaterThan(AI_VALUE2(float, "distance", "current target"), (distance + sPlayerbotAIConfig->contactDistance));
}

std::string const& ReachPartyMemberToHealAction::GetTargetName()
{
    return "party member to heal";
}
