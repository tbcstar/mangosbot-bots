#pragma once

#include "../Action.h"
#include "QuestAction.h"

namespace ai
{
    class CheckValuesAction : public Action
    {
    public:
        CheckValuesAction(PlayerbotAI* botAI);
        virtual bool Execute(Event event);
    };
}
