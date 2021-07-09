/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PassTroughStrategy.h"

class BGStrategy : public PassTroughStrategy
{
    public:
        BGStrategy(PlayerbotAI* ai);

        uint32 GetType() const override { return STRATEGY_TYPE_NONCOMBAT; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "bg"; }
};

class BattlegroundStrategy : public Strategy
{
    public:
        BattlegroundStrategy(PlayerbotAI* ai) : Strategy(ai) {};

        uint32 GetType() const override { return STRATEGY_TYPE_NONCOMBAT; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "battleground"; }
};

class WarsongStrategy : public Strategy
{
    public:
        WarsongStrategy(PlayerbotAI* ai) : Strategy(ai) {};

        uint32 GetType() const override { return STRATEGY_TYPE_GENERIC; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "warsong"; }
};

class AlteracStrategy : public Strategy
{
    public:
        AlteracStrategy(PlayerbotAI* ai) : Strategy(ai) {};

        uint32 GetType() const override { return STRATEGY_TYPE_GENERIC; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "alterac"; }
};

class ArathiStrategy : public Strategy
{
    public:
        ArathiStrategy(PlayerbotAI* ai) : Strategy(ai) {};

        uint32 GetType() const override { return STRATEGY_TYPE_GENERIC; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "arathi"; }
};

class ArenaStrategy : public Strategy
{
    public:
        ArenaStrategy(PlayerbotAI* ai) : Strategy(ai) {};

        uint32 GetType() const override { return STRATEGY_TYPE_GENERIC; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "arena"; }
};

