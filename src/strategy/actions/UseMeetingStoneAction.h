#pragma once

#include "../Action.h"
#include "MovementActions.h"

namespace ai
{
    class SummonAction : public MovementAction
    {
    public:
        SummonAction(PlayerbotAI* botAI, string name = "summon") : MovementAction(ai, name) {}

        virtual bool Execute(Event event);

    protected:
        bool Teleport(Player *summoner, Player *player);
        bool SummonUsingGos(Player *summoner, Player *player);
        bool SummonUsingNpcs(Player *summoner, Player *player);
    };

    class UseMeetingStoneAction : public SummonAction
    {
    public:
        UseMeetingStoneAction(PlayerbotAI* botAI) : SummonAction(ai, "use meeting stone") {}

        virtual bool Execute(Event event);
    };
}
