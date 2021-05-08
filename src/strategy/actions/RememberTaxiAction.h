#pragma once

namespace ai
{
	class RememberTaxiAction : public Action {
	public:
		RememberTaxiAction(PlayerbotAI* botAI) : Action(ai, "remember taxi") {}

    public:
        virtual bool Execute(Event event);
    };

}