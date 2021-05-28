/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "EnemyPlayerValue.h"
#include "../../Playerbot.h"

class FindEnemyPlayerStrategy : public FindTargetStrategy
{
    public:
        FindEnemyPlayerStrategy(PlayerbotAI* botAI) : FindTargetStrategy(botAI) { }

        void CheckAttacker(Unit* attacker, ThreatManager* threatManager) override
        {
            if (!result)
            {
                if (Player* enemy = attacker->ToPlayer())
                {
                    if (botAI->IsOpposing(enemy) && enemy->IsPvP() && !sPlayerbotAIConfig->IsInPvpProhibitedZone(enemy->GetAreaId()) &&
                        !enemy->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) && !enemy->HasStealthAura() && !enemy->HasInvisibilityAura())
                    {
                        result = attacker;
                    }
                }
            }
        }
};

Unit* EnemyPlayerValue::Calculate()
{
    FindEnemyPlayerStrategy strategy(botAI);
    return FindTarget(&strategy);
}
