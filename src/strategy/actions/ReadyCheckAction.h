#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class ReadyCheckAction : public InventoryAction
    {
    public:
        ReadyCheckAction(PlayerbotAI* botAI, string name = "ready check") : InventoryAction(ai, name) {}

        virtual bool Execute(Event event);

    protected:
        bool ReadyCheck();
    };

    class FinishReadyCheckAction : public ReadyCheckAction
    {
    public:
        FinishReadyCheckAction(PlayerbotAI* botAI) : ReadyCheckAction(ai, "finish ready check") {}

        virtual bool Execute(Event event);
    };

}
