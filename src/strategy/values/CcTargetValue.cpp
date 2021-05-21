#include "botpch.h"
#include "../../playerbot.h"
#include "CcTargetValue.h"
#include "../../PlayerbotAIConfig.h"
#include "../../ServerFacade.h"
#include "../Action.h"

using namespace botAI;

class FindTargetForCcStrategy : public FindTargetStrategy
{
public:
    FindTargetForCcStrategy(PlayerbotAI* botAI, std::string const& spell) : FindTargetStrategy(botAI)
    {
        this->spell = spell;
        maxDistance = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = botAI->GetBot();

        if (!botAI->CanCastSpell(spell, creature))
            return;

        if (*botAI->GetAiObjectContext()->GetValue<Unit*>("rti cc target") == creature)
        {
            result = creature;
            return;
        }

        if (*botAI->GetAiObjectContext()->GetValue<Unit*>("current target") == creature)
            return;

        uint8 health = creature->GetHealthPercent();
        if (health < sPlayerbotAIConfig->mediumHealth)
            return;

        float minDistance = botAI->GetRange("spell");
        Group* group = bot->GetGroup();
        if (!group)
            return;

        if (*botAI->GetAiObjectContext()->GetValue<uint8>("aoe count") > 2)
        {
            WorldLocation aoe = *botAI->GetAiObjectContext()->GetValue<WorldLocation>("aoe position");
            if (sServerFacade->IsDistanceLessOrEqualThan(sServerFacade->GetDistance2d(creature, aoe.GetPositionX(), aoe.GetPositionY()), sPlayerbotAIConfig->aoeRadius))
                return;
        }

        int tankCount, dpsCount;
        GetPlayerCount(creature, &tankCount, &dpsCount);
        if (!tankCount || !dpsCount)
        {
            result = creature;
            return;
        }

        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *member = ObjectAccessor::FindPlayer(itr->guid);
            if (!member || !sServerFacade->IsAlive(member) || member == bot)
                continue;

            if (!botAI->IsTank(member))
                continue;

            float distance = member->GetDistance(creature);
            if (distance < minDistance)
                minDistance = distance;
        }

        if (!result || minDistance > maxDistance)
        {
            result = creature;
            maxDistance = minDistance;
        }
    }

private:
    string spell;
    float maxDistance;
};

Unit* CcTargetValue::Calculate()
{
    FindTargetForCcStrategy strategy(botAI, qualifier);
    return FindTarget(&strategy);
}
