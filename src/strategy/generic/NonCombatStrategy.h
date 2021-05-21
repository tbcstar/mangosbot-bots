/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "../Strategy.h"

class PlayerbotAI;

class NonCombatStrategy : public Strategy
{
    public:
        NonCombatStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

		uint32 GetType() const override { return STRATEGY_TYPE_NONCOMBAT; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

class LfgStrategy : public Strategy
{
    public:
        LfgStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

		uint32 GetType() const override { return STRATEGY_TYPE_NONCOMBAT; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "lfg"; }
};

class CollisionStrategy : public Strategy
{
    public:
        CollisionStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

		uint32 GetType() const override { return STRATEGY_TYPE_NONCOMBAT; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "collision"; }
};
