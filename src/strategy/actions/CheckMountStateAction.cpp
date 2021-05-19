/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CheckMountStateAction.h"
#include "../Event.h"
#include "../../Playerbot.h"
#include "../../ServerFacade.h"

bool CheckMountStateAction::Execute(Event event)
{
	Player* master = GetMaster();
	if (!bot->GetGroup() || !master || bot->GetGroup()->GetLeaderGUID() != master->GetGUID())
		return false;

	if (bot->HasUnitState(UNIT_STATE_IN_FLIGHT) || bot->IsFlying())
		return false;

	bool farFromMaster = sServerFacade->IsDistanceGreaterThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig->sightDistance);
	if (master->IsMounted() && !bot->IsMounted() && !farFromMaster)
	{
		return Mount();
	}

	if ((farFromMaster || !master->IsMounted()) && bot->IsMounted())
	{
		WorldPacket emptyPacket;
		bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);
		return true;
	}

	return false;
}

bool CheckMountStateAction::Mount()
{
	Player* master = GetMaster();
	botAI->RemoveShapeshift();

	Unit::AuraEffectList const& auras = master->GetAuraEffectsByType(SPELL_AURA_MOUNTED);
	if (auras.empty())
        return false;

	SpellInfo const* masterSpellInfo = auras.front()->GetSpellInfo();
	int32 masterSpeed = std::max(masterSpellInfo->Effects[1].BasePoints, masterSpellInfo->Effects[2].BasePoints);

	std::map<int32, std::vector<uint32> > spells;
	for (PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
	{
		uint32 spellId = itr->first;
		if (itr->second->State == PLAYERSPELL_REMOVED || !itr->second->Active)
			continue;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
		if (!spellInfo || spellInfo->IsPassive() || spellInfo->Effects[0].ApplyAuraName != SPELL_AURA_MOUNTED)
			continue;

		int32 effect = std::max(spellInfo->Effects[1].BasePoints, spellInfo->Effects[2].BasePoints);
		if (effect < masterSpeed)
			continue;

		spells[effect].push_back(spellId);
	}

	for (std::map<int32, std::vector<uint32> >::iterator i = spells.begin(); i != spells.end(); ++i)
	{
        std::vector<uint32>& ids = i->second;
		uint32 index = urand(0, ids.size() - 1);
		if (index >= ids.size())
			continue;

		botAI->CastSpell(ids[index], bot);
		return true;
	}

    std::vector<Item*> items = AI_VALUE2(std::vector<Item*>, "inventory items", "mount");
    if (!items.empty())
        return UseItemAuto(*items.begin());

    return false;
}
