#include "botpch.h"
#include "../../playerbot.h"
#include "TankTargetValue.h"

#include "AttackersValue.h"
using namespace botAI;

class FindTargetForTankStrategy : public FindNonCcTargetStrategy
{
public:
    FindTargetForTankStrategy(PlayerbotAI* botAI) : FindNonCcTargetStrategy(botAI)
    {
        minThreat = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = botAI->GetBot();
        if (IsCcTarget(creature)) return;

        float threat = threatManager->getThreat(bot);
        if (!result || (minThreat - threat) > 0.1f)
        {
            minThreat = threat;
            result = creature;
        }
    }

protected:
    float minThreat;
};


Unit* TankTargetValue::Calculate()
{
    FindTargetForTankStrategy strategy(botAI);
    return FindTarget(&strategy);
}
