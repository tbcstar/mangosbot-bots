#pragma once

#include "../Action.h"

namespace ai
{
    class TellReputationAction : public Action {
    public:
        TellReputationAction(PlayerbotAI* botAI) : Action(ai, "reputation") {}
        virtual bool Execute(Event event);

    private:

    };

}