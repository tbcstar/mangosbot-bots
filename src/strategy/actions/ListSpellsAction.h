/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DBCStructure.h"
#include "InventoryAction.h"

class Event;
class PlayerbotAI;

class ListSpellsAction : public InventoryAction
{
    public:
        ListSpellsAction(PlayerbotAI* botAI) : InventoryAction(botAI, "spells") { }

        bool Execute(Event event) override;

    private:
        static std::map<uint32, SkillLineAbilityEntry const*> skillSpells;
        static std::set<uint32> vendorItems;
};
