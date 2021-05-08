#pragma once

#include "../Action.h"

namespace ai
{
    class TellTargetAction : public Action
    {
    public:
        TellTargetAction(PlayerbotAI* botAI) : Action(ai, "tell target") {}
        virtual bool Execute(Event event);
    };

    class TellAttackersAction : public Action
    {
    public:
        TellAttackersAction(PlayerbotAI* botAI) : Action(ai, "tell attackers") {}
        virtual bool Execute(Event event);
    };

}
