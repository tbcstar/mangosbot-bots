#pragma once

#include "../Action.h"
#include "QuestAction.h"

namespace ai
{
    class GreetAction : public Action
    {
    public:
        GreetAction(PlayerbotAI* botAI);
        virtual bool Execute(Event event);
    };
}
