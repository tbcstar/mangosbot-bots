/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ChooseTargetActions.h"
#include "../Event.h"
#include "../values/PossibleRpgTargetsValue.h"
#include "../../Playerbot.h"

bool DropTargetAction::Execute(Event event)
{
    Unit* target = context->GetValue<Unit*>("current target")->Get();
    ObjectGuid pullTarget = context->GetValue<ObjectGuid>("pull target")->Get();
    GuidVector possible = botAI->GetAiObjectContext()->GetValue<GuidVector>("possible targets")->Get();

    if (pullTarget && find(possible.begin(), possible.end(), pullTarget) == possible.end())
    {
        context->GetValue<ObjectGuid>("pull target")->Set(ObjectGuid::Empty);
    }

    context->GetValue<Unit*>("current target")->Set(nullptr);

    bot->SetTarget(ObjectGuid::Empty);
    botAI->ChangeEngine(BOT_STATE_NON_COMBAT);
    botAI->InterruptSpell();
    bot->AttackStop();

    if (Pet* pet = bot->GetPet())
    {
        if (CreatureAI* creatureAI = ((Creature*)pet)->AI())
        {
            pet->SetReactState(REACT_PASSIVE);
            pet->GetCharmInfo()->SetCommandState(COMMAND_FOLLOW);
            pet->AttackStop();
        }
    }

    if (!urand(0, 25))
    {
        std::vector<uint32> sounds;
        if (target && target->isDead())
        {
            sounds.push_back(TEXT_EMOTE_CHEER);
            sounds.push_back(TEXT_EMOTE_CONGRATULATE);
        }
        else
        {
            sounds.push_back(304); // guard
            sounds.push_back(325); // stay
        }

        if (!sounds.empty())
            botAI->PlaySound(sounds[urand(0, sounds.size() - 1)]);
    }

    return true;
}

bool AttackAnythingAction::Execute(Event event)
{
    bool result = AttackAction::Execute(event);
    if (result && GetTarget())
        context->GetValue<ObjectGuid>("pull target")->Set(GetTarget()->GetGUID());

    return result;
}

bool AttackAnythingAction::isUseful()
{
    return GetTarget() && (!AI_VALUE(GuidVector, "nearest non bot players").empty() && AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig->mediumHealth &&
        (!AI_VALUE2(uint8, "mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig->mediumMana)) || AI_VALUE2(bool, "combat", "self target");
}

bool AttackAnythingAction::isPossible()
{
    return AttackAction::isPossible() && GetTarget();
}
