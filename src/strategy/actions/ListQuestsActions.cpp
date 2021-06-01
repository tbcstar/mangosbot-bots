/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ListQuestsActions.h"
#include "Event.h"
#include "Playerbot.h"

bool ListQuestsAction::Execute(Event event)
{
    if (event.getParam() == "completed" || event.getParam() == "co")
    {
        ListQuests(QUEST_LIST_FILTER_COMPLETED);
    }
    else if (event.getParam() == "incompleted" || event.getParam() == "in")
    {
        ListQuests(QUEST_LIST_FILTER_INCOMPLETED);
    }
    else if (event.getParam() == "all")
    {
        ListQuests(QUEST_LIST_FILTER_ALL);
    }
    else
    {
        ListQuests(QUEST_LIST_FILTER_SUMMARY);
    }

    return true;
}

void ListQuestsAction::ListQuests(QuestListFilter filter)
{
    bool showIncompleted = filter & QUEST_LIST_FILTER_INCOMPLETED;
    bool showCompleted = filter & QUEST_LIST_FILTER_COMPLETED;

    if (showIncompleted)
        botAI->TellMaster("--- Incompleted quests ---");

    uint32 incompleteCount = ListQuests(false, !showIncompleted);

    if (showCompleted)
        botAI->TellMaster("--- Completed quests ---");

    uint32 completeCount = ListQuests(true, !showCompleted);

    botAI->TellMaster("--- Summary ---");

    std::ostringstream out;
    out << "Total: " << (completeCount + incompleteCount) << " / 25 (incompleted: " << incompleteCount << ", completed: " << completeCount << ")";
    botAI->TellMaster(out);
}

uint32 ListQuestsAction::ListQuests(bool completed, bool silent)
{
    uint32 count = 0;
    for (uint16 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        uint32 questId = bot->GetQuestSlotQuestId(slot);
        if (!questId)
            continue;

        Quest const* pQuest = sObjectMgr->GetQuestTemplate(questId);
        bool isCompletedQuest = bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE;
        if (completed != isCompletedQuest)
            continue;

        count++;

        if (silent)
            continue;

        botAI->TellMaster(chat->formatQuest(pQuest));
    }

    return count;
}
