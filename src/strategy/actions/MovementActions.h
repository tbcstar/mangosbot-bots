/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"
#include "PlayerbotAIConfig.h"

class Event;
class PlayerbotAI;
class Unit;
class WorldObject;

class MovementAction : public Action
{
    public:
        MovementAction(PlayerbotAI* botAI, std::string const& name);

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
        FleeAction(PlayerbotAI* botAI, float distance = sPlayerbotAIConfig->spellDistance) : MovementAction(botAI, "flee"), distance(distance) { }

        bool Execute(Event event) override;

	private:
		float distance;
};

class FleeWithPetAction : public MovementAction
{
    public:
        FleeWithPetAction(PlayerbotAI* botAI) : MovementAction(botAI, "flee with pet") { }

        bool Execute(Event event) override;
};

class RunAwayAction : public MovementAction
{
    public:
        RunAwayAction(PlayerbotAI* botAI) : MovementAction(botAI, "runaway") { }

        bool Execute(Event event) override;
};

class MoveToLootAction : public MovementAction
{
    public:
        MoveToLootAction(PlayerbotAI* botAI) : MovementAction(botAI, "move to loot") { }

        bool Execute(Event event) override;
};

class MoveOutOfEnemyContactAction : public MovementAction
{
    public:
        MoveOutOfEnemyContactAction(PlayerbotAI* botAI) : MovementAction(botAI, "move out of enemy contact") { }

        bool Execute(Event event) override;
        bool isUseful() const override;
};

class SetFacingTargetAction : public MovementAction
{
    public:
        SetFacingTargetAction(PlayerbotAI* botAI) : MovementAction(botAI, "std::set facing") { }

        bool Execute(Event event) override;
        bool isUseful() const override;
};

class SetBehindTargetAction : public MovementAction
{
    public:
        SetBehindTargetAction(PlayerbotAI* botAI) : MovementAction(botAI, "std::set behind") { }

        bool Execute(Event event) override;
        bool isUseful() const override;
};

class MoveOutOfCollisionAction : public MovementAction
{
    public:
        MoveOutOfCollisionAction(PlayerbotAI* botAI) : MovementAction(botAI, "move out of collision") { }

        bool Execute(Event event) override;
        bool isUseful() const override;
};
