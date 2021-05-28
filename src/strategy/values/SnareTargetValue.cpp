/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "SnareTargetValue.h"
#include "../../Playerbot.h"
#include "../../ServerFacade.h"

Unit* SnareTargetValue::Calculate()
{
    std::string const& spell = qualifier;

    GuidVector attackers = botAI->GetAiObjectContext()->GetValue<GuidVector>("attackers")->Get();
    Unit* target = botAI->GetAiObjectContext()->GetValue<Unit*>("current target")->Get();
    for (ObjectGuid const guid : attackers)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || unit == target)
            continue;

        if (bot->GetDistance(unit) > botAI->GetRange("spell"))
            continue;

        Unit* chaseTarget;
        switch (unit->GetMotionMaster()->GetCurrentMovementGeneratorType())
        {
            case FLEEING_MOTION_TYPE:
                return unit;
            case CHASE_MOTION_TYPE:
                chaseTarget = sServerFacade->GetChaseTarget(unit);
                if (!chaseTarget)
                    continue;
                if (Player* chaseTargetPlayer = ObjectAccessor::FindPlayer(chaseTarget->GetGUID()))
                    if (!botAI->IsTank(chaseTargetPlayer))
                        return unit;
        }
    }

    return nullptr;
}
