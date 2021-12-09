/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"

class Event;
class PlayerbotAI;

class TellSpellAction : public Action
{
    public:
        TellSpellAction(PlayerbotAI* botAI) : Action(botAI, "spell") { }

        bool Execute(Event event) override;
};

class TellCastFailedAction : public Action
{
    public:
        TellCastFailedAction(PlayerbotAI* botAI) : Action(botAI, "tell cast failed") { }

        bool Execute(Event event) override;
};