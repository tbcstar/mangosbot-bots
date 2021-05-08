#pragma once

#include "../Trigger.h"

namespace ai
{
class LfgProposalActiveTrigger : public Trigger
{
public:
    LfgProposalActiveTrigger(PlayerbotAI* botAI) : Trigger(ai, "lfg proposal active", 35) {}

    virtual bool IsActive()
    {
        return AI_VALUE(uint32, "lfg proposal");
    }
};
}
