/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "QueryItemUsageAction.h"
class TradeStatusAction : public QueryItemUsageAction
{
    public:
        TradeStatusAction(PlayerbotAI* botAI) : QueryItemUsageAction(botAI, "accept trade") { }

        bool Execute(Event event) override;

    private:
        void BeginTrade();
        bool CheckTrade();
        int32 CalculateCost(Player* player, bool sell);
};
