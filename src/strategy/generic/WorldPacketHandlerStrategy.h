#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    class WorldPacketHandlerStrategy : public PassTroughStrategy
    {
    public:
        WorldPacketHandlerStrategy(PlayerbotAI* botAI);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "default"; }
    };

    class ReadyCheckStrategy : public PassTroughStrategy
    {
    public:
        ReadyCheckStrategy(PlayerbotAI* botAI) : PassTroughStrategy(botAI) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "ready check"; }
    };
}
