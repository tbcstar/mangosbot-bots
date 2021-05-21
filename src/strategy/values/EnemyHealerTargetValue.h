#pragma once
#include "../Value.h"

namespace botAI
{
    class EnemyHealerTargetValue : public UnitCalculatedValue, public Qualified
	{
	public:
        EnemyHealerTargetValue(PlayerbotAI* botAI) :
            UnitCalculatedValue(botAI, "enemy healer target") { }

    protected:
        virtual Unit* Calculate();
	};
}
