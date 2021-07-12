/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericWarlockStrategy.h"
class TankWarlockStrategy : public GenericWarlockStrategy
{
    public:
        TankWarlockStrategy(PlayerbotAI* botAI);

        std::string const& getName() override { return "tank"; }
        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        NextAction** getDefaultActions() override;
};
