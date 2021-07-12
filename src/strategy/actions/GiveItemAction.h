/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "InventoryAction.h"
class GiveItemAction : public InventoryAction
{
    public:
        GiveItemAction(PlayerbotAI* botAI, std::string const& name, std::string const& item) : InventoryAction(botAI, name), item(item) { }

        bool Execute(Event event) override;
        bool isUseful() override;
        Unit* GetTarget() override;

    protected:
        std::string item;
};

class GiveFoodAction : public GiveItemAction
{
    public:
        GiveFoodAction(PlayerbotAI* botAI) : GiveItemAction(botAI, "give food", "conjured food") { }

        Unit* GetTarget() override;
};

class GiveWaterAction : public GiveItemAction
{
    public:
        GiveWaterAction(PlayerbotAI* botAI) : GiveItemAction(botAI, "give water", "conjured water") { }

        Unit* GetTarget() override;
};
