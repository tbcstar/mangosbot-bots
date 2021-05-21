#pragma once
#include "../Value.h"
#include "../../PlayerbotAIConfig.h"

namespace botAI
{
    class NearestGameObjects : public ObjectGuidListCalculatedValue
	{
	public:
        NearestGameObjects(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) :
            ObjectGuidListCalculatedValue(botAI), range(range) { }

    protected:
        virtual GuidVector Calculate();

    private:
        float range;
	};
}
