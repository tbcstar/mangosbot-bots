#include "botpch.h"
#include "../../playerbot.h"
#include "GrindTargetValue.h"
#include "../../PlayerbotAIConfig.h"
#include "../../RandomPlayerbotMgr.h"
#include "../../ServerFacade.h"

using namespace botAI;

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


Unit* GrindTargetValue::FindTargetForGrinding(int assistCount)
{
    uint32 memberCount = 1;
    Group* group = bot->GetGroup();
    Player* master = GetMaster();

    GuidVector attackers = context->GetValue<GuidVector >("attackers")->Get();
    for (GuidVector::iterator i = attackers.begin(); i != attackers.end(); i++)
    {
        Unit* unit = botAI->GetUnit(*i);
        if (!unit || !sServerFacade->IsAlive(unit))
            continue;

        return unit;
    }

    GuidVector targets = *context->GetValue<GuidVector >("possible targets");

    if(targets.empty())
        return nullptr;

    float distance = 0;
    Unit* result = nullptr;
    for(GuidVector::iterator tIter = targets.begin(); tIter != targets.end(); tIter++)
    {
        Unit* unit = botAI->GetUnit(*tIter);
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

		Creature* creature = dynamic_cast<Creature*>(unit);
		if (creature && creature->GetCreatureInfo() && creature->GetCreatureInfo()->Rank > CREATURE_ELITE_NORMAL)
		    continue;

        if (group)
        {
            Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
            for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
            {
                Player *member = ObjectAccessor::FindPlayer(itr->guid);
                if (!member || !sServerFacade->IsAlive(member))
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


int GrindTargetValue::GetTargetingPlayerCount( Unit* unit )
{
    Group* group = bot->GetGroup();
    if (!group)
        return 0;

    int count = 0;
    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        Player *member = ObjectAccessor::FindPlayer(itr->guid);
        if (!member || !sServerFacade->IsAlive(member) || member == bot)
            continue;

        PlayerbotAI* botAI = member->GetPlayerbotAI();
        if ((botAI && *botAI->GetAiObjectContext()->GetValue<Unit*>("current target") == unit) ||
            (!botAI && member->GetTarget() == unit->GetGUID()))
            count++;
    }

    return count;
}

