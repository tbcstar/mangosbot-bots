#pragma once
#include "../Value.h"

namespace ai
{
    class CollisionValue : public BoolCalculatedValue, public Qualified
	{
	public:
        CollisionValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI), Qualified() {}

        virtual bool Calculate();
    };
}
