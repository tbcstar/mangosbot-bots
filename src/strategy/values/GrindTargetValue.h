/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "TargetValue.h"
class GrindTargetValue : public TargetValue
{
	public:
        GrindTargetValue(PlayerbotAI* botAI) : TargetValue(botAI) { }

        Unit* Calculate() override;

    private:
        uint32 GetTargetingPlayerCount(Unit* unit);
        Unit* FindTargetForGrinding(uint32 assistCount);
        bool needForQuest(Unit* target);
};
