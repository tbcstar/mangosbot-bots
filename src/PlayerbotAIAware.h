#pragma once

namespace ai
{
    class PlayerbotAIAware 
    {
    public:
        PlayerbotAIAware(PlayerbotAI* const ai) : ai(botAI) { }

    protected:
        PlayerbotAI* botAI;
    };
}
