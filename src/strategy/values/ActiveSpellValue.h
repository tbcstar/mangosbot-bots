/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "../Value.h"

class PlayerbotAI;

class ActiveSpellValue : public CalculatedValue<uint32>
{
	public:
        ActiveSpellValue(PlayerbotAI* botAI) : CalculatedValue<uint32>(botAI) { }

        uint32 Calculate() override;
};
