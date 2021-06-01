/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AttackersValue.h"
#include "Playerbot.h"
#include "ServerFacade.h"

GuidVector AttackersValue::Calculate()
{
    std::set<Unit*> targets;
    AddAttackersOf(bot, targets);

    if (Group* group = bot->GetGroup())
        AddAttackersOf(group, targets);

    RemoveNonThreating(targets);

    GuidVector result;
	for (Unit* unit : targets)
		result.push_back(unit->GetGUID());

    if (bot->duel && bot->duel->opponent)
        result.push_back(bot->duel->opponent->GetGUID());

	return result;
}

void AttackersValue::AddAttackersOf(Group* group, std::set<Unit*>& targets)
{
    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        Player *member = ObjectAccessor::FindPlayer(itr->guid);
        if (!member || !member->IsAlive() || member == bot)
            continue;

        AddAttackersOf(member, targets);
    }
}

struct AddGuardiansHelper
{
    explicit AddGuardiansHelper(std::vector<Unit*> &units) : units(units) { }

    void operator()(Unit* target) const
    {
        units.push_back(target);
    }

    std::vector<Unit*> &units;
};

void AttackersValue::AddAttackersOf(Player* player, std::set<Unit*>& targets)
{
    if (player->IsBeingTeleported())
        return;

	std::list<Unit*> units;
	acore::AnyUnfriendlyUnitInObjectRangeCheck u_check(player, player, sPlayerbotAIConfig->sightDistance);
    acore::UnitListSearcher<acore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(player, units, u_check);
    player->VisitNearbyObject(sPlayerbotAIConfig->sightDistance, searcher);

	for (Unit* unit : units)
	{
		targets.insert(unit);
		unit->CallForAllControlledUnits(AddGuardiansHelper(units), CONTROLLED_PET | CONTROLLED_GUARDIANS | CONTROLLED_CHARM | CONTROLLED_MINIPET | CONTROLLED_TOTEMS);
	}
}

void AttackersValue::RemoveNonThreating(std::set<Unit*>& targets)
{
    for (std::set<Unit*>::iterator tIter = targets.begin(); tIter != targets.end();)
    {
        Unit* unit = *tIter;
        if (!IsValidTarget(unit, bot))
        {
            std::set<Unit*>::iterator tIter2 = tIter;
            ++tIter;
            targets.erase(tIter2);
        }
        else
            ++tIter;
    }
}

bool AttackersValue::IsPossibleTarget(Unit *attacker, Player *bot)
{
    Creature* c = attacker->ToCreature();
    return attacker && attacker->IsInWorld() && attacker->GetMapId() == bot->GetMapId() && !attacker->isDead() && !attacker->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) &&
        !attacker->HasStealthAura() && !attacker->HasInvisibilityAura() && !attacker->IsPolymorphed() && !attacker->HasUnitState(UNIT_STATE_STUNNED) && !attacker->IsCharmed() &&
        !attacker->isFeared() && !attacker->isInRoots() && !attacker->IsFriendlyTo(bot) && bot->IsWithinDistInMap(attacker, sPlayerbotAIConfig->sightDistance) &&
        !(attacker->getLevel() == 1 && !attacker->IsHostileTo(bot)) && !sPlayerbotAIConfig->IsInPvpProhibitedZone(attacker->GetAreaId()) &&
        (!c || (!c->IsInEvadeMode() && (!attacker->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_TAPPED) || c->isTappedBy(bot))));
}

bool AttackersValue::IsValidTarget(Unit *attacker, Player *bot)
{
    return IsPossibleTarget(attacker, bot) && (attacker->getThreatManager().getCurrentVictim() || attacker->GetTarget() || attacker->GetGUID().IsPlayer() ||
        attacker->GetGUID() == bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<ObjectGuid>("pull target")->Get());
}

bool PossibleAdsValue::Calculate()
{
    GuidVector possible = botAI->GetAiObjectContext()->GetValue<GuidVector >("possible targets")->Get();
    GuidVector attackers = botAI->GetAiObjectContext()->GetValue<GuidVector >("attackers")->Get();

    for (ObjectGuid const guid : possible)
    {
        if (find(attackers.begin(), attackers.end(), guid) != attackers.end())
            continue;

        if (Unit* add = botAI->GetUnit(guid))
        {
            if (!add->GetTarget() && !add->getThreatManager().getCurrentVictim() && add->IsHostileTo(bot))
            {
                for (ObjectGuid const attackerGUID : attackers)
                {
                    Unit* attacker = botAI->GetUnit(attackerGUID);
                    if (!attacker)
                        continue;

                    float dist = sServerFacade->GetDistance2d(attacker, add);
                    if (sServerFacade->IsDistanceLessOrEqualThan(dist, sPlayerbotAIConfig->aoeRadius * 1.5f))
                        continue;

                    if (sServerFacade->IsDistanceLessOrEqualThan(dist, sPlayerbotAIConfig->aggroDistance))
                        return true;
                }
            }
        }
    }

    return false;
}
