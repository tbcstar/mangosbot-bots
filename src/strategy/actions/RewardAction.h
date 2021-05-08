#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class RewardAction : public InventoryAction {
    public:
        RewardAction(PlayerbotAI* botAI) : InventoryAction(ai, "reward") {}
        virtual bool Execute(Event event);

    private:
        bool Reward(uint32 itemId, Object* pNpc);
    };

}