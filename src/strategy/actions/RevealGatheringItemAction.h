#pragma once

#include "../Action.h"
#include "MovementActions.h"
#include "../values/LastMovementValue.h"

namespace ai
{
    class RevealGatheringItemAction : public Action {
    public:
        RevealGatheringItemAction(PlayerbotAI* botAI) : Action(ai, "reveal gathering item") {}

        virtual bool Execute(Event event);
    };

}
