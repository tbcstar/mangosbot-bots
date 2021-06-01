/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericTriggers.h"
#include "Playerbot.h"

bool LowManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig->lowMana;
}

bool MediumManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig->mediumMana;
}

bool NoPetTrigger::IsActive()
{
    return !AI_VALUE(Unit*, "pet target") && !AI_VALUE2(bool, "mounted", "self target");
}

bool RageAvailable::IsActive()
{
    return AI_VALUE2(uint8, "rage", "self target") >= amount;
}

bool EnergyAvailable::IsActive()
{
	return AI_VALUE2(uint8, "energy", "self target") >= amount;
}

bool ComboPointsAvailableTrigger::IsActive()
{
    return AI_VALUE2(uint8, "combo", "current target") >= amount;
}

bool LoseAggroTrigger::IsActive()
{
    return !AI_VALUE2(bool, "has aggro", "current target");
}

bool HasAggroTrigger::IsActive()
{
    return AI_VALUE2(bool, "has aggro", "current target");
}

bool PanicTrigger::IsActive()
{
    return AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig->criticalHealth &&
		(!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig->lowMana);
}

bool BuffTrigger::IsActive()
{
    Unit* target = GetTarget();
	return SpellTrigger::IsActive() && !botAI->HasAura(spell, target, true);
}

Value<Unit*>* BuffOnPartyTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member without aura", spell);
}

Value<Unit*>* DebuffOnAttackerTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("attacker without aura", spell);
}

bool NoAttackersTrigger::IsActive()
{
    return !AI_VALUE(Unit*, "current target") && AI_VALUE(uint8, "attacker count") > 0;
}

bool InvalidTargetTrigger::IsActive()
{
    return AI_VALUE2(bool, "invalid target", "current target");
}

bool NoTargetTrigger::IsActive()
{
	return !AI_VALUE(Unit*, "current target");
}

bool MyAttackerCountTrigger::IsActive()
{
    return AI_VALUE(uint8, "my attacker count") >= amount;
}

bool AoeTrigger::IsActive()
{
    return AI_VALUE(uint8, "aoe count") >= amount && AI_VALUE(uint8, "attacker count") >= amount;
}

bool NoFoodTrigger::IsActive()
{
    return AI_VALUE2(std::list<Item*>, "inventory items", "conjured food").empty();
}

bool NoDrinkTrigger::IsActive()
{
    return AI_VALUE2(std::vector<Item*>, "inventory items", "conjured water").empty();
}

bool TargetInSightTrigger::IsActive()
{
    return AI_VALUE(Unit*, "grind target");
}

bool DebuffTrigger::IsActive()
{
	return BuffTrigger::IsActive() && AI_VALUE2(uint8, "health", GetTargetName()) > 15;
}

bool SpellTrigger::IsActive()
{
	return GetTarget();
}

bool SpellCanBeCastTrigger::IsActive()
{
	Unit* target = GetTarget();
	return target && botAI->CanCastSpell(spell, target);
}

bool RandomTrigger::IsActive()
{
    if (time(0) - lastCheck < sPlayerbotAIConfig->repeatDelay / 1000)
        return false;

    lastCheck = time(0);
    int32 k = (int32)(probability / sPlayerbotAIConfig->randomChangeMultiplier);
    if (k < 1)
        k = 1;
    return (rand() % k) == 0;
}

bool AndTrigger::IsActive()
{
    return ls->IsActive() && rs->IsActive();
}

std::string const& AndTrigger::getName()
{
    std::string name(ls->getName());
    name = name + " and ";
    name = name + rs->getName();
    return name;
}

bool BoostTrigger::IsActive()
{
	return BuffTrigger::IsActive() && AI_VALUE(uint8, "balance") <= balance;
}

bool ItemCountTrigger::IsActive()
{
	return AI_VALUE2(uint8, "item count", item) < count;
}

bool InterruptSpellTrigger::IsActive()
{
	return SpellTrigger::IsActive() && botAI->IsInterruptableSpellCasting(GetTarget(), getName());
}

bool AttackerCountTrigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") >= amount;
}

bool HasAuraTrigger::IsActive()
{
	return botAI->HasAura(getName(), GetTarget());
}

bool TimerTrigger::IsActive()
{
    if (time(0) != lastCheck)
    {
        lastCheck = time(0);
        return true;
    }

    return false;
}

bool TankAoeTrigger::IsActive()
{
    if (!AI_VALUE(uint8, "attacker count"))
        return false;

    Unit* currentTarget = AI_VALUE(Unit*, "current target");
    if (!currentTarget)
        return true;

    Unit* tankTarget = AI_VALUE(Unit*, "tank target");
    if (!tankTarget || currentTarget == tankTarget)
        return false;

    return currentTarget->GetVictim() == AI_VALUE(Unit*, "self target");
}

bool IsBehindTargetTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    return target && AI_VALUE2(bool, "behind", "current target");
}

bool IsNotBehindTargetTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    return target && !AI_VALUE2(bool, "behind", "current target");
}

bool IsNotFacingTargetTrigger::IsActive()
{
    return !AI_VALUE2(bool, "facing", "current target");
}

bool HasCcTargetTrigger::IsActive()
{
    return AI_VALUE2(Unit*, "cc target", getName()) && !AI_VALUE2(Unit*, "current cc target", getName());
}

bool NoMovementTrigger::IsActive()
{
	return !AI_VALUE2(bool, "moving", "self target");
}

bool NoPossibleTargetsTrigger::IsActive()
{
    GuidVector targets = AI_VALUE(GuidVector, "possible targets");
    return !targets.size();
}

bool PossibleAdsTrigger::IsActive()
{
    return AI_VALUE(bool, "possible ads") && !AI_VALUE(ObjectGuid, "pull target");
}

bool NotDpsTargetActiveTrigger::IsActive()
{
    Unit* dps = AI_VALUE(Unit*, "dps target");
    Unit* target = AI_VALUE(Unit*, "current target");
    return dps && target != dps;
}

bool NotDpsAoeTargetActiveTrigger::IsActive()
{
    Unit* dps = AI_VALUE(Unit*, "dps aoe target");
    Unit* target = AI_VALUE(Unit*, "current target");
    return dps && target != dps;
}

bool EnemyPlayerIsAttacking::IsActive()
{
    Unit* enemyPlayer = AI_VALUE(Unit*, "enemy player target");
    Unit* target = AI_VALUE(Unit*, "current target");
    return enemyPlayer && !target;
}

bool IsSwimmingTrigger::IsActive()
{
    return AI_VALUE2(bool, "swimming", "self target");
}

bool HasNearestAddsTrigger::IsActive()
{
    GuidVector targets = AI_VALUE(GuidVector, "nearest adds");
    return targets.size();
}

bool HasItemForSpellTrigger::IsActive()
{
	std::string const& spell = getName();
    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    return spellId && AI_VALUE2(Item*, "item for spell", spellId);
}

bool TargetChangedTrigger::IsActive()
{
    Unit* oldTarget = context->GetValue<Unit*>("old target")->Get();
    Unit* target = context->GetValue<Unit*>("current target")->Get();
    return target && oldTarget != target;
}

Value<Unit*>* InterruptEnemyHealerTrigger::GetTargetValue()
{
    return context->GetValue<Unit*>("enemy healer target", spell);
}

bool RandomBotUpdateTrigger::IsActive()
{
    return RandomTrigger::IsActive() && AI_VALUE(bool, "random bot update");
}

bool NoNonBotPlayersAroundTrigger::IsActive()
{
    return AI_VALUE(GuidVector, "nearest non bot players").empty();
}

bool NewPlayerNearbyTrigger::IsActive()
{
    return AI_VALUE(ObjectGuid, "new player nearby");
}

bool CollisionTrigger::IsActive()
{
    return AI_VALUE2(bool, "collision", "self target");
}

bool GiveItemTrigger::IsActive()
{
    return AI_VALUE2(Unit*, "party member without item", item) && AI_VALUE2(uint8, "item count", item);
}

bool GiveFoodTrigger::IsActive()
{
    return AI_VALUE(Unit*, "party member without food") && AI_VALUE2(uint8, "item count", item);
}

bool GiveWaterTrigger::IsActive()
{
    return AI_VALUE(Unit*, "party member without water") && AI_VALUE2(uint8, "item count", item);
}

Value<Unit*>* SnareTargetTrigger::GetTargetValue()
{
    return context->GetValue<Unit*>("snare target", spell);
}

bool StayTimeTrigger::IsActive()
{
    time_t stayTime = AI_VALUE(time_t, "stay time");
    time_t now = time(0);
    return delay && stayTime && now > stayTime + 2 * delay / 1000;
}
