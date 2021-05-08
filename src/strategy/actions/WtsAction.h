#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class WtsAction : public InventoryAction {
    public:
        WtsAction(PlayerbotAI* botAI) : InventoryAction(ai, "wts") {}

    public:
        virtual bool Execute(Event event);
    };

}
