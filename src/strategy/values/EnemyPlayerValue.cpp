#include "botpch.h"
#include "../../playerbot.h"
#include "EnemyPlayerValue.h"
#include "TargetValue.h"

using namespace ai;
using namespace std;

class FindEnemyPlayerStrategy : public FindTargetStrategy
{
public:
    FindEnemyPlayerStrategy(PlayerbotAI* botAI) : FindTargetStrategy(botAI)
    {
    }

public:
    virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager)
    {
        if (!result)
        {
            Player* enemy = dynamic_cast<Player*>(attacker);
            if (enemy &&
                    botAI->IsOpposing(enemy) &&
                    enemy->IsPvP() &&
                    !sPlayerbotAIConfig->IsInPvpProhibitedZone(enemy->GetAreaId()) &&
                    !enemy->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) &&
                    !enemy->HasStealthAura() &&
                    !enemy->HasInvisibilityAura())
                result = attacker;
        }
    }

};


Unit* EnemyPlayerValue::Calculate()
{
    FindEnemyPlayerStrategy strategy(botAI);
    return FindTarget(&strategy);
}
