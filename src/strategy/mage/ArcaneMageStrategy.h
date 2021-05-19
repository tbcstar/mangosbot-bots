#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class ArcaneMageStrategy : public GenericMageStrategy
    {
    public:
        ArcaneMageStrategy();

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "arcane"; }
        virtual NextAction** getDefaultActions();
    };

}
