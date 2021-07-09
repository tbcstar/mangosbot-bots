/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Trigger.h"

class PlayerbotAI;

class EnemyPlayerNear : public Trigger
{
    public:
        EnemyPlayerNear(PlayerbotAI* ai) : Trigger(ai, "enemy player near") { }

        bool IsActive() override;
};

class PlayerHasNoFlag : public Trigger
{
    public:
        PlayerHasNoFlag(PlayerbotAI* ai) : Trigger(ai, "player has no flag") { }

        bool IsActive() override;
};

class PlayerHasFlag : public Trigger
{
    public:
        PlayerHasFlag(PlayerbotAI* ai) : Trigger(ai, "player has flag") { }

        bool IsActive() override;
};

class EnemyFlagCarrierNear : public Trigger
{
    public:
        EnemyFlagCarrierNear(PlayerbotAI* ai) : Trigger(ai, "enemy flagcarrier near") { }

        bool IsActive() override;
};

class TeamFlagCarrierNear : public Trigger
{
    public:
        TeamFlagCarrierNear(PlayerbotAI* ai) : Trigger(ai, "team flagcarrier near") { }

        bool IsActive() override;
};

class TeamHasFlag : public Trigger
{
    public:
        TeamHasFlag(PlayerbotAI* ai) : Trigger(ai, "team has flag") { }

        bool IsActive() override;
};

class EnemyTeamHasFlag : public Trigger
{
    public:
        EnemyTeamHasFlag(PlayerbotAI* ai) : Trigger(ai, "enemy team has flag") { }

        bool IsActive() override;
};

class PlayerIsInBattleground : public Trigger
{
    public:
        PlayerIsInBattleground(PlayerbotAI* ai) : Trigger(ai, "in battleground") {}

        bool IsActive() override;
};

class BgWaitingTrigger : public Trigger
{
    public:
        BgWaitingTrigger(PlayerbotAI* ai) : Trigger(ai, "bg waiting", 30) {}

        bool IsActive() override;
};

class BgActiveTrigger : public Trigger
{
    public:
        BgActiveTrigger(PlayerbotAI* ai) : Trigger(ai, "bg active", 1) {}

        bool IsActive() override;
};

class PlayerIsInBattlegroundWithoutFlag : public Trigger
{
    public:
        PlayerIsInBattlegroundWithoutFlag(PlayerbotAI* ai) : Trigger(ai, "in battleground without flag") {}

        bool IsActive() override;
};

class PlayerWantsInBattlegroundTrigger : public Trigger
{
    public:
        PlayerWantsInBattlegroundTrigger(PlayerbotAI* ai) : Trigger(ai, "wants in bg") {}

        bool IsActive() override;
};
