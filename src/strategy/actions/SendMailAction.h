#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class SendMailAction : public InventoryAction
    {
    public:
        SendMailAction(PlayerbotAI* botAI) : InventoryAction(ai, "sendmail") {}

        virtual bool Execute(Event event);
    };

}