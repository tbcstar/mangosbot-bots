/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AttackersValue.h"
#include "GridNotifiers.h"
#include "Playerbot.h"
#include "ServerFacade.h"

GuidVector AttackersValue::Calculate()
{
    std::set<Unit*> targets;
    AddAttackersOf(bot, targets);

    GuidVector result;
    if (!botAI->AllowActive(ALL_ACTIVITY))
        return std::move(result);

    if (Group* group = bot->GetGroup())
        AddAttackersOf(group, targets);

    RemoveNonThreating(targets);

	for (Unit* unit : targets)
		result.push_back(unit->GetGUID());

    if (bot->duel && bot->duel->opponent)
        result.push_back(bot->duel->opponent->GetGUID());

	return std::move(result);
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
	Acore::AnyUnfriendlyUnitInObjectRangeCheck u_check(player, player, sPlayerbotAIConfig->sightDistance);
    Acore::UnitListSearcher<Acore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(player, units, u_check);
    player->VisitNearbyObject(sPlayerbotAIConfig->sightDistance, searcher);

	for (Unit* unit : units)
    {
        if (!player->GetGroup())
        {
            if (!unit->getThreatManager().getThreat(player))
                continue;
        }

        targets.insert(unit);
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
    bool rti = false;
    if (attacker && bot->GetGroup())
        rti = bot->GetGroup()->GetTargetIcon(7) == attacker->GetGUID();

    PlayerbotAI* botAI = bot->GetPlayerbotAI();

    bool leaderHasThreat = false;
    if (attacker && bot->GetGroup() && botAI->GetMaster())
        leaderHasThreat = attacker->getThreatManager().getThreat(botAI->GetMaster());

    bool isMemberBotGroup = false;
    if (bot->GetGroup() && botAI->GetMaster() && botAI->GetMaster()->GetPlayerbotAI() && !botAI->GetMaster()->GetPlayerbotAI()->IsRealPlayer())
        isMemberBotGroup = true;

    return attacker && attacker->IsInWorld() && attacker->GetMapId() == bot->GetMapId() && !attacker->isDead() && !attacker->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) &&
        !attacker->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE) && !attacker->isInvisibleForAlive() && !attacker->HasStealthAura() && !attacker->HasInvisibilityAura() &&
        /*!attacker->hasUnitState(UNIT_STAT_STUNNED) &&*/!((attacker->IsPolymorphed() || botAI->HasAura("sap", attacker) || attacker->IsCharmed() || attacker->isFeared()) && !rti) &&
        /*!sServerFacade->IsInRoots(attacker) &&*/!attacker->IsFriendlyTo(bot) && bot->IsWithinDistInMap(attacker, sPlayerbotAIConfig->sightDistance) &&
        !(attacker->GetCreatureType() == CREATURE_TYPE_CRITTER) && !(sPlayerbotAIConfig->IsInPvpProhibitedZone(attacker->GetAreaId()) && (attacker->GetGUID().IsPlayer() ||
        attacker->GetGUID().IsPet())) && (!c || (!c->IsInEvadeMode() && ((!isMemberBotGroup && botAI->HasStrategy("attack tagged", BOT_STATE_NON_COMBAT)) ||
        leaderHasThreat || !c->hasLootRecipient() || c->isTappedBy(bot))));
}

bool AttackersValue::IsValidTarget(Unit *attacker, Player *bot)
{
    return  IsPossibleTarget(attacker, bot) && (attacker->getThreatManager().getCurrentVictim() || attacker->GetGuidValue(UNIT_FIELD_TARGET) ||
        attacker->GetGUID().IsPlayer() || attacker->GetGUID() == bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<ObjectGuid>("pull target")->Get());
}
bool PossibleAddsValue::Calculate()
{
    GuidVector possible = botAI->GetAiObjectContext()->GetValue<GuidVector >("possible targets no los")->Get();
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