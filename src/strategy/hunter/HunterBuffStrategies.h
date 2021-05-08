#pragma once

#include "GenericHunterStrategy.h"
#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class HunterBuffSpeedStrategy : public NonCombatStrategy
    {
    public:
        HunterBuffSpeedStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "bspeed"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class HunterBuffManaStrategy : public NonCombatStrategy
    {
    public:
        HunterBuffManaStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
        virtual string getName() { return "bmana"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

	class HunterBuffDpsStrategy : public NonCombatStrategy
	{
	public:
		HunterBuffDpsStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
		virtual string getName() { return "bdps"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};

	class HunterNatureResistanceStrategy : public NonCombatStrategy
	{
	public:
		HunterNatureResistanceStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}
		virtual string getName() { return "rnature"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};
}
