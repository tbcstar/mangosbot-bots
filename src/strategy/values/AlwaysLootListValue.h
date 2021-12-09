/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Value.h"

class PlayerbotAI;

class AlwaysLootListValue : public ManualSetValue<std::set<uint32>&>
{
	public:
        AlwaysLootListValue(PlayerbotAI* botAI) : ManualSetValue<std::set<uint32>&>(botAI, list) { }

        std::string const& Save() override;
        bool Load(std::string const& value) override;

    private:
        std::set<uint32> list;
};