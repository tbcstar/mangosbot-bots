#pragma once

#include "../Action.h"

namespace ai
{
    class TellSpellAction : public Action
    {
    public:
        TellSpellAction(PlayerbotAI* botAI) : Action(ai, "spell") {}

        virtual bool Execute(Event event);
    };

    class TellCastFailedAction : public Action 
    {
    public:
        TellCastFailedAction(PlayerbotAI* botAI) : Action(ai, "tell cast failed") {}

        virtual bool Execute(Event event);
    };
}
