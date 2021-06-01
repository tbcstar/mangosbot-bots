/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PlayerbotAIBase.h"
#include "Playerbot.h"

PlayerbotAIBase::PlayerbotAIBase() : nextAICheckDelay(0)
{
}

void PlayerbotAIBase::UpdateAI(uint32 elapsed)
{
    if (nextAICheckDelay > elapsed)
        nextAICheckDelay -= elapsed;
    else
        nextAICheckDelay = 0;

    if (!CanUpdateAI())
        return;

    UpdateAIInternal(elapsed);
    YieldThread();
}

void PlayerbotAIBase::SetNextCheckDelay(uint32 const delay)
{
    if (nextAICheckDelay < delay)
        sLog->outDebug("Setting lesser delay %d -> %d", nextAICheckDelay, delay);

    nextAICheckDelay = delay;

    if (nextAICheckDelay > sPlayerbotAIConfig->globalCoolDown)
        sLog->outDebug( "std::set next check delay: %d", nextAICheckDelay);
}

void PlayerbotAIBase::IncreaseNextCheckDelay(uint32 delay)
{
    nextAICheckDelay += delay;

    if (nextAICheckDelay > sPlayerbotAIConfig->globalCoolDown)
        sLog->outDebug( "increase next check delay: %d", nextAICheckDelay);
}

bool PlayerbotAIBase::CanUpdateAI()
{
    return nextAICheckDelay < 100;
}

void PlayerbotAIBase::YieldThread()
{
    if (nextAICheckDelay < sPlayerbotAIConfig->reactDelay)
        nextAICheckDelay = sPlayerbotAIConfig->reactDelay;
}

bool PlayerbotAIBase::IsActive()
{
    return nextAICheckDelay < sPlayerbotAIConfig->maxWaitForMove;
}
