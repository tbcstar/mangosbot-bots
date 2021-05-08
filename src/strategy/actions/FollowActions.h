#pragma once

#include "../Action.h"
#include "MovementActions.h"

namespace ai
{
	class FollowAction : public MovementAction {
	public:
		FollowAction(PlayerbotAI* botAI) : MovementAction(ai, "follow") {}
		virtual bool Execute(Event event);
        virtual bool isUseful();
	};
}
