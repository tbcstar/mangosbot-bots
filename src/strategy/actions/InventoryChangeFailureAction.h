#pragma once

#include "../Action.h"

namespace ai
{
    class InventoryChangeFailureAction : public Action {
    public:
        InventoryChangeFailureAction(PlayerbotAI* botAI) : Action(ai, "inventory change failure") {}
        virtual bool Execute(Event event);

    private:
        static map<InventoryResult, string> messages;
    };
}