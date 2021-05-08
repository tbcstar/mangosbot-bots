#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    class QuestStrategy : public PassTroughStrategy
    {
    public:
        QuestStrategy(PlayerbotAI* botAI);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class DefaultQuestStrategy : public QuestStrategy
    {
    public:
        DefaultQuestStrategy(PlayerbotAI* botAI);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "quest"; }
    };

    class AcceptAllQuestsStrategy : public QuestStrategy
    {
    public:
        AcceptAllQuestsStrategy(PlayerbotAI* botAI);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "accept all quests"; }
    };
}
