/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NamedObjectContext.h"
#include "Value.h"

class PlayerbotAI;

class RangeValue : public ManualSetValue<float>, public Qualified
{
	public:
        RangeValue(PlayerbotAI* botAI);

        std::string const& Save() override;
        bool Load(std::string const& value) override;
};
