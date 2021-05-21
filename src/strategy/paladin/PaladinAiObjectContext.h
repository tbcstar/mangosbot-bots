#pragma once

#include "../AiObjectContext.h"

namespace botAI
{
    class PaladinAiObjectContext : public AiObjectContext
    {
    public:
        PaladinAiObjectContext(PlayerbotAI* botAI);
    };
}