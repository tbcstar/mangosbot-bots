#pragma once
#include "../Value.h"

namespace botAI
{
    class SkipSpellsListValue : public ManualSetValue<set<uint32>&>
	{
	public:
        SkipSpellsListValue(PlayerbotAI* botAI) : ManualSetValue<set<uint32>&>(botAI, list) { }

        virtual string Save();
        virtual bool Load(string value);

    private:
        set<uint32> list;
    };
}
