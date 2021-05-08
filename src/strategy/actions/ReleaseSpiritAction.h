#pragma once

#include "../../ServerFacade.h"
#include "../Action.h"
#include "MovementActions.h"
#include "../values/LastMovementValue.h"

namespace ai
{
	class ReleaseSpiritAction : public Action {
	public:
		ReleaseSpiritAction(PlayerbotAI* botAI) : Action(ai, "release") {}

    public:
        virtual bool Execute(Event event)
        {
            if (sServerFacade->IsAlive(bot) || bot->GetCorpse())
            {
                botAI->TellError("I am not dead");
                return false;
            }

            botAI->ChangeStrategy("-follow,+stay", BOT_STATE_NON_COMBAT);

            bot->SetBotDeathTimer();
            bot->BuildPlayerRepop();

            bot->RepopAtGraveyard();
            botAI->TellMaster("Meet me at the graveyard");
            return true;
        }
    };

}
