#pragma once
#include "Action.h"

namespace ai
{
    class Multiplier : public AiNamedObject
    {
    public:
        Multiplier(PlayerbotAI* botAI, string name) : AiNamedObject(ai, name) {}
        virtual ~Multiplier() {}

    public:
        virtual float GetValue(Action* action) { return 1.0f; }
    };

}
