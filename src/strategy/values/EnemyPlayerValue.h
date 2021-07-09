/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "TargetValue.h"
#include "PossibleTargetsValue.h"

class PlayerbotAI;
class Unit;

/*class EnemyPlayerValue : public TargetValue
{
	public:
        EnemyPlayerValue(PlayerbotAI* botAI) : TargetValue(botAI) { }

        Unit* Calculate() override;
};*/

class NearestEnemyPlayersValue : public PossibleTargetsValue
{
    public:
        NearestEnemyPlayersValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
            PossibleTargetsValue(ai, "nearest enemy players", range) { }

    public:
        bool AcceptUnit(Unit* unit) override;
};

class EnemyPlayerValue : public UnitCalculatedValue
{
    public:
        EnemyPlayerValue(PlayerbotAI* ai) : UnitCalculatedValue(ai) { }

        Unit* Calculate() override;

    private:
        float GetMaxAttackDistance();
};
