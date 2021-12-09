/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericMageStrategy.h"

class PlayerbotAI;

class ArcaneMageStrategy : public GenericMageStrategy
{
    public:
        ArcaneMageStrategy(PlayerbotAI* botAI);

        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const& getName() override { return "arcane"; }
        NextAction** getDefaultActions() override;
};