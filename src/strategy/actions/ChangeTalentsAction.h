#pragma once

#include "../Action.h"

namespace ai
{
	class ChangeTalentsAction : public Action {
	public:
		ChangeTalentsAction(PlayerbotAI* botAI) : Action(ai, "talents") {}

    public:
        virtual bool Execute(Event event);

    };

}