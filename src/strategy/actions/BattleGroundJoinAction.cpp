/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "BattleGroundJoinAction.h"
#include "ArenaTeam.h"
#include "ArenaTeamMgr.h"
#include "BattlegroundMgr.h"
#include "Event.h"
#include "Playerbot.h"
#include "PositionValue.h"

bool BGJoinAction::Execute(Event event)
{
    uint32 queueType = AI_VALUE(uint32, "bg type");
    if (!queueType) // force join to fill bg
    {
        if (bgList.empty())
            return false;

        BattleGroundQueueTypeId queueTypeId = (BattleGroundQueueTypeId)bgList[urand(0, bgList.size() - 1)];
        BattleGroundTypeId bgTypeId = sServerFacade.BgTemplateId(queueTypeId);
        BattleGroundBracketId bracketId;
        bool isArena = false;
        bool isRated = false;

        BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
        if (!bg)
            return false;

        BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
        uint32 mapId = bg->GetMapId();
        PvPDifficultyEntry const* pvpDiff = GetBattlegroundBracketByLevel(mapId, bot->getLevel());
        if (!pvpDiff)
            return false;

        bracketId = pvpDiff->GetBracketId();

        // Find BattleMaster by Entry
        //uint32 BmEntry = sRandomPlayerbotMgr.GetBattleMasterEntry(bot, bgTypeId, true);
        //if (!BmEntry)
        //{
        //    LOG_ERROR("playerbots", "Bot #%d <%s> could not find Battlemaster for %d", bot->GetGUIDLow(), bot->GetName().c_str(), bgTypeId);
        //    return false;
        //}

        if (ArenaType type = sServerFacade.BgArenaType(queueTypeId))
        {
            isArena = true;

            std::vector<uint32>::iterator i = find(ratedList.begin(), ratedList.end(), queueTypeId);
            if (i != ratedList.end())
                isRated = true;

            if (isRated && !gatherArenaTeam(type))
                return false;

            botAI->GetAiObjectContext()->GetValue<uint32>("arena type")->Set(isRated);
        }

        // set bg type and bm guid
        //botAI->GetAiObjectContext()->GetValue<ObjectGuid>("bg master")->Set(BmGuid);
        botAI->GetAiObjectContext()->GetValue<uint32>("bg type")->Set(queueTypeId);
        queueType = queueTypeId;
    }

    return JoinQueue(queueType);
}

bool BGJoinAction::gatherArenaTeam(ArenaType type)
{
    ArenaTeam* arenateam = nullptr;
    for (uint32 arena_slot = 0; arena_slot < MAX_ARENA_SLOT; ++arena_slot)
    {
        ArenaTeam* temp = sObjectMgr.GetArenaTeamById(bot->GetArenaTeamId(arena_slot));
        if (!temp)
            continue;

        if (temp->GetCaptainGuid() != bot->GetObjectGuid())
            continue;

        if (temp->GetType() != type)
            continue;

        arenateam = temp;
    }

    if (!arenateam)
        return false;

    std::vector<uint32> members;

    // search for arena team members and make them online
    for (ArenaTeam::MemberList::iterator itr = arenateam->GetMembers().begin(); itr != arenateam->GetMembers().end(); ++itr)
    {
        bool offline = false;
        Player* member = sObjectMgr.GetPlayer(itr->guid);
        if (!member)
        {
            offline = true;
        }
        //if (!member && !sObjectMgr.GetPlayerAccountIdByGUID(itr->guid))
        //    continue;

        if (offline)
            sRandomPlayerbotMgr.AddPlayerBot(itr->guid.GetRawValue(), 0);

        if (member)
        {
            if (member->GetGroup() && !member->GetGroup()->IsLeader(bot->GetObjectGuid()))
                continue;

            if (member->IsInCombat())
                continue;

            if (member->GetObjectGuid() == bot->GetObjectGuid())
                continue;

            if (!member->GetPlayerbotAI())
                continue;

            member->GetPlayerbotAI()->Reset();
        }

        if (member)
            members.push_back(member->GetGUIDLow());
    }

    if (!members.size() || (int)members.size() < (int)(arenateam->GetType() - 1))
    {
        LOG_INFO("playerbots", "Team #%d <%s> has not enough members for match", arenateam->GetId(), arenateam->GetName().c_str());
        return false;
    }

    Group* group = new Group();
    uint32 count = 1;
    group->Create(bot->GetObjectGuid(), bot->GetName());

    for (auto i = begin(members); i != end(members); ++i)
    {
        if (*i == bot->GetGUIDLow())
            continue;

        if (count >= (int)arenateam->GetType())
            break;

        Player* member = sObjectMgr.GetPlayer(ObjectGuid(HIGHGUID_PLAYER, *i));
        if (!member)
            continue;

        if (member->getLevel() < 70)
            continue;

        if (!group->AddMember(ObjectGuid(HIGHGUID_PLAYER, *i), member->GetName()))
            continue;

        if (!member->GetPlayerbotAI())
            continue;

        member->GetPlayerbotAI()->Reset();
        member->TeleportTo(bot->GetMapId(), bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ(), 0);


        LOG_INFO("playerbots", "Bot #%d <%s>: member of <%s>", member->GetGUIDLow(), member->GetName().c_str(), arenateam->GetName().c_str());

        count++;
    }

    if (group && group->GetMembersCount() == (uint32)arenateam->GetType())
    {
        LOG_INFO("playerbots", "Team #%d <%s> is ready for match", arenateam->GetId(), arenateam->GetName().c_str());
        return true;
    }
    else
    {
        LOG_INFO("playerbots", "Team #%d <%s> is not ready for match", arenateam->GetId(), arenateam->GetName().c_str());
        group->Disband();
    }

    return false;
}

bool BGJoinAction::canJoinBg(BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId)
{
    // check if bot can join this bg/bracket
    BattleGroundTypeId bgTypeId = sServerFacade.BgTemplateId(queueTypeId);

    // check if already in queue
    if (bot->InBattleGroundQueueForBattleGroundQueueType(queueTypeId))
        return false;

    // check too low/high level
    if (!bot->GetBGAccessByLevel(bgTypeId))
        return false;

    // check bracket
    BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
    uint32 mapId = bg->GetMapId();
    PvPDifficultyEntry const* pvpDiff = GetBattlegroundBracketByLevel(mapId, bot->getLevel());
    if (!pvpDiff)
        return false;

    BattleGroundBracketId bracket_temp = pvpDiff->GetBracketId();

    if (bracket_temp != bracketId)
        return false;

    return true;
}

bool BGJoinAction::shouldJoinBg(BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId)
{
    // check if bot should join (queue has real players)
    BattleGroundTypeId bgTypeId = sServerFacade.BgTemplateId(queueTypeId);
    BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
    if (!bg)
        return false;

    bool isArena = false;
    bool isRated = false;

    ArenaType type = sServerFacade.BgArenaType(queueTypeId);
    if (type != ARENA_TYPE_NONE)
        isArena = true;

    bool hasPlayers = (sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][0] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][1]) > 0;
    if (!hasPlayers)
        return false;

    // hack fix crash in queue remove event
    if (!isArena && bot->GetGroup())
        return false;

    uint32 BracketSize = bg->GetMaxPlayers();
    uint32 TeamSize = bg->GetMaxPlayersPerTeam();

    uint32 ACount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][0] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][0];
    uint32 HCount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][1] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][1];

    uint32 BgCount = ACount + HCount;
    uint32 SCount = 0;
    uint32 RCount = 0;

    uint32 TeamId = bot->GetTeam() == ALLIANCE ? 0 : 1;

    if (isArena)
    {
        uint32 rated_players = sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][1];
        if (rated_players)
        {
            isRated = true;
        }

        isArena = true;
        BracketSize = (uint32)(type * 2);
        TeamSize = type;
        ACount = sRandomPlayerbotMgr.ArenaBots[queueTypeId][bracketId][isRated][0];
        HCount = sRandomPlayerbotMgr.ArenaBots[queueTypeId][bracketId][isRated][1];
        BgCount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][isRated] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][isRated];
        SCount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][0] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][0];
        RCount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][1] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][1];
    }

    // do not try if not a captain of arena team
    if (isRated)
    {
        if (!sObjectMgr.GetArenaTeamByCaptain(bot->GetObjectGuid()))
            return false;

        // check if bot has correct team
        ArenaTeam* arenateam = nullptr;
        for (uint32 arena_slot = 0; arena_slot < MAX_ARENA_SLOT; ++arena_slot)
        {
            ArenaTeam* temp = sObjectMgr.GetArenaTeamById(bot->GetArenaTeamId(arena_slot));
            if (!temp)
                continue;

            if (temp->GetType() != type)
                continue;

            arenateam = temp;
        }

        if (!arenateam)
            return false;

        ratedList.push_back(queueTypeId);
    }

    bool needBots = sRandomPlayerbotMgr.NeedBots[queueTypeId][bracketId][isArena ? isRated : GetTeamIndexByTeamId(bot->GetTeam())];

    // add more bots if players are not invited or 1st BG instance is full
    if (needBots/* || (hasPlayers && BgCount > BracketSize && (BgCount % BracketSize) != 0)*/)
        return true;

    // do not join if BG queue is full
    if (BgCount >= BracketSize && (ACount >= TeamSize) && (HCount >= TeamSize))
    {
        return false;
    }

    if (!isArena && ((ACount >= TeamSize && TeamId == 0) || (HCount >= TeamSize && TeamId == 1)))
    {
        return false;
    }

    if (isArena && (((ACount >= TeamSize && HCount > 0) && TeamId == 0) || ((HCount >= TeamSize && ACount > 0) && TeamId == 1)))
    {
        return false;
    }

    if (isArena && (((ACount > TeamSize && HCount == 0) && TeamId == 1) || ((HCount > TeamSize && ACount == 0) && TeamId == 0)))
    {
        return false;
    }

    if (isArena && ((!isRated && SCount >= BracketSize) || (isRated && RCount >= BracketSize)))
    {
        return false;
    }

    return true;
}

bool BGJoinAction::isUseful()
{
    // do not try if BG bots disabled
    if (!sPlayerbotAIConfig.randomBotJoinBG)
        return false;

    // can't queue in BG
    if (bot->InBattleGround())
        return false;

    // do not try right after login
    if ((time(0) - bot->GetInGameTime()) < 30)
        return false;

    // check level
    if (bot->getLevel() < 10)
        return false;

    // do not try if with player master or in combat/group
    if (bot->GetPlayerbotAI()->HasActivePlayerMaster())
        return false;

    //if (bot->GetGroup())
    //    return false;

    if (bot->IsInCombat())
        return false;

    // check Deserter debuff
    if (!bot->CanJoinToBattleground())
        return false;

    // check if has free queue slots
    if (!bot->HasFreeBattleGroundQueueId())
        return false;

    // do not try if in dungeon
     //Map* map = bot->GetMap();
    //if (map && map->Instanceable())
    //    return false;

    bgList.clear();
    ratedList.clear();

    for (int i = BG_BRACKET_ID_FIRST; i < MAX_BATTLEGROUND_BRACKETS; ++i)
    {
        for (int j = BATTLEGROUND_QUEUE_AV; j < MAX_BATTLEGROUND_QUEUE_TYPES; ++j)
        {
            BattleGroundQueueTypeId queueTypeId = BattleGroundQueueTypeId(j);
            BattleGroundTypeId bgTypeId = sServerFacade.BgTemplateId(queueTypeId);
            BattleGroundBracketId bracketId = BattleGroundBracketId(i);

            if (!canJoinBg(queueTypeId, bracketId))
                continue;

            if (shouldJoinBg(queueTypeId, bracketId))
                bgList.push_back(queueTypeId);
        }
    }

    if (!bgList.empty())
        return true;

    return false;
}

bool BGJoinAction::JoinQueue(uint32 type)
{
    // ignore if player is already in BG
    if (bot->InBattleground())
        return false;

    // get BG TypeId
    BattlegroundQueueTypeId queueTypeId = BattlegroundQueueTypeId(type);
    BattlegroundTypeId bgTypeId = sServerFacade.BgTemplateId(queueTypeId);
    BattleGroundBracketId bracketId;

    Battleground* bg = sBattleGroundMgr->GetBattleGroundTemplate(bgTypeId);
    if (!bg)
        return false;

    BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
    uint32 mapId = bg->GetMapId();
    PvPDifficultyEntry const* pvpDiff = GetBattlegroundBracketByLevel(mapId, bot->getLevel());
    if (!pvpDiff)
        return false;

    bracketId = pvpDiff->GetBracketId();

    uint32 BracketSize = bg->GetMaxPlayers();
    uint32 TeamSize = bg->GetMaxPlayersPerTeam();
    uint32 TeamId = GetTeamIndexByTeamId(bot->GetTeam());

    // check if already in queue
    if (bot->InBattleGroundQueueForBattleGroundQueueType(queueTypeId))
        return false;

    // check bg req level
    if (!bot->GetBGAccessByLevel(bgTypeId))
        return false;

    // get BattleMaster unit
    // Find BattleMaster by Entry
    /*uint32 BmEntry = sRandomPlayerbotMgr.GetBattleMasterEntry(bot, bgTypeId, true);
    if (!BmEntry)
    {
        LOG_ERROR("playerbots", "Bot #%d <%s> could not find Battlemaster for %d", bot->GetGUIDLow(), bot->GetName().c_str(), bgTypeId);
        return false;
    }
    // check bm map
    CreatureDataPair const* dataPair = sRandomPlayerbotMgr.GetCreatureDataByEntry(BmEntry);
    CreatureData const* data = &dataPair->second;
    ObjectGuid BmGuid = ObjectGuid(HIGHGUID_UNIT, BmEntry, dataPair->first);
    if (data->mapid != bot->GetMapId())
    {
        LOG_ERROR("playerbots", "Bot #%d <%s> : Battlemaster is not in map for BG %d", bot->GetGUIDLow(), bot->GetName().c_str(), bgTypeId);
        return false;
    }*/

    // get BG MapId
    uint32 bgTypeId_ = bgTypeId;
    uint32 instanceId = 0; // 0 = First Available
    bool joinAsGroup = bot->GetGroup() && bot->GetGroup()->GetLeaderGUID() == bot->GetGUID();
    bool isPremade = false;
    bool isArena = false;
    bool isRated = false;
    uint8 arenaslot = 0;
    uint8 asGroup = false;

    std::string _bgType;

    // check if arena
    ArenaType arenaType = sServerFacade.BgArenaType(queueTypeId);
    if (arenaType != ARENA_TYPE_NONE)
        isArena = true;

    // get battlemaster
    Unit* unit = botAI->GetUnit(AI_VALUE2(CreatureDataPair const*, "bg master", bgTypeId));
    if (!unit && isArena)
    {
        LOG_ERROR("playerbots", "Bot %d could not find Battlemaster to join", bot->GetGUIDLow());
        return false;
    }

    // in wotlk only arena requires battlemaster guid
    ObjectGuid guid = unit->GetGUID();

    switch (bgTypeId)
    {
        case BATTLEGROUND_AV:
            _bgType = "AV";
            break;
        case BATTLEGROUND_WS:
            _bgType = "WSG";
            break;
        case BATTLEGROUND_AB:
            _bgType = "AB";
             break;
        case BATTLEGROUND_EY:
            _bgType = "EotS";
            break;
        default:
            break;
    }

    if (isArena)
    {
        isArena = true;
        BracketSize = type * 2;
        TeamSize = type;
        isRated = botAI->GetAiObjectContext()->GetValue<uint32>("arena type")->Get();

        if (joinAsGroup)
            asGroup = true;

        switch (arenaType)
        {
            case ARENA_TYPE_2v2:
                arenaslot = 0;
                _bgType = "2v2";
                break;
            case ARENA_TYPE_3v3:
                arenaslot = 1;
                _bgType = "3v3";
                break;
            case ARENA_TYPE_5v5:
                arenaslot = 2;
                _bgType = "5v5";
                break;
            default:
                break;
        }
    }

    LOG_INFO("playerbots", "Bot %s %s:%d <%s> queued %s %s",
        bot->GetGUID().ToString().c_str(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName().c_str(), _bgType.c_str(), isRated ? "Rated Arena" : isArena ? "Arena" : "");

    // refresh food/regs
    sRandomPlayerbotMgr.Refresh(bot);

    if (isArena)
    {
        if (isRated)
        {
            sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][isRated] += TeamSize;
            sRandomPlayerbotMgr.ArenaBots[queueTypeId][bracketId][isRated][TeamId] += TeamSize;
        }
        else
        {
            sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][isRated]++;
            sRandomPlayerbotMgr.ArenaBots[queueTypeId][bracketId][isRated][TeamId]++;
        }
    }
    else if (!joinAsGroup)
        sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][TeamId]++;
    else
        sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][TeamId] += bot->GetGroup()->GetMembersCount();

    botAI->GetAiObjectContext()->GetValue<uint32>("bg type")->Set(0);

    WorldPacket packet(CMSG_BATTLEMASTER_JOIN, 20);
    if (!isArena)
    {
        packet << unit->GetGUID() << bgTypeId_ << instanceId << joinAsGroup;
    }
    else
    {
        WorldPacket arena_packet(CMSG_BATTLEMASTER_JOIN_ARENA, 20);
        arena_packet << unit->GetGUID() << arenaslot << asGroup << isRated;
        bot->GetSession()->HandleBattlemasterJoinArena(arena_packet);
        return true;
    }

    bot->GetSession()->HandleBattlemasterJoinOpcode(packet);
       return true;
}

bool FreeBGJoinAction::shouldJoinBg(BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId)
{
    BattleGroundTypeId bgTypeId = sServerFacade.BgTemplateId(queueTypeId);
    BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
    if (!bg)
        return false;

    bool isArena = false;
    bool isRated = false;

    ArenaType type = sServerFacade.BgArenaType(queueTypeId);
    if (type != ARENA_TYPE_NONE)
        isArena = true;

    // hack fix crash in queue remove event
    if (!isArena && bot->GetGroup())
        return false;

    uint32 BracketSize = bg->GetMaxPlayers();
    uint32 TeamSize = bg->GetMaxPlayersPerTeam();

    uint32 ACount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][0] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][0];
    uint32 HCount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][1] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][1];

    uint32 BgCount = ACount + HCount;
    uint32 SCount, RCount = 0;

    uint32 TeamId = bot->GetTeam() == ALLIANCE ? 0 : 1;

    if (isArena)
    {
        uint32 rated_players = sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][1];
        if (rated_players)
        {
            isRated = true;
        }

        isArena = true;
        BracketSize = (uint32)(type * 2);
        TeamSize = type;
        ACount = sRandomPlayerbotMgr.ArenaBots[queueTypeId][bracketId][isRated][0];
        HCount = sRandomPlayerbotMgr.ArenaBots[queueTypeId][bracketId][isRated][1];
        BgCount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][isRated] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][isRated];
        SCount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][0] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][0];
        RCount = sRandomPlayerbotMgr.BgBots[queueTypeId][bracketId][1] + sRandomPlayerbotMgr.BgPlayers[queueTypeId][bracketId][1];
    }

    // do not try if not a captain of arena team

    if (isRated)
    {
        if (!sObjectMgr.GetArenaTeamByCaptain(bot->GetObjectGuid()))
            return false;

        // check if bot has correct team
        ArenaTeam* arenateam = nullptr;
        for (uint32 arena_slot = 0; arena_slot < MAX_ARENA_SLOT; ++arena_slot)
        {
            ArenaTeam* temp = sObjectMgr.GetArenaTeamById(bot->GetArenaTeamId(arena_slot));
            if (!temp)
                continue;

            if (temp->GetType() != type)
                continue;

            arenateam = temp;
        }

        if (!arenateam)
            return false;

        ratedList.push_back(queueTypeId);
    }

    bool needBots = sRandomPlayerbotMgr.NeedBots[queueTypeId][bracketId][isArena ? isRated : GetTeamIndexByTeamId(bot->GetTeam())];

    // add more bots if players are not invited or 1st BG instance is full
    if (needBots/* || (hasPlayers && BgCount > BracketSize && (BgCount % BracketSize) != 0)*/)
        return true;

    // do not join if BG queue is full
    if (BgCount >= BracketSize && (ACount >= TeamSize) && (HCount >= TeamSize))
    {
        return false;
    }

    if (!isArena && ((ACount >= TeamSize && TeamId == 0) || (HCount >= TeamSize && TeamId == 1)))
    {
        return false;
    }

    if (isArena && (((ACount >= TeamSize && HCount > 0) && TeamId == 0) || ((HCount >= TeamSize && ACount > 0) && TeamId == 1)))
    {
        return false;
    }

    if (isArena && (((ACount > TeamSize && HCount == 0) && TeamId == 1) || ((HCount > TeamSize && ACount == 0) && TeamId == 0)))
    {
        return false;
    }

    if (isArena && ((!isRated && SCount >= BracketSize) || (isRated && RCount >= BracketSize)))
    {
        return false;
    }

    return true;
}

bool BGLeaveAction::Execute(Event event)
{
    if (!bot->InBattlegroundQueue())
        return false;

    uint32 queueType = AI_VALUE(uint32, "bg type");
    if (!queueType)
        return false;

    //botAI->ChangeStrategy("-bg", BOT_STATE_NON_COMBAT);

    BattlegroundQueueTypeId queueTypeId = bot->GetBattlegroundQueueTypeId(0);
    BattlegroundTypeId _bgTypeId = sServerFacade->BgTemplateId(queueTypeId);
    uint8 type = false;
    uint16 unk = 0x1F90;
    uint8 unk2 = 0x0;
    bool isArena = false;
    bool IsRandomBot = sRandomPlayerbotMgr->IsRandomBot(bot->GetGUID().GetCounter());

    ArenaType arenaType = sServerFacade.BgArenaType(queueTypeId);
    if (arenaType)
    {
        isArena = true;
        type = arenaType;
    }

    LOG_INFO("playerbots", "Bot %s %s:%d <%s> leaves %s queue",
        bot->GetGUID().ToString().c_str(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName().c_str(), isArena ? "Arena" : "BG");

    WorldPacket packet(CMSG_BATTLEFIELD_PORT, 20);
    packet << type << unk2 << (uint32)_bgTypeId << unk << uint8(0);
    bot->GetSession()->HandleBattleFieldPortOpcode(packet);

    if (IsRandomBot)
        botAI->SetMaster(nullptr);

    botAI->ResetStrategies(!IsRandomBot);
    botAI->GetAiObjectContext()->GetValue<uint32>("bg type")->Set(nullptr);
    botAI->GetAiObjectContext()->GetValue<uint32>("bg role")->Set(nullptr);
    botAI->GetAiObjectContext()->GetValue<uint32>("arena type")->Set(nullptr);

    return true;
}

bool BGStatusAction::isUseful()
{
    return bot->InBattleGroundQueue();
}

bool BGStatusAction::Execute(Event event)
{
    uint32 QueueSlot;
    uint32 instanceId;
    uint32 mapId;
    uint32 statusid;
    uint32 Time1;
    uint32 Time2;
    uint8 unk1;
    std::string _bgType;

    uint64 arenatype;
    uint64 arenaByte;
    uint8 arenaTeam;
    uint8 isRated;
    uint64 unk0;
    uint64 x1f90;
    uint8 minlevel;
    uint8 maxlevel;
    uint64 bgTypeId;
    uint32 battleId;

    WorldPacket p(event.getPacket());
    statusid = 0;
    p >> QueueSlot; // queue id (0...2) - player can be in 3 queues in time
    p >> arenaByte;
    if (arenaByte == 0)
        return false;
    p >> minlevel;
    p >> maxlevel;
    p >> instanceId;
    p >> isRated;
    p >> statusid;

    // check status
    switch (statusid)
    {
        case STATUS_WAIT_QUEUE:             // status_in_queue
            p >> Time1;                     // average wait time, milliseconds
            p >> Time2;                     // time in queue, updated every minute!, milliseconds
            break;
        case STATUS_WAIT_JOIN:              // status_invite
            p >> mapId;                     // map id
            p >> unk0;
            p >> Time1;                     // time to remove from queue, milliseconds
            break;
        case STATUS_IN_PROGRESS:            // status_in_progress
            p >> mapId;                     // map id
            p >> unk0;
            p >> Time1;                     // time to bg auto leave, 0 at bg start, 120000 after bg end, milliseconds
            p >> Time2;                     // time from bg start, milliseconds
            p >> arenaTeam;
            break;
        default:
            LOG_ERROR("playerbots", "Unknown BG status!");
            break;
    }

    bool IsRandomBot = sRandomPlayerbotMgr->IsRandomBot(bot->GetGUID().GetCounter());
    BattlegroundQueueTypeId queueTypeId = bot->GetBattlegroundQueueTypeId(QueueSlot);
    BattlegroundTypeId _bgTypeId = sServerFacade->BgTemplateId(queueTypeId);
    BattleGroundBracketId bracketId;
    BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(_bgTypeId);
    uint32 mapId = bg->GetMapId();
    PvPDifficultyEntry const* pvpDiff = GetBattlegroundBracketByLevel(mapId, bot->getLevel());
    if (pvpDiff)
        bracketId = pvpDiff->GetBracketId();

    bool isArena = false;
    uint8 type = false;                                             // arenatype if arena
    uint16 unk = 0x1F90;
    uint8 unk2 = 0x0;
    uint8 action = 0x1;

    ArenaType arenaType = sServerFacade->BgArenaType(queueTypeId);
    if (arenaType)
    {
        isArena = true;
        type = arenaType;
    }

    switch (_bgTypeId)
    {
        case BATTLEGROUND_AV:
            _bgType = "AV";
            break;
        case BATTLEGROUND_WS:
            _bgType = "WSG";
            break;
        case BATTLEGROUND_AB:
            _bgType = "AB";
            break;
        case BATTLEGROUND_EY:
            _bgType = "EotS";
            break;
        default:
            break;
    }

    switch (arenaType)
    {
        case ARENA_TYPE_2v2:
            _bgType = "2v2";
            break;
        case ARENA_TYPE_3v3:
            _bgType = "3v3";
            break;
        case ARENA_TYPE_5v5:
            _bgType = "5v5";
            break;
        default:
            break;
    }

    if (Time1 == TIME_TO_AUTOREMOVE) //battleground is over, bot needs to leave
    {
        if (Battleground* bg = bot->GetBattleground())
        {
            uint32 TeamId = bot->GetTeamId();
            if (isArena)
            {
                sRandomPlayerbotMgr->ArenaBots[queueTypeId][bracketId][isRated][TeamId]--;
                TeamId = isRated ? 1 : 0;
            }

            sRandomPlayerbotMgr->BgBots[queueTypeId][bracketId][TeamId]--;
            sRandomPlayerbotMgr->BgPlayers[queueTypeId][bracketId][TeamId] = 0;
        }

        // remove warsong strategy
        if (IsRandomBot)
            botAI->SetMaster(nullptr);

        botAI->ChangeStrategy("-warsong", BOT_STATE_COMBAT);
        botAI->ChangeStrategy("-warsong", BOT_STATE_NON_COMBAT);
        botAI->ChangeStrategy("-arathi", BOT_STATE_COMBAT);
        botAI->ChangeStrategy("-arathi", BOT_STATE_NON_COMBAT);
        botAI->ChangeStrategy("-battleground", BOT_STATE_COMBAT);
        botAI->ChangeStrategy("-battleground", BOT_STATE_NON_COMBAT);
        botAI->ChangeStrategy("-arena", BOT_STATE_COMBAT);
        botAI->ChangeStrategy("-arena", BOT_STATE_NON_COMBAT);

        LOG_INFO("playerbots", "Bot %s <%s> leaves %s (%s).", bot->GetGUID().ToString().c_str(), bot->GetName().c_str(), isArena ? "Arena" : "BG", _bgType.c_str());

        WorldPacket packet(CMSG_LEAVE_BATTLEFIELD);
        packet << uint8(0);
        packet << uint8(0);                           // BattleGroundTypeId-1 ?
        packet << uint32(0);
        packet << uint16(0);

        bot->GetSession()->HandleBattlefieldLeaveOpcode(packet);

        botAI->ResetStrategies(!IsRandomBot);
        botAI->GetAiObjectContext()->GetValue<uint32>("bg type")->Set(nullptr);
        botAI->GetAiObjectContext()->GetValue<uint32>("bg role")->Set(nullptr);
        botAI->GetAiObjectContext()->GetValue<uint32>("arena type")->Set(nullptr);
        PositionMap& posMap = context->GetValue<PositionMap&>("position")->Get();
        PositionInfo pos = context->GetValue<PositionMap&>("position")->Get()["bg objective"];
        pos.Reset();
        posMap["bg objective"] = pos;
    }

    if (statusid == STATUS_WAIT_QUEUE) // bot is in queue
    {
        Battleground* bg = sBattleGroundMgr->GetBattleGroundTemplate(_bgTypeId);
        if (!bg)
            return false;

        bool leaveQ = false;
        uint32 timer;
        if (isArena)
            timer = TIME_TO_AUTOREMOVE;
        else
            timer = TIME_TO_AUTOREMOVE + 1000 * (bg->GetMaxPlayers() * 4);

        if (Time2 > timer && isArena) // disabled for BG
            leaveQ = true;

        if (leaveQ && ((bot->GetGroup() && bot->GetGroup()->IsLeader(bot->GetObjectGuid())) || !(bot->GetGroup() || botAI->GetMaster())))
        {
            uint32 TeamId = bot->GetTeamId();
            bool realPlayers = sRandomPlayerbotMgr->BgPlayers[queueTypeId][bracketId][TeamId];
            if (realPlayers)
                return false;

            LOG_INFO("playerbots", "Bot %s <%s> (%u %s) waited too long and leaves queue (%s %s).", bot->GetGUID().ToString().c_str(), bot->GetName().c_str(),
                bot->getLevel(), bot->GetTeamId() == TEAM_ALLIANCE ? "A" : "H", isArena ? "Arena" : "BG", _bgType.c_str());

            WorldPacket packet(CMSG_BATTLEFIELD_PORT, 20);
            action = 0;
            packet << type << unk2 << (uint32)_bgTypeId << unk << action;
            bot->GetSession()->HandleBattleFieldPortOpcode(packet);

            botAI->ResetStrategies(!IsRandomBot);
            botAI->GetAiObjectContext()->GetValue<uint32>("bg type")->Set(nullptr);
            botAI->GetAiObjectContext()->GetValue<uint32>("bg role")->Set(nullptr);
            botAI->GetAiObjectContext()->GetValue<uint32>("arena type")->Set(nullptr);
            sRandomPlayerbotMgr->BgBots[queueTypeId][bracketId][TeamId]--;

            return true;
        }
    }

    if (statusid == STATUS_WAIT_JOIN) //bot may join
    {
        if (isArena)
        {
            isArena = true;
            BattlegroundQueue& bgQueue = sServerFacade->bgQueue(queueTypeId);
            GroupQueueInfo ginfo;

            if (!bgQueue.GetPlayerGroupInfoData(bot->GetGUID(), &ginfo))
            {
                return false;
            }

            if (ginfo.IsInvitedToBGInstanceGUID)
            {
                Battleground* bg = sBattleGroundMgr->GetBattleGround(ginfo.IsInvitedToBGInstanceGUID, BATTLEGROUND_TYPE_NONE);
                if (!bg)
                {
                    return false;
                }

                _bgTypeId = bg->GetBgTypeID();
            }
        }

        LOG_INFO("playerbots", "Bot %s <%s> (%u %s) joined %s (%s)", bot->GetGUID().ToString().c_str(), bot->GetName().c_str(), bot->getLevel(),
            bot->GetTeamId() == TEAM_ALLIANCE ? "A" : "H", isArena ? "Arena" : "BG", _bgType.c_str());

        bot->Dismount();

        // bg started so players should get invites by now
        sRandomPlayerbotMgr.NeedBots[queueTypeId][bracketId][isArena ? isRated : GetTeamIndexByTeamId(bot->GetTeam())] = false;

        WorldPacket packet(CMSG_BATTLEFIELD_PORT, 20);
        packet << type << unk2 << (uint32)_bgTypeId << unk << action;
        bot->GetSession()->HandleBattleFieldPortOpcode(packet);

        botAI->ResetStrategies(false);
        //botAI->ChangeStrategy("-bg,-rpg,-travel,-grind", BOT_STATE_NON_COMBAT);
        context->GetValue<uint32>("bg role")->Set(urand(0, 9));
        PositionMap& posMap = context->GetValue<PositionMap&>("position")->Get();
        PositionInfo pos = context->GetValue<PositionMap&>("position")->Get()["bg objective"];
        pos.Reset();
        posMap["bg objective"] = pos;

        return true;
    }

    if (statusid == STATUS_IN_PROGRESS) // placeholder for Leave BG if it takes too long
    {
        return true;
    }

    return true;
}

bool BGStatusCheckAction::Execute(Event event)
{
    if (bot->IsBeingTeleported())
        return false;

    WorldPacket packet(CMSG_BATTLEFIELD_STATUS);
    bot->GetSession()->HandleBattlefieldStatusOpcode(packet);
    return true;
}

bool BGStatusCheckAction::isUseful()
{
    return bot->InBattleGroundQueue();
}
