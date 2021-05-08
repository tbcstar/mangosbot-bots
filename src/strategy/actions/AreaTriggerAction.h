#pragma once

#include "../Action.h"
#include "MovementActions.h"
#include "../values/LastMovementValue.h"

namespace ai
{
    class ReachAreaTriggerAction : public MovementAction {
    public:
        ReachAreaTriggerAction(PlayerbotAI* botAI) : MovementAction(ai, "reach area trigger") {}

        virtual bool Execute(Event event);
    };

    class AreaTriggerAction : public MovementAction {
    public:
        AreaTriggerAction(PlayerbotAI* botAI) : MovementAction(ai, "area trigger") {}

        virtual bool Execute(Event event);
    };

}