/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NonCombatStrategy.h"
class HunterBuffSpeedStrategy : public NonCombatStrategy
{
    public:
        HunterBuffSpeedStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }

        std::string const& getName() override { return "bspeed"; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

class HunterBuffManaStrategy : public NonCombatStrategy
{
    public:
        HunterBuffManaStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }

        std::string const& getName() override { return "bmana"; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

class HunterBuffDpsStrategy : public NonCombatStrategy
{
	public:
		HunterBuffDpsStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }

		std::string const& getName() override { return "bdps"; }
		void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

class HunterNatureResistanceStrategy : public NonCombatStrategy
{
	public:
		HunterNatureResistanceStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) { }

		std::string const& getName() override { return "rnature"; }
		void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};
