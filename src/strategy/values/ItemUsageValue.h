/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NamedObjectContext.h"
#include "Value.h"

class PlayerbotAI;

struct ItemTemplate;

enum ItemUsage
{
    ITEM_USAGE_NONE         = 0,
    ITEM_USAGE_EQUIP        = 1,
    ITEM_USAGE_REPLACE      = 2,
    ITEM_USAGE_SKILL        = 3,
    ITEM_USAGE_USE          = 4,
    ITEM_USAGE_GUILD_TASK   = 5,
    ITEM_USAGE_DISENCHANT   = 6
};

class ItemUsageValue : public CalculatedValue<ItemUsage>, public Qualified
{
	public:
        ItemUsageValue(PlayerbotAI* botAI) : CalculatedValue<ItemUsage>(botAI) { }

        ItemUsage Calculate() override;

    private:
        ItemUsage QueryItemUsageForEquip(ItemTemplate const* proto);
        bool IsItemUsefulForSkill(ItemTemplate const* proto);
};
