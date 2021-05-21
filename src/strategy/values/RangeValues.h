#pragma once
#include "../Value.h"

namespace botAI
{
    class RangeValue : public ManualSetValue<float>, public Qualified
	{
	public:
        RangeValue(PlayerbotAI* botAI);

        virtual string Save();
        virtual bool Load(string value);
    };
}
