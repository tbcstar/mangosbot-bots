/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"
class RtiAction : public Action
{
    public:
        RtiAction(PlayerbotAI* botAI) : Action(botAI, "rti") { }

        bool Execute(Event event) override;

    private:
        void AppendRti(std::ostringstream& out, std::string const& type);
};

class MarkRtiAction : public Action
{
    public:
        MarkRtiAction(PlayerbotAI* botAI) : Action(botAI, "mark rti") { }

        bool Execute(Event event) override;
};
