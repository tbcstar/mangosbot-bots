#pragma once
#include "../Value.h"

namespace botAI
{
    class RtiValue : public ManualSetValue<string>
	{
	public:
        RtiValue(PlayerbotAI* botAI);

        virtual string Save() { return value; }
        virtual bool Load(string text) { value = text; return true; }
	};

    class RtiCcValue : public ManualSetValue<string>
	{
	public:
        RtiCcValue(PlayerbotAI* botAI);

        virtual string Save() { return value; }
        virtual bool Load(string text) { value = text; return true; }
	};
}
