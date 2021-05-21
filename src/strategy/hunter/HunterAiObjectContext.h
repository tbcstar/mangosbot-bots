#pragma once

#include "../AiObjectContext.h"

namespace botAI
{
    class HunterAiObjectContext : public AiObjectContext
    {
    public:
        HunterAiObjectContext(PlayerbotAI* botAI);
    };
}