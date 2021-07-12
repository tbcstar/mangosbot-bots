/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ChangeStrategyAction.h"
class SwitchToMeleeAction : public ChangeCombatStrategyAction
{
    public:
        SwitchToMeleeAction(PlayerbotAI* botAI) : ChangeCombatStrategyAction(botAI, "-ranged,+close") { }

        bool Execute(Event event) override;
        bool isUseful() override;
};

class SwitchToRangedAction : public ChangeCombatStrategyAction
{
    public:
        SwitchToRangedAction(PlayerbotAI* botAI) : ChangeCombatStrategyAction(botAI, "-close,+ranged") { }

        bool Execute(Event event) override;
        bool isUseful() override;
};
