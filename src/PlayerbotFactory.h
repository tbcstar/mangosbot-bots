/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "strategy/actions/InventoryAction.h"

class Item;
class Player;

struct ItemTemplate;

class PlayerbotFactory : public InventoryAction
{
    public:
        PlayerbotFactory(Player* bot, uint32 level, uint32 itemQuality = 0);

        static ObjectGuid GetRandomBot();
        static void Init();
        void Refresh();
        void Randomize(bool incremental);

    private:
        void Prepare();
        void InitSecondEquipmentSet();
        void InitEquipment(bool incremental);
        bool CanEquipItem(ItemTemplate const* proto, uint32 desiredQuality);
        bool CanEquipUnseenItem(uint8 slot, uint16& dest, uint32 item);
        void InitSkills();
        void InitTradeSkills();
        void UpdateTradeSkills();
        void SetRandomSkill(uint16 id);
        void InitSpells();
        void ClearSpells();
        void ClearSkills();
        void InitAvailableSpells();
        void InitSpecialSpells();
        void InitTalents();
        void InitTalents(uint32 specNo);
        void InitQuests(std::list<uint32>& questMap);
        void InitPet();
        void ClearInventory();
        void InitAmmo();
        void InitMounts();
        void InitPotions();
        void InitFood();
        bool CanEquipArmor(ItemTemplate const* proto);
        bool CanEquipWeapon(ItemTemplate const* proto);
        void EnchantItem(Item* item);
        void AddItemStats(uint32 mod, uint8& sp, uint8& ap, uint8& tank);
        bool CheckItemStats(uint8 sp, uint8 ap, uint8 tank);
        void CancelAuras();
        bool IsDesiredReplacement(Item* item);
        void InitBags();
        void InitInventory();
        void InitInventoryTrade();
        void InitInventoryEquip();
        void InitInventorySkill();
        Item* StoreItem(uint32 itemId, uint32 count);
        void InitGuild();
        void InitImmersive();
        void InitStats();
        static void AddPrevQuests(uint32 questId, std::list<uint32>& questIds);

        uint32 level;
        uint32 itemQuality;
        static uint32 tradeSkills[];
        static std::list<uint32> classQuestIds;
        static std::list<uint32> specialQuestIds;
};
