#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class TellItemCountAction : public InventoryAction {
    public:
        TellItemCountAction(PlayerbotAI* botAI) : InventoryAction(ai, "c") {}
        virtual bool Execute(Event event);
    };

}