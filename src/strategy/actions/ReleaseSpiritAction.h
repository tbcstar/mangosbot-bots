/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"

class Event;
class PlayerbotAI;

class ReleaseSpiritAction : public Action
{
	public:
		ReleaseSpiritAction(PlayerbotAI* botAI, std::string const& name = "release") : Action(botAI, name) { }

        bool Execute(Event event) override;
};

class AutoReleaseSpiritAction : public ReleaseSpiritAction
{
    public:
        AutoReleaseSpiritAction(PlayerbotAI* ai, std::string const& name = "auto release") : ReleaseSpiritAction(ai, name) {}

        bool Execute(Event event) override;
        bool isUseful() override;
};

class RepopAction : public Action
{
    public:
        RepopAction(PlayerbotAI* ai, std::string const& name = "repop") : Action(ai, name) {}

        bool Execute(Event event) override;
        bool isUseful() override;
};
