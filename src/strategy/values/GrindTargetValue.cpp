/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GrindTargetValue.h"
#include "Playerbot.h"

Unit* GrindTargetValue::Calculate()
{
    uint32 memberCount = 1;
    Group* group = bot->GetGroup();
    if (group)
        memberCount = group->GetMembersCount();

    Unit* target = nullptr;
    uint32 assistCount = 0;
    while (!target && assistCount < memberCount)
    {
        target = FindTargetForGrinding(assistCount++);
    }

    return target;
}

Unit* GrindTargetValue::FindTargetForGrinding(uint32 assistCount)
{
    uint32 memberCount = 1;
    Group* group = bot->GetGroup();
    Player* master = GetMaster();

    GuidVector attackers = context->GetValue<GuidVector>("attackers")->Get();
    for (ObjectGuid const guid : attackers)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive())
            continue;

        return unit;
    }

    GuidVector targets = *context->GetValue<GuidVector>("possible targets");
    if (targets.empty())
        return nullptr;

    float distance = 0;
    Unit* result = nullptr;
    for (ObjectGuid const guid : targets)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit)
            continue;

        if (abs(bot->GetPositionZ() - unit->GetPositionZ()) > sPlayerbotAIConfig->spellDistance)
            continue;

        if (GetTargetingPlayerCount(unit) > assistCount)
            continue;

		if (master && master->GetDistance(unit) >= sPlayerbotAIConfig->grindDistance && !sRandomPlayerbotMgr->IsRandomBot(bot))
            continue;

		if ((int)unit->getLevel() - (int)bot->getLevel() > 4 && !unit->GetGUID().IsPlayer())
		    continue;

		if (Creature* creature = unit->ToCreature())
            if (CreatureTemplate const* creatureInfo = creature->GetCreatureTemplate())
		        if (creatureInfo->rank > CREATURE_ELITE_NORMAL)
		            continue;

        if (group)
        {
            Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
            for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
            {
                Player *member = ObjectAccessor::FindPlayer(itr->guid);
                if (!member || !member->IsAlive())
                    continue;

                float d = member->GetDistance(unit);
                if (!result || d < distance)
                {
                    distance = d;
                    result = unit;
                }
            }
        }
        else
        {
            float d = bot->GetDistance(unit);
            if (!result || d < distance)
            {
                distance = d;
                result = unit;
            }
        }
    }

    return result;
}

uint32 GrindTargetValue::GetTargetingPlayerCount(Unit* unit)
{
    Group* group = bot->GetGroup();
    if (!group)
        return 0;

    uint32 count = 0;
    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        Player *member = ObjectAccessor::FindPlayer(itr->guid);
        if (!member || !member->IsAlive() || member == bot)
            continue;

        PlayerbotAI* botAI = member->GetPlayerbotAI();
        if ((botAI && *botAI->GetAiObjectContext()->GetValue<Unit*>("current target") == unit) ||
            (!botAI && member->GetTarget() == unit->GetGUID()))
            count++;
    }

    return count;
}
