#pragma once

#include "../Action.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class MovementAction : public Action {
    public:
        MovementAction(PlayerbotAI* botAI, string name) : Action(ai, name)
        {
            bot = botAI->GetBot();
        }

    protected:
        bool MoveNear(uint32 mapId, float x, float y, float z, float distance = sPlayerbotAIConfig->contactDistance);
        bool MoveTo(uint32 mapId, float x, float y, float z, bool idle = false);
        bool MoveTo(Unit* target, float distance = 0.0f);
        bool MoveNear(WorldObject* target, float distance = sPlayerbotAIConfig->contactDistance);
        float GetFollowAngle();
        bool Follow(Unit* target, float distance = sPlayerbotAIConfig->followDistance);
        bool Follow(Unit* target, float distance, float angle);
        void WaitForReach(float distance);
        bool IsMovingAllowed(Unit* target);
        bool IsMovingAllowed(uint32 mapId, float x, float y, float z);
        bool IsMovingAllowed();
        bool Flee(Unit *target);
        void ClearIdleState();
        void UpdateMovementState();
    };

    class FleeAction : public MovementAction
    {
    public:
        FleeAction(PlayerbotAI* botAI, float distance = sPlayerbotAIConfig->spellDistance) : MovementAction(ai, "flee")
        {
			this->distance = distance;
		}

        virtual bool Execute(Event event);

	private:
		float distance;
    };

    class FleeWithPetAction : public MovementAction
    {
    public:
        FleeWithPetAction(PlayerbotAI* botAI) : MovementAction(ai, "flee with pet") {}

        virtual bool Execute(Event event);
    };

    class RunAwayAction : public MovementAction
    {
    public:
        RunAwayAction(PlayerbotAI* botAI) : MovementAction(ai, "runaway") {}
        virtual bool Execute(Event event);
    };

    class MoveToLootAction : public MovementAction
    {
    public:
        MoveToLootAction(PlayerbotAI* botAI) : MovementAction(ai, "move to loot") {}
        virtual bool Execute(Event event);
    };

    class MoveOutOfEnemyContactAction : public MovementAction
    {
    public:
        MoveOutOfEnemyContactAction(PlayerbotAI* botAI) : MovementAction(ai, "move out of enemy contact") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class SetFacingTargetAction : public MovementAction
    {
    public:
        SetFacingTargetAction(PlayerbotAI* botAI) : MovementAction(ai, "set facing") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class SetBehindTargetAction : public MovementAction
    {
    public:
        SetBehindTargetAction(PlayerbotAI* botAI) : MovementAction(ai, "set behind") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class MoveOutOfCollisionAction : public MovementAction
    {
    public:
        MoveOutOfCollisionAction(PlayerbotAI* botAI) : MovementAction(ai, "move out of collision") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

}
