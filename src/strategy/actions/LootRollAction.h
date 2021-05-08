#pragma once

#include "../Action.h"
#include "QueryItemUsageAction.h"
#include "LootAction.h"

namespace ai
{
    class LootRollAction : public QueryItemUsageAction {
    public:
        LootRollAction(PlayerbotAI* botAI) : QueryItemUsageAction(ai, "loot roll") {}
        virtual bool Execute(Event event);

    private:
        RollVote CalculateRollVote(ItemPrototype const *proto);
    };

}
