#include "botpch.h"
#include "../../playerbot.h"
#include "LootStrategyValue.h"
#include "../values/ItemUsageValue.h"

using namespace botAI;
using namespace std;

namespace botAI
{
    class NormalLootStrategy : public LootStrategy
    {
    public:
        virtual bool CanLoot(ItemTemplate const* proto, AiObjectContext* context)
        {
            ostringstream out; out << proto->ItemId;
            ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", out.str());
            return usage != ITEM_USAGE_NONE;
        }
        std::string const& getName() override { return "normal"; }
    };

    class GrayLootStrategy : public NormalLootStrategy
    {
    public:
        virtual bool CanLoot(ItemTemplate const* proto, AiObjectContext* context)
        {
            return NormalLootStrategy::CanLoot(proto, context) || proto->Quality == ITEM_QUALITY_POOR;
        }
        std::string const& getName() override { return "gray"; }
    };

    class DisenchantLootStrategy : public NormalLootStrategy
    {
    public:
        virtual bool CanLoot(ItemTemplate const* proto, AiObjectContext* context)
        {
            return NormalLootStrategy::CanLoot(proto, context) ||
                    (proto->Quality >= ITEM_QUALITY_UNCOMMON && proto->Bonding != BIND_WHEN_PICKED_UP &&
                    (proto->Class == ITEM_CLASS_ARMOR || proto->Class == ITEM_CLASS_WEAPON));
        }
        std::string const& getName() override { return "disenchant"; }
    };

    class AllLootStrategy : public LootStrategy
    {
    public:
        virtual bool CanLoot(ItemTemplate const* proto, AiObjectContext* context)
        {
            return true;
        }
        std::string const& getName() override { return "all"; }
    };
}

LootStrategy *LootStrategyValue::normal = new NormalLootStrategy();
LootStrategy *LootStrategyValue::gray = new GrayLootStrategy();
LootStrategy *LootStrategyValue::disenchant = new DisenchantLootStrategy();
LootStrategy *LootStrategyValue::all = new AllLootStrategy();

LootStrategy* LootStrategyValue::instance(string strategy)
{
    if (strategy == "*" || strategy == "all")
        return all;

    if (strategy == "g" || strategy == "gray")
        return gray;

    if (strategy == "d" || strategy == "e" || strategy == "disenchant" || strategy == "enchant")
        return disenchant;

    return normal;
}

string LootStrategyValue::Save()
{
    return value ? value->GetName() : "?";
}

bool LootStrategyValue::Load(string text)
{
    value = LootStrategyValue::instance(text);
    return true;
}
