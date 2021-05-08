#pragma once

#include "../Action.h"
#include "MovementActions.h"

namespace ai
{
    class StayActionBase : public MovementAction {
    public:
        StayActionBase(PlayerbotAI* botAI, string name) : MovementAction(ai, name) {}

    protected:
        bool Stay();
    };

    class StayAction : public StayActionBase {
    public:
        StayAction(PlayerbotAI* botAI) : StayActionBase(ai, "stay") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class SitAction : public StayActionBase {
    public:
        SitAction(PlayerbotAI* botAI) : StayActionBase(ai, "sit") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

}
