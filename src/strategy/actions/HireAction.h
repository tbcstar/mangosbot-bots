#pragma once

#include "../Action.h"

namespace ai
{
    class HireAction : public Action {
    public:
        HireAction(PlayerbotAI* botAI) : Action(ai, "hire") {}
        virtual bool Execute(Event event);

    };

}
