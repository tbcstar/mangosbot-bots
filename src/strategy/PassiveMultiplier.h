#pragma once
#include "Action.h"
#include "Multiplier.h"

namespace ai
{
    class PassiveMultiplier : public Multiplier
    {
    public:
        PassiveMultiplier(PlayerbotAI* botAI);

    public:
        virtual float GetValue(Action* action);

    private:
        static list<string> allowedActions;
        static list<string> allowedParts;
    };

}
