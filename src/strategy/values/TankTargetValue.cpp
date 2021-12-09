/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AttackersValue.h"
#include "TankTargetValue.h"
#include "Playerbot.h"

class FindTargetForTankStrategy : public FindNonCcTargetStrategy
{
    public:
        FindTargetForTankStrategy(PlayerbotAI* botAI) : FindNonCcTargetStrategy(botAI), minThreat(0) { }

        void CheckAttacker(Unit* creature, ThreatManager* threatManager) override
        {
            Player* bot = botAI->GetBot();
            if (IsCcTarget(creature))
                return;

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