#pragma once

#include "../Action.h"
#include "QuestDef.h"

namespace ai
{
    class QuestAction : public Action 
    {
    public:
        QuestAction(PlayerbotAI* botAI, string name) : Action(ai, name) {}

    public:
        virtual bool Execute(Event event);

    protected:
        virtual void ProcessQuest(Quest const* quest, WorldObject* questGiver) = 0;

    protected:
        bool AcceptQuest(Quest const* quest, ObjectGuid questGiver);
        bool ProcessQuests(ObjectGuid questGiver);
        bool ProcessQuests(WorldObject* questGiver);
    };
    
    class QuestObjectiveCompletedAction : public Action 
    {
    public:
        QuestObjectiveCompletedAction(PlayerbotAI* botAI) : Action(ai, "quest objective completed") {}

    public:
        virtual bool Execute(Event event);
    };
}
