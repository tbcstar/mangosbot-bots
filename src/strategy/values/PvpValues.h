/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Value.h"

class PlayerbotAI;
class Unit;

class BgTypeValue : public ManualSetValue<uint32>
{
    public:
        BgTypeValue(PlayerbotAI* ai) : ManualSetValue<uint32>(ai, 0, "bg type") { }
};

class ArenaTypeValue : public ManualSetValue<uint32>
{
    public:
        ArenaTypeValue(PlayerbotAI* ai) : ManualSetValue<uint32>(ai, 0, "arena type") { }
};

class BgRoleValue : public ManualSetValue<uint32>
{
    public:
        BgRoleValue(PlayerbotAI* ai) : ManualSetValue<uint32>(ai, 0, "bg role") { }
};

class BgMastersValue : public SingleCalculatedValue<std::vector<CreatureData const*>>, public Qualified
{
    public:
        BgMastersValue(PlayerbotAI* ai) : SingleCalculatedValue<std::vector<CreatureData const*>>(ai, "bg masters") {}

        std::vector<CreatureData const*> Calculate() override;
};

class BgMasterValue : public CDPairCalculatedValue, public Qualified
{
    public:
        BgMasterValue(PlayerbotAI* ai) : CDPairCalculatedValue(ai, "bg master", 60) {}

        CreatureData const* Calculate() override;
        CreatureData const* NearestBm(bool allowDead = true) override;
};

class FlagCarrierValue : public UnitCalculatedValue
{
    public:
        FlagCarrierValue(PlayerbotAI* ai, bool sameTeam = false, bool ignoreRange = false) :
            UnitCalculatedValue(ai), sameTeam(sameTeam), ignoreRange(ignoreRange) { }

        Unit* Calculate() override;

    private:
        bool sameTeam;
        bool ignoreRange;
};
