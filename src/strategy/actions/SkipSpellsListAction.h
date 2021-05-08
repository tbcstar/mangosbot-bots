#pragma once

#include "../Action.h"
#include "../../LootObjectStack.h"

namespace ai
{
    class SkipSpellsListAction : public Action {
    public:
        SkipSpellsListAction(PlayerbotAI* botAI) : Action(ai, "ss") {}
        virtual bool Execute(Event event);

    private:
        SpellIds parseIds(string text);
    };

}
