#pragma once

#include "../Action.h"
#include "MovementActions.h"
#include "../../PlayerbotAIConfig.h"
#include "../../ServerFacade.h"

namespace ai
{
    class ReachTargetAction : public MovementAction
    {
    public:
        ReachTargetAction(PlayerbotAI* botAI, string name, float distance) : MovementAction(ai, name)
		{
            this->distance = distance;
        }
        virtual bool Execute(Event event)
		{
			return MoveTo(AI_VALUE(Unit*, GetTargetName()), distance);
        }
        virtual bool isUseful()
		{
            return sServerFacade->IsDistanceGreaterThan(AI_VALUE2(float, "distance", GetTargetName()), (distance + sPlayerbotAIConfig->contactDistance));
        }
        virtual string GetTargetName() { return "current target"; }

    protected:
        float distance;
    };

    class CastReachTargetSpellAction : public CastSpellAction
    {
    public:
        CastReachTargetSpellAction(PlayerbotAI* botAI, string spell, float distance) : CastSpellAction(ai, spell)
		{
            this->distance = distance;
        }
		virtual bool isUseful()
		{
			return sServerFacade->IsDistanceGreaterThan(AI_VALUE2(float, "distance", "current target"), (distance + sPlayerbotAIConfig->contactDistance));
		}

    protected:
        float distance;
    };

    class ReachMeleeAction : public ReachTargetAction
	{
    public:
        ReachMeleeAction(PlayerbotAI* botAI) : ReachTargetAction(ai, "reach melee", sPlayerbotAIConfig->meleeDistance) {}
    };

    class ReachSpellAction : public ReachTargetAction
	{
    public:
        ReachSpellAction(PlayerbotAI* botAI) : ReachTargetAction(ai, "reach spell", botAI->GetRange("spell")) {}
    };

    class ReachPartyMemberToHealAction : public ReachTargetAction
	{
    public:
        ReachPartyMemberToHealAction(PlayerbotAI* botAI) : ReachTargetAction(ai, "reach party member to heal", botAI->GetRange("heal")) {}
        virtual string GetTargetName() { return "party member to heal"; }
    };
}
