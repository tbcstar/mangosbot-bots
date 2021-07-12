/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "InventoryAction.h"
#include "MovementActions.h"

class GameObject;
class LootObject;

class LootAction : public InventoryAction
{
    public:
        LootAction(PlayerbotAI* botAI) : InventoryAction(botAI, "loot") { }

        bool Execute(Event event) override;
};

class OpenLootAction : public MovementAction
{
    public:
        OpenLootAction(PlayerbotAI* botAI) : MovementAction(botAI, "open loot") { }

        bool Execute(Event event) override;

    private:
        bool DoLoot(LootObject& lootObject);
        uint32 GetOpeningSpell(LootObject& lootObject);
        uint32 GetOpeningSpell(LootObject& lootObject, GameObject* go);
        bool CanOpenLock(LootObject& lootObject, SpellInfo const* spellInfo, GameObject* go);
        bool CanOpenLock(uint32 skillId, uint32 reqSkillValue);
};

class StoreLootAction : public MovementAction
{
    public:
        StoreLootAction(PlayerbotAI* botAI) : MovementAction(botAI, "store loot") { }

        bool Execute(Event event) override;
        static bool IsLootAllowed(uint32 itemid, PlayerbotAI* botAI);
};

class ReleaseLootAction : public MovementAction
{
    public:
        ReleaseLootAction(PlayerbotAI* botAI) : MovementAction(botAI, "release loot") { }

        bool Execute(Event event) override;
};
