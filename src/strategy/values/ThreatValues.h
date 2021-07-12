/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NamedObjectContext.h"
#include "Value.h"
class ThreatValue : public Uint8CalculatedValue, public Qualified
{
	public:
        ThreatValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

    	uint8 Calculate() override;

    protected:
    	uint8 Calculate(Unit* target);
};
