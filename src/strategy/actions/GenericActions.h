/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AttackAction.h"
class MeleeAction : public AttackAction
{
    public:
        MeleeAction(PlayerbotAI* botAI) : AttackAction(botAI, "melee") { }

        std::string const& GetTargetName() override { return "current target"; }
};
