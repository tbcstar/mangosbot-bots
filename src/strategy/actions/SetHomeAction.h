#pragma once

#include "MovementActions.h"

namespace ai
{
    class SetHomeAction : public MovementAction {
    public:
        SetHomeAction(PlayerbotAI* botAI) : MovementAction(ai, "home") {}
        virtual bool Execute(Event event);
    };
}
