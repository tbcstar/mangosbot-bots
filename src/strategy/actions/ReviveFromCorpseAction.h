#pragma once

namespace ai
{
	class ReviveFromCorpseAction : public Action {
	public:
		ReviveFromCorpseAction(PlayerbotAI* botAI) : Action(ai, "revive") {}

    public:
        virtual bool Execute(Event event);
    };

	class SpiritHealerAction : public Action {
	public:
	    SpiritHealerAction(PlayerbotAI* botAI) : Action(ai, "spirit healer") {}

    public:
        virtual bool Execute(Event event);
    };

}
