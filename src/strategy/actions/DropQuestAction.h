/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"
class DropQuestAction : public Action
{
    public:
        DropQuestAction(PlayerbotAI* botAI) : Action(botAI, "drop quest") { }

        bool Execute(Event event) override;
};

class CleanQuestLogAction : public Action
{
    public:
        CleanQuestLogAction(PlayerbotAI* botAI) : Action(botAI, "clean quest log") {}

        bool Execute(Event event) override;
        void DropQuestType(uint8& numQuest, uint8 wantNum = 100, bool isGreen = false, bool hasProgress = false, bool isComplete = false);
        bool HasProgress(uint32 questId);
};
