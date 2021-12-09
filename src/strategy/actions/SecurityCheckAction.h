/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"

class Event;
class PlayerbotAI;

class SecurityCheckAction : public Action
{
    public:
        SecurityCheckAction(PlayerbotAI* botAI) : Action(botAI, "security check") { }

        bool isUseful() override;
        bool Execute(Event event) override;
};