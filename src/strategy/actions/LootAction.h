#pragma once

#include "../Action.h"
#include "../../LootObjectStack.h"
#include "MovementActions.h"

namespace ai
{
    class LootAction : public MovementAction
    {
    public:
        LootAction(PlayerbotAI* botAI) : MovementAction(ai, "loot") {}
        virtual bool Execute(Event event);
    };

    class OpenLootAction : public MovementAction
    {
    public:
        OpenLootAction(PlayerbotAI* botAI) : MovementAction(ai, "open loot") {}
        virtual bool Execute(Event event);

    private:
        bool DoLoot(LootObject& lootObject);
        uint32 GetOpeningSpell(LootObject& lootObject);
        uint32 GetOpeningSpell(LootObject& lootObject, GameObject* go);
        bool CanOpenLock(LootObject& lootObject, const SpellEntry* pSpellInfo, GameObject* go);
        bool CanOpenLock(uint32 skillId, uint32 reqSkillValue);
    };

    class StoreLootAction : public MovementAction
    {
    public:
        StoreLootAction(PlayerbotAI* botAI) : MovementAction(ai, "store loot") {}
        virtual bool Execute(Event event);
        static bool IsLootAllowed(uint32 itemid, PlayerbotAI* botAI);
    };

    class ReleaseLootAction : public MovementAction
    {
    public:
        ReleaseLootAction(PlayerbotAI* botAI) : MovementAction(ai, "release loot") {}
        virtual bool Execute(Event event);
    };
}
