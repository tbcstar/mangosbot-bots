#pragma once

#include "../Action.h"

namespace ai
{
    class RemoveAuraAction : public Action
    {
    public:
        RemoveAuraAction(PlayerbotAI* botAI);
        virtual bool Execute(Event event);
    };
}
