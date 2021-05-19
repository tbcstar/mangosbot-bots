/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "../Action.h"

class Event;
class PlayerbotAI;

enum QuestListFilter
{
    QUEST_LIST_FILTER_SUMMARY       = 0,
    QUEST_LIST_FILTER_COMPLETED     = 1,
    QUEST_LIST_FILTER_INCOMPLETED   = 2,
    QUEST_LIST_FILTER_ALL           = QUEST_LIST_FILTER_COMPLETED | QUEST_LIST_FILTER_INCOMPLETED
};

class ListQuestsAction : public Action
{
    public:
        ListQuestsAction(PlayerbotAI* botAI) : Action(botAI, "quests") { }

        bool Execute(Event event) override;

    private:
        uint32 ListQuests(bool completed, bool silent);
        void ListQuests(QuestListFilter filter);

};
