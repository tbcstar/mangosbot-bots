/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ThreatValues.h"
#include "ThreatManager.h"

uint8 ThreatValue::Calculate()
{
    if (qualifier == "aoe")
    {
        uint8 maxThreat = 0;
        GuidVector attackers = context->GetValue<GuidVector >("attackers")->Get();
        for (ObjectGuid const guid : attackers)
        {
            Unit* unit = botAI->GetUnit(guid);
            if (!unit || !unit->IsAlive())
                continue;

            uint8 threat = Calculate(unit);
            if (!maxThreat || threat > maxThreat)
                maxThreat = threat;
        }

        return maxThreat;
    }

    Unit* target = AI_VALUE(Unit*, qualifier);
    return Calculate(target);
}

uint8 ThreatValue::Calculate(Unit* target)
{
    if (!target)
        return 0;

    if (target->GetGUID().IsPlayer())
        return 0;

    Group* group = bot->GetGroup();
    if (!group)
        return 0;

    float botThreat = target->getThreatManager().getThreat(bot);
    float maxThreat = -1.0f;

    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        Player *player = ObjectAccessor::FindPlayer(itr->guid);
        if (!player || !player->IsAlive() || player == bot)
            continue;

        if (botAI->IsTank(player))
        {
            float threat = target->getThreatManager().getThreat(player);
            if (maxThreat < threat)
                maxThreat = threat;
        }
    }

    if (maxThreat <= 0)
        return 0;

    return botThreat * 100 / maxThreat;
}
