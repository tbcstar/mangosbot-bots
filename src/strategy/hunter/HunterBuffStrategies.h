#pragma once

#include "GenericHunterStrategy.h"
#include "../generic/NonCombatStrategy.h"

namespace botAI
{
    class HunterBuffSpeedStrategy : public NonCombatStrategy
    {
    public:
        HunterBuffSpeedStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }
        std::string const& getName() override { return "bspeed"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

    class HunterBuffManaStrategy : public NonCombatStrategy
    {
    public:
        HunterBuffManaStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }
        std::string const& getName() override { return "bmana"; }

    public:
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    };

	class HunterBuffDpsStrategy : public NonCombatStrategy
	{
	public:
		HunterBuffDpsStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }
		std::string const& getName() override { return "bdps"; }

	public:
		void InitTriggers(std::vector<TriggerNode*>& triggers) override;
	};

	class HunterNatureResistanceStrategy : public NonCombatStrategy
	{
	public:
		HunterNatureResistanceStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }
		std::string const& getName() override { return "rnature"; }

	public:
		void InitTriggers(std::vector<TriggerNode*>& triggers) override;
	};
}
