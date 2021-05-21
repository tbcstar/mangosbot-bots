#include "botpch.h"
#include "../../playerbot.h"
#include "PartyMemberWithoutAuraValue.h"

#include "../../ServerFacade.h"
using namespace botAI;

extern vector<string> split(const string &s, char delim);

class PlayerWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutAuraPredicate(PlayerbotAI* botAI, std::string const& aura) :
        PlayerbotAIAware(botAI), FindPlayerPredicate(), auras(split(aura, ',')) { }

public:
    virtual bool Check(Unit* unit)
    {
        Pet* pet = dynamic_cast<Pet*>(unit);
        if (pet && (pet->getPetType() == MINI_PET || pet->getPetType() == SUMMON_PET))
            return false;

        if (!sServerFacade->IsAlive(unit)) return false;

        for (vector<string>::iterator i = auras.begin(); i != auras.end(); ++i)
        {
            if (botAI->HasAura(*i, unit))
                return false;
        }

        return true;
    }

private:
    vector<string> auras;
};

Unit* PartyMemberWithoutAuraValue::Calculate()
{
	PlayerWithoutAuraPredicate predicate(botAI, qualifier);
    return FindPartyMember(predicate);
}

