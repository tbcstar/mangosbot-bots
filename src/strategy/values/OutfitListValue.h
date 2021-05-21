#pragma once
#include "../Value.h"

namespace botAI
{
    typedef list<string> Outfit;
    class OutfitListValue : public ManualSetValue<Outfit&>
	{
	public:
        OutfitListValue(PlayerbotAI* botAI) : ManualSetValue<Outfit&>(botAI, list) { }

        virtual string Save();
        virtual bool Load(string value);

    private:
        Outfit list;
    };
}
