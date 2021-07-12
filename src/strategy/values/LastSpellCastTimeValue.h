/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NamedObjectContext.h"
#include "Value.h"
class LastSpellCastTimeValue : public ManualSetValue<time_t>, public Qualified
{
	public:
        LastSpellCastTimeValue(PlayerbotAI* botAI) : ManualSetValue<time_t>(botAI, 0), Qualified() { }
};
