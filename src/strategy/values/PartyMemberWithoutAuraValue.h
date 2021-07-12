/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PartyMemberValue.h"
#include "NamedObjectContext.h"
class PartyMemberWithoutAuraValue : public PartyMemberValue, public Qualified
{
	public:
        PartyMemberWithoutAuraValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) : PartyMemberValue(botAI) { }

    protected:
        Unit* Calculate() override;
};
