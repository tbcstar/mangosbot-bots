/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "MovementActions.h"
class ReachAreaTriggerAction : public MovementAction
{
    public:
        ReachAreaTriggerAction(PlayerbotAI* botAI) : MovementAction(botAI, "reach area trigger") { }

        bool Execute(Event event) override;
};

class AreaTriggerAction : public MovementAction
{
    public:
        AreaTriggerAction(PlayerbotAI* botAI) : MovementAction(botAI, "area trigger") { }

        bool Execute(Event event) override;
};
