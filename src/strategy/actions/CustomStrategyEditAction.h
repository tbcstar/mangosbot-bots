#pragma once

#include "../Action.h"

namespace ai
{
    class CustomStrategyEditAction : public Action {
    public:
        CustomStrategyEditAction(PlayerbotAI* botAI) : Action(ai, "cs") {}
        virtual bool Execute(Event event);

    private:
        bool PrintHelp();
        bool PrintActionLine(uint32 idx, string command);
        bool Print(string name);
        bool Edit(string name, uint32 idx, string command);
    };

}
