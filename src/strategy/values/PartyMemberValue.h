/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Player.h"
#include "../Value.h"

class PlayerbotAI;

class FindPlayerPredicate
{
    public:
        virtual bool Check(Unit* /*unit*/) = 0;
};

class SpellEntryPredicate
{
    public:
        virtual bool Check(SpellInfo const* /*spellInfo*/) = 0;
};

class PartyMemberValue : public UnitCalculatedValue
{
	public:
        PartyMemberValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI) { }

        bool IsTargetOfSpellCast(Player* target, SpellEntryPredicate& predicate);

    protected:
        Unit* FindPartyMember(FindPlayerPredicate& predicate);
        Unit* FindPartyMember(std::vector<Player*>* party, FindPlayerPredicate& predicate);
        virtual bool Check(Unit* player);
};
