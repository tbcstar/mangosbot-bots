#pragma once

#include "../Action.h"

namespace ai
{
    class RepairAllAction : public Action 
    {
    public:
        RepairAllAction(PlayerbotAI* botAI) : Action(ai, "repair") {}
        virtual bool Execute(Event event);
    };
}