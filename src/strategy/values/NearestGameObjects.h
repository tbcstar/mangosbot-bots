/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Value.h"
#include "PlayerbotAIConfig.h"

class PlayerbotAI;

class NearestGameObjects : public ObjectGuidListCalculatedValue
{
	public:
        NearestGameObjects(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) : ObjectGuidListCalculatedValue(botAI), range(range) { }

    protected:
        GuidVector Calculate() override;

    private:
        float range;
};
