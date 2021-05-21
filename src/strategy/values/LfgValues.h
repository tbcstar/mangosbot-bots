#pragma once

#include "../Value.h"

namespace botAI
{
class LfgProposalValue : public ManualSetValue<uint32>
{
public:
    LfgProposalValue(PlayerbotAI* botAI) : ManualSetValue<uint32>(botAI, 0, "lfg proposal") { }
};
}
