/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"

class Event;
class PlayerbotAI;

class ReviveFromCorpseAction : public Action
{
	public:
		ReviveFromCorpseAction(PlayerbotAI* botAI) : Action(botAI, "revive") { }

        bool Execute(Event event) override;
};

class SpiritHealerAction : public Action
{
	public:
	    SpiritHealerAction(PlayerbotAI* botAI) : Action(botAI, "spirit healer") { }

        bool Execute(Event event) override;
};
