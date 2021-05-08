#pragma once

#include "../Action.h"

namespace ai
{
    class RangeAction : public Action
    {
    public:
        RangeAction(PlayerbotAI* botAI) : Action(ai, "range")
        {}

        virtual bool Execute(Event event);

    private:
        void PrintRange(string type);

    };
}
