#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class DebugAction : public Action
    {
    public:
        DebugAction(PlayerbotAI* botAI) : Action(ai, "Debug") {}

        virtual bool Execute(Event event);
    };

}
