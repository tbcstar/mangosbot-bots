#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class PartyMemberWithoutItemValue : public PartyMemberValue, public Qualified
    {
    public:
        PartyMemberWithoutItemValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) :
          PartyMemberValue(botAI) {}

    protected:
        virtual Unit* Calculate();
        virtual FindPlayerPredicate* CreatePredicate();
    };

    class PartyMemberWithoutFoodValue : public PartyMemberWithoutItemValue
    {
    public:
        PartyMemberWithoutFoodValue(PlayerbotAI* botAI) : PartyMemberWithoutItemValue(botAI) {}

    protected:
        virtual FindPlayerPredicate* CreatePredicate();
    };

    class PartyMemberWithoutWaterValue : public PartyMemberWithoutItemValue
    {
    public:
        PartyMemberWithoutWaterValue(PlayerbotAI* botAI) : PartyMemberWithoutItemValue(botAI) {}

    protected:
        virtual FindPlayerPredicate* CreatePredicate();
    };
}
