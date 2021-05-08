#pragma once

#include "../Action.h"

namespace ai
{
    class RtiAction : public Action
    {
    public:
        RtiAction(PlayerbotAI* botAI) : Action(ai, "rti")
        {}

        virtual bool Execute(Event event);

    private:
        void AppendRti(ostringstream & out, string type);

    };

    class MarkRtiAction : public Action
    {
    public:
        MarkRtiAction(PlayerbotAI* botAI) : Action(ai, "mark rti")
        {}

        virtual bool Execute(Event event);
    };
}
