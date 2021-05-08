#pragma once

#include "../Action.h"
#include "MovementActions.h"

namespace ai
{
    class PositionAction : public Action
    {
    public:
        PositionAction(PlayerbotAI* botAI) : Action(ai, "position")
        {}

        virtual bool Execute(Event event);
    };

    class MoveToPositionAction : public MovementAction
    {
    public:
        MoveToPositionAction(PlayerbotAI* botAI, string name, string qualifier, bool idle = false) :
            MovementAction(ai, name), qualifier(qualifier), idle(idle)
        {}

        virtual bool Execute(Event event);
        virtual bool isUseful();

    protected:
        string qualifier;
        bool idle;
    };

    class GuardAction : public MoveToPositionAction
    {
    public:
        GuardAction(PlayerbotAI* botAI) : MoveToPositionAction(ai, "move to position", "guard") {}
    };

    class SetReturnPositionAction : public Action
    {
    public:
        SetReturnPositionAction(PlayerbotAI* botAI) : Action(ai, "set return position")
        {}

        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class ReturnAction : public MoveToPositionAction
    {
    public:
        ReturnAction(PlayerbotAI* botAI) : MoveToPositionAction(ai, "return", "return", true) {}

        virtual bool isUseful();
    };

}
