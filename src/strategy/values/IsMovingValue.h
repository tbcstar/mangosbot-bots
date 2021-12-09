/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NamedObjectContext.h"
#include "Value.h"

class PlayerbotAI;

class IsMovingValue : public BoolCalculatedValue, public Qualified
{
	public:
        IsMovingValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

        bool Calculate() override;
};

class IsSwimmingValue : public BoolCalculatedValue, public Qualified
{
	public:
        IsSwimmingValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

        bool Calculate() override;
};