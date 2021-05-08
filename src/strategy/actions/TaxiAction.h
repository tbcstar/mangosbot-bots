#pragma once

namespace ai
{
	class TaxiAction : public Action {
	public:
		TaxiAction(PlayerbotAI* botAI) : Action(ai, "taxi") {}

    public:
        virtual bool Execute(Event event);
    };

}