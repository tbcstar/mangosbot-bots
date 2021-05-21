#pragma once
#include "../Value.h"

namespace botAI
{
    class FindPlayerPredicate
    {
    public:
        virtual bool Check(Unit*) = 0;
    };

    class SpellEntryPredicate
    {
    public:
        virtual bool Check(SpellEntry const*) = 0;
    };

    class PartyMemberValue : public UnitCalculatedValue
	{
	public:
        PartyMemberValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI) { }

    public:
        bool IsTargetOfSpellCast(Player* target, SpellEntryPredicate &predicate);

    protected:
        Unit* FindPartyMember(FindPlayerPredicate &predicate);
        Unit* FindPartyMember(list<Player*>* party, FindPlayerPredicate &predicate);
        bool Check(Unit* player);
	};
}
