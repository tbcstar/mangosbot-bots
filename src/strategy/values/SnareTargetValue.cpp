#include "botpch.h"
#include "../../playerbot.h"
#include "SnareTargetValue.h"
#include "../../PlayerbotAIConfig.h"
#include "../../ServerFacade.h"
#include "MotionGenerators/TargetedMovementGenerator.h"

using namespace ai;

Unit* SnareTargetValue::Calculate()
{
    string spell = qualifier;

    list<ObjectGuid> attackers = botAI->GetAiObjectContext()->GetValue<list<ObjectGuid> >("attackers")->Get();
    Unit* target = botAI->GetAiObjectContext()->GetValue<Unit*>("current target")->Get();
    for (list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* unit = botAI->GetUnit(*i);
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
            if (!chaseTarget) continue;
            Player* chaseTargetPlayer = sObjectMgr->GetPlayer(chaseTarget->GetGUID());
            if (chaseTargetPlayer && !botAI->IsTank(chaseTargetPlayer)) {
                return unit;
            }
        }
    }

    return NULL;
}
