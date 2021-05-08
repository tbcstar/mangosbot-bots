#pragma once
#include "../Value.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class NearestGameObjects : public ObjectGuidListCalculatedValue
	{
	public:
        NearestGameObjects(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) :
            ObjectGuidListCalculatedValue(botAI), range(range) {}

    protected:
        virtual list<ObjectGuid> Calculate();

    private:
        float range;
	};
}
