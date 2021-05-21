#include "botpch.h"
#include "../../playerbot.h"
#include "TargetValue.h"

#include "../../ServerFacade.h"
#include "RtiTargetValue.h"
#include "Unit.h"

using namespace botAI;

Unit* TargetValue::FindTarget(FindTargetStrategy* strategy)
{
    GuidVector attackers = botAI->GetAiObjectContext()->GetValue<GuidVector >("attackers")->Get();
    for (GuidVector::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* unit = botAI->GetUnit(*i);
        if (!unit)
            continue;

        ThreatManager &threatManager = sServerFacade->GetThreatManager(unit);
        strategy->CheckAttacker(unit, &threatManager);
    }

    return strategy->GetResult();
}


bool FindNonCcTargetStrategy::IsCcTarget(Unit* attacker)
{
    Group* group = botAI->GetBot()->GetGroup();
    if (group)
    {
        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *member = ObjectAccessor::FindPlayer(itr->guid);
            if (!member || !sServerFacade->IsAlive(member))
                continue;

            PlayerbotAI* botAI = member->GetPlayerbotAI();
            if (botAI)
            {
                if (botAI->GetAiObjectContext()->GetValue<Unit*>("rti cc target")->Get() == attacker)
                    return true;

                string rti = botAI->GetAiObjectContext()->GetValue<string>("rti cc")->Get();
                int index = RtiTargetValue::GetRtiIndex(rti);
                if (index != -1)
                {
                    ObjectGuid guid = group->GetTargetIcon(index);
                    if (guid && attacker->GetGUID() == guid)
                        return true;
                }
            }
        }

        ObjectGuid guid = group->GetTargetIcon(4);
        if (guid && attacker->GetGUID() == guid)
            return true;
    }

    return false;
}

void FindTargetStrategy::GetPlayerCount(Unit* creature, int* tankCount, int* dpsCount)
{
    Player* bot = botAI->GetBot();
    if (tankCountCache.find(creature) != tankCountCache.end())
    {
        *tankCount = tankCountCache[creature];
        *dpsCount = dpsCountCache[creature];
        return;
    }

    *tankCount = 0;
    *dpsCount = 0;

    Unit::AttackerSet attackers(creature->getAttackers());
    for (set<Unit*>::const_iterator i = attackers.begin(); i != attackers.end(); i++)
    {
        Unit* attacker = *i;
        if (!attacker || !sServerFacade->IsAlive(attacker) || attacker == bot)
            continue;

        Player* player = dynamic_cast<Player*>(attacker);
        if (!player)
            continue;

        if (botAI->IsTank(player))
            (*tankCount)++;
        else
            (*dpsCount)++;
    }

    tankCountCache[creature] = *tankCount;
    dpsCountCache[creature] = *dpsCount;
}
