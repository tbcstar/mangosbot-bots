/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Value.h"
class LfgProposalValue : public ManualSetValue<uint32>
{
    public:
        LfgProposalValue(PlayerbotAI* botAI) : ManualSetValue<uint32>(botAI, 0, "lfg proposal") { }
};
