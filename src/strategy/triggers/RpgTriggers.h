/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Trigger.h"

class PlayerbotAI;

class NoRpgTargetTrigger : public Trigger
{
    public:
        NoRpgTargetTrigger(PlayerbotAI* botAI) : Trigger(botAI, "no rpg target") { }

        bool IsActive() override;
};

class FarFromRpgTargetTrigger : public Trigger
{
    public:
        FarFromRpgTargetTrigger(PlayerbotAI* ai, std::string const& name = "far from rpg target") : Trigger(ai, name) {}

        bool IsActive() override;
};

class NearRpgTargetTrigger : public FarFromRpgTargetTrigger
{
    public:
        NearRpgTargetTrigger(PlayerbotAI* ai) : FarFromRpgTargetTrigger(ai, "near rpg target") {}

        bool IsActive() override { return !FarFromRpgTargetTrigger::IsActive(); };
};
