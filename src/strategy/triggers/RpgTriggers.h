#pragma once
#include "../Trigger.h"

namespace ai
{
    class NoRpgTargetTrigger : public Trigger
    {
    public:
        NoRpgTargetTrigger(PlayerbotAI* botAI) : Trigger(ai, "no rpg target") {}

        virtual bool IsActive();
    };

    class FarFromRpgTargetTrigger : public Trigger
    {
    public:
        FarFromRpgTargetTrigger(PlayerbotAI* botAI) : Trigger(ai, "far from rpg target") {}

        virtual bool IsActive();
    };
}
