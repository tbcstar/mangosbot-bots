#include "botpch.h"
#include "../../playerbot.h"
#include "CheckMountStateAction.h"

#include "../../ServerFacade.h"
using namespace ai;

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

	Unit::AuraList const& auras = master->GetAurasByType(SPELL_AURA_MOUNTED);
	if (auras.empty()) return false;

	const SpellEntry* masterSpell = auras.front()->GetSpellProto();
	int32 masterSpeed = max(masterSpell->EffectBasePoints[1], masterSpell->EffectBasePoints[2]);

	map<int32, vector<uint32> > spells;
	for (PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
	{
		uint32 spellId = itr->first;
		if (itr->second.state == PLAYERSPELL_REMOVED || itr->second.disabled || IsPassiveSpell(spellId))
			continue;

		const SpellEntry* spellInfo = sServerFacade->LookupSpellInfo(spellId);
		if (!spellInfo || spellInfo->EffectApplyAuraName[0] != SPELL_AURA_MOUNTED)
			continue;

		int32 effect = max(spellInfo->EffectBasePoints[1], spellInfo->EffectBasePoints[2]);
		if (effect < masterSpeed)
			continue;

		spells[effect].push_back(spellId);
	}

	for (map<int32, vector<uint32> >::iterator i = spells.begin(); i != spells.end(); ++i)
	{
		vector<uint32>& ids = i->second;
		int index = urand(0, ids.size() - 1);
		if (index >= ids.size())
			continue;

		botAI->CastSpell(ids[index], bot);
		return true;
	}

    list<Item*> items = AI_VALUE2(list<Item*>, "inventory items", "mount");
    if (!items.empty()) return UseItemAuto(*items.begin());

    return false;
}
