/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "UseItemAction.h"

class Event;
class PlayerbotAI;

class CheckMountStateAction : public UseItemAction
{
    public:
        CheckMountStateAction(PlayerbotAI* botAI) : UseItemAction(botAI, "check mount state") { }

        bool Execute(Event event) override;
        bool isUseful() override;
        bool isPossible() const override { return true; }
        bool Mount();
};