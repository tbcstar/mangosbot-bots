/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"
class TellTargetAction : public Action
{
    public:
        TellTargetAction(PlayerbotAI* botAI) : Action(botAI, "tell target") { }

        bool Execute(Event event) override;
};

class TellAttackersAction : public Action
{
    public:
        TellAttackersAction(PlayerbotAI* botAI) : Action(botAI, "tell attackers") { }

        bool Execute(Event event) override;
};
