/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"

class Event;
class PlayerbotAI;

struct CreatureData;

class BGJoinAction : public Action
{
    public:
        BGJoinAction(PlayerbotAI* botAI, std::string const& name = "bg join") : Action(botAI, name) { }

        bool isUseful() override;
        virtual bool canJoinBg(BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId);
        virtual bool shouldJoinBg(BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId);
        bool Execute(Event event) override;
        virtual bool gatherArenaTeam(ArenaType type);

    protected:
        bool JoinQueue(uint32 type);
        std::vector<uint32> bgList;
        std::vector<uint32> ratedList;
};

class FreeBGJoinAction : public BGJoinAction
{
    public:
        FreeBGJoinAction(PlayerbotAI* botAI, std::string const& name = "free bg join") : BGJoinAction(botAI, name) {}

        bool shouldJoinBg(BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId) override;
};

class BGLeaveAction : public Action
{
public:
        BGLeaveAction(PlayerbotAI* botAI, std::string const& name = "bg leave") : Action(botAI) { }

        bool Execute(Event event) override;
};

class BGStatusAction : public Action
{
public:
        BGStatusAction(PlayerbotAI* botAI) : Action(botAI, "bg status") { }

        bool Execute(Event event) override;
        bool isUseful() override;
};

class BGStatusCheckAction : public Action
{
    public:
        BGStatusCheckAction(PlayerbotAI* botAI, std::string const& name = "bg status check") : Action(botAI, name) { }

        bool Execute(Event event) override;
        bool isUseful() override;
};
