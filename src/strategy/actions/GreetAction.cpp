#include "botpch.h"
#include "../../playerbot.h"
#include "GreetAction.h"

#include "../../PlayerbotAIConfig.h"
#include "../../ServerFacade.h"
using namespace ai;

GreetAction::GreetAction(PlayerbotAI* botAI) : Action(ai, "greet")
{
}

bool GreetAction::Execute(Event event)
{
    ObjectGuid guid = AI_VALUE(ObjectGuid, "new player nearby");
    if (!guid || !guid.IsPlayer()) return false;

    Player* player = dynamic_cast<Player*>(botAI->GetUnit(guid));
    if (!player) return false;

    if (!sServerFacade->IsInFront(bot, player, sPlayerbotAIConfig->sightDistance, CAST_ANGLE_IN_FRONT))
        sServerFacade->SetFacingTo(bot, player);

    ObjectGuid oldSel = bot->GetTarget();
    bot->SetTarget(guid);
    bot->HandleEmote(EMOTE_ONESHOT_WAVE);
    botAI->PlaySound(TEXTEMOTE_HELLO);
    bot->SetTarget(oldSel);

    set<ObjectGuid>& alreadySeenPlayers = botAI->GetAiObjectContext()->GetValue<set<ObjectGuid>& >("already seen players")->Get();
    alreadySeenPlayers.insert(guid);

    list<ObjectGuid> nearestPlayers = botAI->GetAiObjectContext()->GetValue<list<ObjectGuid> >("nearest friendly players")->Get();
    for (list<ObjectGuid>::iterator i = nearestPlayers.begin(); i != nearestPlayers.end(); ++i) {
        alreadySeenPlayers.insert(*i);
    }
    return true;
}
