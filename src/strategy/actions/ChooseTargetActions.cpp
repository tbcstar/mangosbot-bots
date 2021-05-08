#pragma once

#include "../Action.h"
#include "ChooseTargetActions.h"

#include "../../ServerFacade.h"
#include "MovementGenerator.h"
#include "CreatureAI.h"

bool DropTargetAction::Execute(Event event)
{
    Unit* target = context->GetValue<Unit*>("current target")->Get();
    ObjectGuid pullTarget = context->GetValue<ObjectGuid>("pull target")->Get();
    list<ObjectGuid> possible = botAI->GetAiObjectContext()->GetValue<list<ObjectGuid> >("possible targets")->Get();
    if (pullTarget && find(possible.begin(), possible.end(), pullTarget) == possible.end())
    {
        context->GetValue<ObjectGuid>("pull target")->Set(ObjectGuid::Empty);
    }
    context->GetValue<Unit*>("current target")->Set(NULL);
    bot->SetTarget(ObjectGuid::Empty);
    botAI->ChangeEngine(BOT_STATE_NON_COMBAT);
    botAI->InterruptSpell();
    bot->AttackStop();
    Pet* pet = bot->GetPet();
    if (pet)
    {
        CreatureAI* creatureAI = ((Creature*)pet)->AI();
        if (creatureAI)
        {
            pet->GetCharmInfo()->SetReactState(REACT_PASSIVE);
            pet->GetCharmInfo()->SetCommandState(COMMAND_FOLLOW);
            pet->AttackStop();
        }
    }
    if (!urand(0, 25))
    {
        vector<uint32> sounds;
        if (target && sServerFacade->UnitIsDead(target))
        {
            sounds.push_back(TEXTEMOTE_CHEER);
            sounds.push_back(TEXTEMOTE_CONGRATULATE);
        }
        else
        {
            sounds.push_back(304); // guard
            sounds.push_back(325); // stay
        }
        if (!sounds.empty()) botAI->PlaySound(sounds[urand(0, sounds.size() - 1)]);
    }
    return true;
}


bool AttackAnythingAction::Execute(Event event)
{
    bool result = AttackAction::Execute(event);
    if (result && GetTarget()) context->GetValue<ObjectGuid>("pull target")->Set(GetTarget()->GetGUID());
    return result;
}
