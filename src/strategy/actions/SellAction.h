/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "InventoryAction.h"

class Event;
class FindItemVisitor;
class Item;
class PlayerbotAI;

class SellAction : public InventoryAction
{
    public:
        SellAction(PlayerbotAI* botAI) : InventoryAction(botAI, "sell") { }

        bool Execute(Event event) override;
        void Sell(FindItemVisitor* visitor);
        void Sell(Item* item);

};
