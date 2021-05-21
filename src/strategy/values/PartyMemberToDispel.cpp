#include "botpch.h"
#include "../../playerbot.h"
#include "PartyMemberToDispel.h"

#include "../../ServerFacade.h"
using namespace botAI;

class PartyMemberToDispelPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberToDispelPredicate(PlayerbotAI* botAI, uint32 dispelType) :
        PlayerbotAIAware(botAI), FindPlayerPredicate(), dispelType(dispelType) { }

public:
    virtual bool Check(Unit* unit)
    {
        Pet* pet = dynamic_cast<Pet*>(unit);
        if (pet && (pet->getPetType() == MINI_PET || pet->getPetType() == SUMMON_PET))
            return false;

        return sServerFacade->IsAlive(unit) && botAI->HasAuraToDispel(unit, dispelType);
    }

private:
    uint32 dispelType;
};

Unit* PartyMemberToDispel::Calculate()
{
    uint32 dispelType = atoi(qualifier.c_str());

    PartyMemberToDispelPredicate predicate(botAI, dispelType);
    return FindPartyMember(predicate);
}
