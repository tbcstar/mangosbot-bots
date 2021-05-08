#pragma once

#include "../Action.h"
#include "AttackAction.h"

namespace ai
{
    class DpsAoeAction : public AttackAction
    {
    public:
        DpsAoeAction(PlayerbotAI* botAI) : AttackAction(ai, "dps aoe") {}

        virtual string GetTargetName() { return "dps aoe target"; }
    };

    class DpsAssistAction : public AttackAction
    {
    public:
        DpsAssistAction(PlayerbotAI* botAI) : AttackAction(ai, "dps assist") {}

        virtual string GetTargetName() { return "dps target"; }
    };

    class TankAssistAction : public AttackAction
    {
    public:
        TankAssistAction(PlayerbotAI* botAI) : AttackAction(ai, "tank assist") {}
        virtual string GetTargetName() { return "tank target"; }
    };

    class AttackAnythingAction : public AttackAction
    {
    public:
        AttackAnythingAction(PlayerbotAI* botAI) : AttackAction(ai, "attack anything") {}
        virtual string GetTargetName() { return "grind target"; }
        virtual bool Execute(Event event);
        virtual bool isUseful() {
            return GetTarget() &&
                (!AI_VALUE(list<ObjectGuid>, "nearest non bot players").empty() &&
                    AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig->mediumHealth &&
                    (!AI_VALUE2(uint8, "mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig->mediumMana)
                ) || AI_VALUE2(bool, "combat", "self target")
                ;
        }
        virtual bool isPossible()
        {
            return AttackAction::isPossible() && GetTarget();
        }
    };

    class AttackLeastHpTargetAction : public AttackAction
    {
    public:
        AttackLeastHpTargetAction(PlayerbotAI* botAI) : AttackAction(ai, "attack least hp target") {}
        virtual string GetTargetName() { return "least hp target"; }
    };

    class AttackEnemyPlayerAction : public AttackAction
    {
    public:
        AttackEnemyPlayerAction(PlayerbotAI* botAI) : AttackAction(ai, "attack enemy player") {}
        virtual string GetTargetName() { return "enemy player target"; }
    };

    class AttackRtiTargetAction : public AttackAction
    {
    public:
        AttackRtiTargetAction(PlayerbotAI* botAI) : AttackAction(ai, "attack rti target") {}
        virtual string GetTargetName() { return "rti target"; }
    };

    class DropTargetAction : public Action
    {
    public:
        DropTargetAction(PlayerbotAI* botAI) : Action(ai, "drop target") {}

        virtual bool Execute(Event event);
    };

}
