/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RandomPlayerbotMgr.h"
#include "AccountMgr.h"
#include "AiFactory.h"
#include "FleeManager.h"
#include "GuildMgr.h"
#include "GuildTaskMgr.h"
#include "MapManager.h"
#include "PerformanceMonitor.h"
#include "Playerbot.h"
#include "PlayerbotCommandServer.h"
#include "PlayerbotFactory.h"

class PrintStatsThread: public ACE_Task <ACE_MT_SYNCH>
{
    public:
        int svc(void)
        {
            sRandomPlayerbotMgr->PrintStats();
            return 0;
        }
};

void activatePrintStatsThread()
{
    PrintStatsThread* thread = new PrintStatsThread();
    thread->activate();
}

RandomPlayerbotMgr::RandomPlayerbotMgr() : PlayerbotHolder(), processTicks(0)
{
    sPlayerbotCommandServer->Start();
    PrepareTeleportCache();
}

RandomPlayerbotMgr::~RandomPlayerbotMgr()
{
}

uint32 RandomPlayerbotMgr::GetMaxAllowedBotCount()
{
    return GetEventValue(0, "bot_count");
}

void RandomPlayerbotMgr::UpdateAIInternal(uint32 elapsed)
{
    if (!sPlayerbotAIConfig->randomBotAutologin || !sPlayerbotAIConfig->enabled)
        return;

    uint32 maxAllowedBotCount = GetEventValue(0, "bot_count");
    if (!maxAllowedBotCount)
    {
        maxAllowedBotCount = urand(sPlayerbotAIConfig->minRandomBots, sPlayerbotAIConfig->maxRandomBots);
        SetEventValue(0, "bot_count", maxAllowedBotCount, urand(sPlayerbotAIConfig->randomBotCountChangeMinInterval, sPlayerbotAIConfig->randomBotCountChangeMaxInterval));
    }

    SetNextCheckDelay(1000 * sPlayerbotAIConfig->randomBotUpdateInterval / (maxAllowedBotCount / sPlayerbotAIConfig->randomBotsPerInterval));

    std::vector<uint32> bots = GetBots();
    uint32 botCount = bots.size();

    PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_TOTAL, playerBots.size() < maxAllowedBotCount ? "RandomPlayerbotMgr::Login" : "RandomPlayerbotMgr::UpdateAIInternal");

    if (botCount < maxAllowedBotCount)
        AddRandomBots();

    uint32 botProcessed = 0;
    for (std::vector<uint32>::iterator i = bots.begin(); i != bots.end(); ++i)
    {
        uint32 bot = *i;
        if (ProcessBot(bot))
            botProcessed++;

        if (botProcessed >= sPlayerbotAIConfig->randomBotsPerInterval)
            break;
    }

    if (pmo)
        pmo->finish();
}

uint32 RandomPlayerbotMgr::AddRandomBots()
{
    std::set<uint32> bots;

    QueryResult results = CharacterDatabase.PQuery("SELECT `bot` FROM ai_playerbot_random_bots WHERE event = 'add'");
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 bot = fields[0].GetUInt32();
            bots.insert(bot);
        } while (results->NextRow());
    }

    std::vector<uint32> guids;
    uint32 maxAllowedBotCount = GetEventValue(0, "bot_count");
    for (std::vector<uint32>::iterator i = sPlayerbotAIConfig->randomBotAccounts.begin(); i != sPlayerbotAIConfig->randomBotAccounts.end(); i++)
    {
        uint32 accountId = *i;
        if (!AccountMgr::GetCharactersCount(accountId))
            continue;

        QueryResult result = CharacterDatabase.PQuery("SELECT guid, race FROM characters WHERE account = '%u'", accountId);
        if (!result)
            continue;

        do
        {
            Field* fields = result->Fetch();
            uint32 guid = fields[0].GetUInt32();
            uint8 race = fields[1].GetUInt8();
            bool alliance = guids.size() % 2 == 0;
            if (bots.find(guid) == bots.end() && ((alliance && IsAlliance(race)) || ((!alliance && !IsAlliance(race)))))
            {
                guids.push_back(guid);
                uint32 bot = guid;
                SetEventValue(bot, "add", 1, urand(sPlayerbotAIConfig->minRandomBotInWorldTime, sPlayerbotAIConfig->maxRandomBotInWorldTime));

                uint32 randomTime = 30 + urand(sPlayerbotAIConfig->randomBotUpdateInterval, sPlayerbotAIConfig->randomBotUpdateInterval * 3);
                ScheduleRandomize(bot, randomTime);

                bots.insert(bot);
                currentBots.push_back(bot);

                sLog->outString( "New random bot %d added", bot);

                if (bots.size() >= maxAllowedBotCount)
                {
                    return guids.size();
                }
            }
        } while (result->NextRow());
    }

    return guids.size();
}

void RandomPlayerbotMgr::ScheduleRandomize(uint32 bot, uint32 time)
{
    SetEventValue(bot, "randomize", 1, time);
    SetEventValue(bot, "logout", 1, time + 30 + urand(sPlayerbotAIConfig->randomBotUpdateInterval, sPlayerbotAIConfig->randomBotUpdateInterval * 3));
}

void RandomPlayerbotMgr::ScheduleTeleport(uint32 bot, uint32 time)
{
    if (!time)
        time = 60 + urand(sPlayerbotAIConfig->randomBotUpdateInterval, sPlayerbotAIConfig->randomBotUpdateInterval * 3);

    SetEventValue(bot, "teleport", 1, time);
}

void RandomPlayerbotMgr::ScheduleChangeStrategy(uint32 bot, uint32 time)
{
    if (!time)
        time = urand(sPlayerbotAIConfig->minRandomBotChangeStrategyTime, sPlayerbotAIConfig->maxRandomBotChangeStrategyTime);

    SetEventValue(bot, "change_strategy", 1, time);
}

bool RandomPlayerbotMgr::ProcessBot(uint32 bot)
{
    ObjectGuid botGUID = ObjectGuid::Create<HighGuid::Player>(bot);

    Player* player = GetPlayerBot(botGUID);
    PlayerbotAI* botAI = player ? player->GetPlayerbotAI() : nullptr;

    uint32 isValid = GetEventValue(bot, "add");
    if (!isValid)
    {
		if (!player || !player->GetGroup())
		{
			sLog->outString("Bot %d expired", bot);
			SetEventValue(bot, "add", 0, 0);
			currentBots.remove(bot);

			if (player)
                LogoutPlayerBot(botGUID);
		}

        return true;
    }

    uint32 isLogginIn = GetEventValue(bot, "login");
    if (isLogginIn)
        return false;

    if (!player)
    {
        AddPlayerBot(botGUID, 0);
        SetEventValue(bot, "login", 1, sPlayerbotAIConfig->randomBotUpdateInterval);

        uint32 randomTime = urand(sPlayerbotAIConfig->minRandomBotReviveTime, sPlayerbotAIConfig->maxRandomBotReviveTime);
        SetEventValue(bot, "update", 1, randomTime);

        return true;
    }

    SetEventValue(bot, "login", 0, 0);

    if (player->GetGroup() || player->HasUnitState(UNIT_STATE_IN_FLIGHT))
        return false;

    uint32 update = GetEventValue(bot, "update");
    if (!update)
    {
        if (botAI)
            botAI->GetAiObjectContext()->GetValue<bool>("random bot update")->Set(true);

        uint32 randomTime = urand(sPlayerbotAIConfig->minRandomBotReviveTime, sPlayerbotAIConfig->maxRandomBotReviveTime);
        SetEventValue(bot, "update", 1, randomTime);

        return true;
    }

    uint32 logout = GetEventValue(bot, "logout");
    if (!logout)
    {
        sLog->outString("Logging out bot %d", bot);
        LogoutPlayerBot(botGUID);
        SetEventValue(bot, "logout", 1, sPlayerbotAIConfig->maxRandomBotInWorldTime);
        return true;
    }

    return false;
}

bool RandomPlayerbotMgr::ProcessBot(Player* player)
{
    player->GetPlayerbotAI()->GetAiObjectContext()->GetValue<bool>("random bot update")->Set(false);

    uint32 bot = player->GetGUID().GetCounter();
    if (player->isDead())
    {
        if (!GetEventValue(bot, "dead"))
        {
            Revive(player);
            return true;
        }

        uint32 randomTime = urand(sPlayerbotAIConfig->minRandomBotReviveTime, sPlayerbotAIConfig->maxRandomBotReviveTime);
        SetEventValue(bot, "dead", 1, randomTime);

        return false;
    }

    if (player->GetGuildId())
    {
        if (Guild* guild = sGuildMgr->GetGuildById(player->GetGuildId()))
        {
            if (guild->GetLeaderGUID().GetRawValue() == player->GetGUID().GetRawValue())
            {
                for (std::vector<Player*>::iterator i = players.begin(); i != players.end(); ++i)
                    sGuildTaskMgr->Update(*i, player);
            }
        }
    }

    uint32 randomize = GetEventValue(bot, "randomize");
    if (!randomize)
    {
        sLog->outString("Randomizing bot %d", bot);
        Randomize(player);
        uint32 randomTime = urand(sPlayerbotAIConfig->minRandomBotRandomizeTime, sPlayerbotAIConfig->maxRandomBotRandomizeTime);
        ScheduleRandomize(bot, randomTime);
        return true;
    }

    uint32 teleport = GetEventValue(bot, "teleport");
    if (!teleport)
    {
        sLog->outDetail("Random teleporting bot %d", bot);
        RandomTeleportForLevel(player);
        SetEventValue(bot, "teleport", 1, sPlayerbotAIConfig->maxRandomBotInWorldTime);
        return true;
    }

    uint32 changeStrategy = GetEventValue(bot, "change_strategy");
    if (!changeStrategy)
    {
        sLog->outDetail("Changing strategy for bot %d", bot);
        ChangeStrategy(player);
        ScheduleChangeStrategy(bot);
        return true;
    }

    return false;
}

void RandomPlayerbotMgr::Revive(Player* player)
{
    uint32 bot = player->GetGUID().GetCounter();

    sLog->outDetail("Reviving dead bot %d", bot);
    SetEventValue(bot, "dead", 0, 0);
    SetEventValue(bot, "revive", 0, 0);

    if (player->getDeathState() == CORPSE)
        RandomTeleport(player);
    else
    {
        RandomTeleportForLevel(player);
        Refresh(player);
    }
}

void RandomPlayerbotMgr::RandomTeleport(Player* bot, std::vector<WorldLocation>& locs)
{
    if (bot->IsBeingTeleported())
        return;

    if (locs.empty())
    {
        sLog->outError("Cannot teleport bot %s - no locations available", bot->GetName());
        return;
    }

    PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_RNDBOT, "RandomTeleportByLocations");
    for (uint8 attemtps = 0; attemtps < 10; ++attemtps)
    {
        uint32 index = urand(0, locs.size() - 1);
        WorldLocation loc = locs[index];
        float x = loc.GetPositionX() + (attemtps > 0 ? urand(0, sPlayerbotAIConfig->grindDistance) - sPlayerbotAIConfig->grindDistance / 2 : 0);
        float y = loc.GetPositionY() + (attemtps > 0 ? urand(0, sPlayerbotAIConfig->grindDistance) - sPlayerbotAIConfig->grindDistance / 2 : 0);
        float z = loc.GetPositionZ();

        Map* map = sMapMgr->FindMap(loc.GetMapId(), 0);
        if (!map)
            continue;

		AreaTableEntry const* area = sAreaTableStore.LookupEntry(map->GetAreaId(x, y, z));
		if (!area)
			continue;

		if (map->IsUnderWater(x, y, z) || map->IsInWater(x, y, z))
			continue;

        float ground = map->GetHeight(x, y, z + 0.5f);
        if (ground <= INVALID_HEIGHT)
            continue;

        z = 0.05f + ground;

        sLog->outDetail("Random teleporting bot %s to %s %f,%f,%f (%u/%u locations)", bot->GetName(), area->area_name[0], x, y, z, attemtps, locs.size());

        bot->GetMotionMaster()->Clear();
        bot->TeleportTo(loc.GetMapId(), x, y, z, 0);
        bot->SendMovementFlagUpdate();

        if (pmo)
            pmo->finish();

        return;
    }

    if (pmo)
        pmo->finish();

    sLog->outError("Cannot teleport bot %s - no locations available", bot->GetName());
}

void RandomPlayerbotMgr::PrepareTeleportCache()
{
    uint32 maxLevel = sPlayerbotAIConfig->randomBotMaxLevel;
    if (maxLevel > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
        maxLevel = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);

    QueryResult results = CharacterDatabase.PQuery("SELECT map_id, x, y, z, level FROM ai_playerbot_tele_cache");
    if (results)
    {
        sLog->outBasic("Loading random teleport caches for %d levels...", maxLevel);

        do
        {
            Field* fields = results->Fetch();
            uint16 mapId = fields[0].GetUInt16();
            float x = fields[1].GetFloat();
            float y = fields[2].GetFloat();
            float z = fields[3].GetFloat();
            uint16 level = fields[4].GetUInt16();

            WorldLocation loc(mapId, x, y, z, 0);
            locsPerLevelCache[level].push_back(std::move(loc));
        } while (results->NextRow());
    }
    else
    {
        sLog->outBasic("Preparing random teleport caches for %d levels...", maxLevel);

        for (uint8 level = 1; level <= maxLevel; level++)
        {
            QueryResult results = WorldDatabase.PQuery("SELECT map, position_x, position_y, position_z "
                "FROM (SELECT map, position_x, position_y, position_z, AVG(t.maxlevel), AVG(t.minlevel), "
                "%u - (AVG(t.maxlevel) + aAVGvg(t.minlevel)) / 2 delta FROM creature c INNER JOIN creature_template t ON c.id = t.entry WHERE t.NpcFlags = 0 GROUP BY t.entry) q "
                "WHERE delta >= 0 AND delta <= %u AND map IN (%s) AND NOT EXISTS (SELECT map, position_x, position_y, position_z FROM "
                "(SELECT map, c.position_x, c.position_y, c.position_z, AVG(t.maxlevel), AVG(t.minlevel), %u - (AVG(t.maxlevel) + AVG(t.minlevel)) / 2 delta "
                "FROM creature c INNER JOIN creature_template t ON c.id = t.entry GROUP BY t.entry) q1 WHERE delta > %u and q1.map = q.map AND SQRT("
                "(q1.position_x - q.position_x) * (q1.position_x - q.position_x) + (q1.position_y - q.position_y) * (q1.position_y - q.position_y) + "
                "(q1.position_z - q.position_z) * (q1.position_z - q.position_z)) < %u)", level, sPlayerbotAIConfig->randomBotTeleLevel, sPlayerbotAIConfig->randomBotMapsAsString.c_str(),
                level, sPlayerbotAIConfig->randomBotTeleLevel, (uint32)sPlayerbotAIConfig->sightDistance);
            if (results)
            {
                do
                {
                    Field* fields = results->Fetch();
                    uint16 mapId = fields[0].GetUInt16();
                    float x = fields[1].GetFloat();
                    float y = fields[2].GetFloat();
                    float z = fields[3].GetFloat();
                    WorldLocation loc(mapId, x, y, z, 0);
                    locsPerLevelCache[level].push_back(std::move(loc));

                    CharacterDatabase.PExecute("INSERT INTO ai_playerbot_tele_cache (level, map_id, x, y, z) VALUES (%u, %u, %f, %f, %f)",
                            level, mapId, x, y, z);
                } while (results->NextRow());
            }
        }
    }

    results = WorldDatabase.PQuery("SELECT COUNT(*) FROM creature c INNER JOIN creature_template t ON c.id = t.entry WHERE t.NpcFlags & %u <> 0", UNIT_NPC_FLAG_INNKEEPER);
    uint32 rpgCacheSize = 0;
    if (results)
    {
        Field* fields = results->Fetch();
        rpgCacheSize = fields[0].GetUInt32();
    }

    sLog->outBasic("Preparing RPG teleport caches for %d factions...", sFactionTemplateStore.GetNumRows());

    results = WorldDatabase.PQuery("SELECT map, position_x, position_y, position_z, t.Faction, t.Name, r.race FROM creature c INNER JOIN creature_template t ON c.id = t.entry "
            "LEFT JOIN ai_playerbot_rpg_races r ON r.entry = t.entry WHERE t.NpcFlags & %u <> 0", UNIT_NPC_FLAG_INNKEEPER);
    if (results)
    {
        do
        {
            for (uint32 factionId = 0; factionId < sFactionTemplateStore.GetNumRows(); ++factionId)
            {
                FactionTemplateEntry const* botFaction = sFactionTemplateStore.LookupEntry(factionId);
                if (!botFaction)
                    continue;

                Field* fields = results->Fetch();
                uint16 mapId = fields[0].GetUInt16();
                float x = fields[1].GetFloat();
                float y = fields[2].GetFloat();
                float z = fields[3].GetFloat();
                uint32 faction = fields[4].GetUInt32();
                std::string name = fields[5].GetString();
                uint32 race = fields[6].GetUInt32();

                FactionTemplateEntry const* coFaction = sFactionTemplateStore.LookupEntry(faction);
                if (!botFaction->IsFriendlyTo(*coFaction))
                    continue;

                WorldLocation loc(mapId, x, y, z, 0);
                for (uint32 r = 1; r < MAX_RACES; r++)
                {
                    if (race == r || !race)
                        rpgLocsCache[r].push_back(std::move(loc));
                }
            }
        } while (results->NextRow());
    }
}

void RandomPlayerbotMgr::RandomTeleportForLevel(Player* bot)
{
    sLog->outDetail("Preparing location to random teleporting bot %s for level %u", bot->GetName(), bot->getLevel());
    RandomTeleport(bot, locsPerLevelCache[bot->getLevel()]);
}

void RandomPlayerbotMgr::RandomTeleport(Player* bot)
{
    PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_RNDBOT, "RandomTeleport");
    std::vector<WorldLocation> locs;

    std::vector<Unit*> targets;
    float range = sPlayerbotAIConfig->randomBotTeleportDistance;
    acore::AnyUnitInObjectRangeCheck u_check(bot, range);
    acore::UnitListSearcher<acore::AnyUnitInObjectRangeCheck> searcher(bot, targets, u_check);
    bot->VisitNearbyObject(range, u_check);

    for (Unit* unit : targets)
    {
        bot->UpdatePosition(*unit);

        FleeManager manager(bot, sPlayerbotAIConfig->sightDistance, 0, true);
        float rx, ry, rz;
        if (manager.CalculateDestination(&rx, &ry, &rz))
        {
            WorldLocation loc(bot->GetMapId(), rx, ry, rz);
            locs.push_back(std::move(loc));
        }
    }

    RandomTeleport(bot, locs);

    if (pmo)
        pmo->finish();

    Refresh(bot);
}

void RandomPlayerbotMgr::Randomize(Player* bot)
{
    if (bot->getLevel() == 1)
        RandomizeFirst(bot);
    else
        IncreaseLevel(bot);
}

void RandomPlayerbotMgr::IncreaseLevel(Player* bot)
{
	uint32 maxLevel = sPlayerbotAIConfig->randomBotMaxLevel;
	if (maxLevel > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
		maxLevel = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);

	PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_RNDBOT, "IncreaseLevel");
	uint32 lastLevel = GetValue(bot, "level");
	uint32 level = bot->getLevel();
	if (lastLevel != level)
	{
        PlayerbotFactory factory(bot, level);
        factory.Randomize(true);
	}

    RandomTeleportForLevel(bot);

    if (pmo)
        pmo->finish();
}

void RandomPlayerbotMgr::RandomizeFirst(Player* bot)
{
	uint32 maxLevel = sPlayerbotAIConfig->randomBotMaxLevel;
	if (maxLevel > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
		maxLevel = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);

	PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_RNDBOT, "RandomizeFirst");
    uint32 level = urand(sPlayerbotAIConfig->randomBotMinLevel, maxLevel);

    if (urand(0, 100) < 100 * sPlayerbotAIConfig->randomBotMaxLevelChance)
        level = maxLevel;

    SetValue(bot, "level", level);

    PlayerbotFactory factory(bot, level);
    factory.Randomize(false);

    RandomTeleportForLevel(bot);

    uint32 randomTime = urand(sPlayerbotAIConfig->minRandomBotRandomizeTime, sPlayerbotAIConfig->maxRandomBotRandomizeTime);
    CharacterDatabase.PExecute("UPDATE ai_playerbot_random_bots SET validIn = '%u' WHERE event = 'randomize' AND bot = '%u'", randomTime, bot->GetGUID().GetCounter());
    CharacterDatabase.PExecute("UPDATE ai_playerbot_random_bots SET validIn = '%u' WHERE event = 'logout' AND bot = '%u'", sPlayerbotAIConfig->maxRandomBotInWorldTime, bot->bot->GetGUID().GetCounter());

	if (pmo)
        pmo->finish();
}

uint32 RandomPlayerbotMgr::GetZoneLevel(uint16 mapId, float teleX, float teleY, float teleZ)
{
	uint32 maxLevel = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);

    uint32 level = 0;
    QueryResult results = WorldDatabase.PQuery("SELECT AVG(t.minlevel) minlevel, AVG(t.maxlevel) maxlevel FROM creature c "
            "INNER JOIN creature_template t ON c.id = t.entry WHERE map = '%u' AND minlevel > 1 AND ABS(position_x - '%f') < '%u' AND ABS(position_y - '%f') < '%u'",
            mapId, teleX, sPlayerbotAIConfig->randomBotTeleportDistance / 2, teleY, sPlayerbotAIConfig->randomBotTeleportDistance / 2);

    if (results)
    {
        Field* fields = results->Fetch();
        uint8 minLevel = fields[0].GetUInt8();
        uint8 maxLevel = fields[1].GetUInt8();
        level = urand(minLevel, maxLevel);
        if (level > maxLevel)
            level = maxLevel;
    }
    else
    {
        level = urand(1, maxLevel);
    }

    return level;
}

void RandomPlayerbotMgr::Refresh(Player* bot)
{
    sLog->outDetail("Refreshing bot %s", bot->GetName());

    PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_RNDBOT, "Refresh");

    if (bot->isDead())
    {
        bot->ResurrectPlayer(1.0f);
        bot->SpawnCorpseBones();
        bot->GetPlayerbotAI()->ResetStrategies(false);
    }

    bot->GetPlayerbotAI()->Reset();

    bot->DurabilityRepairAll(false, 1.0f);
	bot->SetFullHealth();
	bot->SetPvP(true);

    PlayerbotFactory factory(bot, bot->getLevel());
    factory.Refresh();

    if (bot->GetMaxPower(POWER_MANA) > 0)
        bot->SetPower(POWER_MANA, bot->GetMaxPower(POWER_MANA));

    if (bot->GetMaxPower(POWER_ENERGY) > 0)
        bot->SetPower(POWER_ENERGY, bot->GetMaxPower(POWER_ENERGY));

    if (pmo)
        pmo->finish();
}

bool RandomPlayerbotMgr::IsRandomBot(Player* bot)
{
	return IsRandomBot(bot->GetGUID().GetCounter());
}

bool RandomPlayerbotMgr::IsRandomBot(uint32 bot)
{
    return GetEventValue(bot, "add");
}

std::vector<uint32> RandomPlayerbotMgr::GetBots()
{
    if (!currentBots.empty())
        return currentBots;

    QueryResult results = CharacterDatabase.Query("SELECT bot FROM ai_playerbot_random_bots WHERE owner = 0 AND event = 'add'");
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 bot = fields[0].GetUInt32();
            currentBots.push_back(bot);
        } while (results->NextRow());
    }

    return currentBots;
}

uint32 RandomPlayerbotMgr::GetEventValue(uint32 bot, std::string const& event)
{
    CachedEvent& e = eventCache[bot][event];
    if (e.IsEmpty())
    {
        QueryResult results = CharacterDatabase.PQuery("SELECT `value`, `time`, validIn FROM ai_playerbot_random_bots WHERE owner = 0 AND bot = '%u' AND event = '%s'",
                bot, event.c_str());

        if (results)
        {
            Field* fields = results->Fetch();
            e.value = fields[0].GetUInt32();
            e.lastChangeTime = fields[1].GetUInt32();
            e.validIn = fields[2].GetUInt32();
        }
    }

    if ((time(0) - e.lastChangeTime) >= e.validIn)
        e.value = 0;

    return e.value;
}

uint32 RandomPlayerbotMgr::SetEventValue(uint32 bot, std::string const& event, uint32 value, uint32 validIn)
{
    CharacterDatabase.PExecute("DELETE FROM ai_playerbot_random_bots WHERE owner = 0 AND bot = '%u' AND event = '%s'", bot, event.c_str());
    if (value)
    {
        CharacterDatabase.PExecute("INSERT INTO ai_playerbot_random_bots (owner, bot, `time`, validIn, event, `value`) VALUES ('%u', '%u', '%u', '%u', '%s', '%u')",
                0, bot, (uint32)time(0), validIn, event.c_str(), value);
    }

    CachedEvent e(value, (uint32)time(0), validIn);
    eventCache[bot][event] = std::move(e);
    return value;
}

uint32 RandomPlayerbotMgr::GetValue(uint32 bot, std::string const& type)
{
    return GetEventValue(bot, type);
}

uint32 RandomPlayerbotMgr::GetValue(Player* bot, std::string const& type)
{
    return GetValue(bot->GetGUID().GetCounter(), type);
}

void RandomPlayerbotMgr::SetValue(uint32 bot, std::string const& type, uint32 value)
{
    SetEventValue(bot, type, value, sPlayerbotAIConfig->maxRandomBotInWorldTime);
}

void RandomPlayerbotMgr::SetValue(Player* bot, std::string const& type, uint32 value)
{
    SetValue(bot->GetGUID().GetCounter(), type, value);
}

bool RandomPlayerbotMgr::HandlePlayerbotConsoleCommand(ChatHandler* handler, char const* args)
{
    if (!sPlayerbotAIConfig->enabled)
    {
        sLog->outError("Playerbot system is currently disabled!");
        return false;
    }

    if (!args || !*args)
    {
        sLog->outError("Usage: rndbot stats/update/reset/init/refresh/add/remove");
        return false;
    }

    std::string const& cmd = args;

    if (cmd == "reset")
    {
        CharacterDatabase.PExecute("delete from ai_playerbot_random_bots");
        sRandomPlayerbotMgr->eventCache.clear();
        sLog->outString("Random bots were reset for all players. Please restart the Server.");
        return true;
    }

    if (cmd == "stats")
    {
        activatePrintStatsThread();
        return true;
    }

    if (cmd == "update")
    {
        sRandomPlayerbotMgr->UpdateAIInternal(0);
        return true;
    }

    std::map<std::string, ConsoleCommandHandler> handlers;
    handlers["init"] = &RandomPlayerbotMgr::RandomizeFirst;
    handlers["levelup"] = handlers["level"] = &RandomPlayerbotMgr::IncreaseLevel;
    handlers["refresh"] = &RandomPlayerbotMgr::Refresh;
    handlers["teleport"] = &RandomPlayerbotMgr::RandomTeleportForLevel;
    handlers["rpg"] = &RandomPlayerbotMgr::RandomTeleportForRpg;
    handlers["revive"] = &RandomPlayerbotMgr::Revive;
    handlers["grind"] = &RandomPlayerbotMgr::RandomTeleport;
    handlers["change_strategy"] = &RandomPlayerbotMgr::ChangeStrategy;

    for (std::map<std::string, ConsoleCommandHandler>::iterator j = handlers.begin(); j != handlers.end(); ++j)
    {
        std::string const& prefix = j->first;
        if (cmd.find(prefix) != 0)
            continue;

        std::string const& name = cmd.size() > prefix.size() + 1 ? cmd.substr(1 + prefix.size()) : "%";

        std::vector<uint32> botIds;
        for (std::vector<uint32>::iterator i = sPlayerbotAIConfig->randomBotAccounts.begin(); i != sPlayerbotAIConfig->randomBotAccounts.end(); ++i)
        {
            uint32 account = *i;
            if (QueryResult results = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE account = '%u' AND name like '%s'", account, name))
            {
                do
                {
                    Field* fields = results->Fetch();

                    uint32 botId = fields[0].GetUInt32();
                    ObjectGuid guid = ObjectGuid::Create<HighGuid::Player>(botId);
                    Player* bot = ObjectAccessor::FindPlayer(guid);
                    if (!bot)
                        continue;

                    botIds.push_back(botId);
                } while (results->NextRow());
			}
        }

        if (botIds.empty())
        {
            sLog->outString("Nothing to do");
            return false;
        }

        uint32 processed = 0;
        for (std::vector<uint32>::iterator i = botIds.begin(); i != botIds.end(); ++i)
        {
            ObjectGuid guid = ObjectGuid::Create<HighGuid::Player>(*i);
            Player* bot = ObjectAccessor::FindPlayer(guid);
            if (!bot)
                continue;

            sLog->outString("[%u/%u] Processing command '%s' for bot '%s'", processed++, botIds.size(), cmd.c_str(), bot->GetName());

            ConsoleCommandHandler handler = j->second;
            (sRandomPlayerbotMgr->*handler)(bot);
        }

        return true;
    }

    std::vector<string> messages = sRandomPlayerbotMgr->HandlePlayerbotCommand(args, nullptr);
    for (std::vector<string>::iterator i = messages.begin(); i != messages.end(); ++i)
    {
        sLog->outString(i->c_str());
    }
    return true;
}

void RandomPlayerbotMgr::HandleCommand(uint32 type, std::string const& text, Player* fromPlayer)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->GetPlayerbotAI()->HandleCommand(type, text, fromPlayer);
    }
}

void RandomPlayerbotMgr::OnPlayerLogout(Player* player)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        PlayerbotAI* botAI = bot->GetPlayerbotAI();
        if (player == botAI->GetMaster())
        {
            botAI->SetMaster(nullptr);
            botAI->ResetStrategies();
        }
    }

    std::vector<Player*>::iterator i = std::find(players.begin(), players.end(), player);
    if (i != players.end())
        players.erase(i);
}

void RandomPlayerbotMgr::OnBotLoginInternal(Player * const bot)
{
    sLog->outDetail("%d/%d Bot %s logged in", playerBots.size(), sRandomPlayerbotMgr->GetMaxAllowedBotCount(), bot->GetName());
}

void RandomPlayerbotMgr::OnPlayerLogin(Player* player)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        if (player == bot || player->GetPlayerbotAI())
            continue;

        Group* group = bot->GetGroup();
        if (!group)
            continue;

        for (GroupReference* gref = group->GetFirstMember(); gref; gref = gref->next())
        {
            Player* member = gref->GetSource();
            PlayerbotAI* botAI = bot->GetPlayerbotAI();
            if (member == player && (!botAI->GetMaster() || botAI->GetMaster()->GetPlayerbotAI()))
            {
                botAI->SetMaster(player);
                botAI->ResetStrategies();
                botAI->TellMaster("Hello");
                break;
            }
        }
    }

    if (IsRandomBot(player))
    {
        ObjectGuid::LowType guid = player->GetGUID().GetCounter();
        SetEventValue(guid, "login", 0, 0);
    }
    else
    {
        players.push_back(player);
        sLog->outDebug("Including non-random bot player %s into random bot update", player->GetName());
    }
}

void RandomPlayerbotMgr::OnPlayerLoginError(uint32 bot)
{
    SetEventValue(bot, "add", 0, 0);
    currentBots.remove(bot);
}

Player* RandomPlayerbotMgr::GetRandomPlayer()
{
    if (players.empty())
        return nullptr;

    uint32 index = urand(0, players.size() - 1);
    return players[index];
}

void RandomPlayerbotMgr::PrintStats()
{
    sLog->outString("%d Random Bots online", playerBots.size());

    std::map<uint8, uint32> alliance, horde;
    for (uint32 i = 0; i < 10; ++i)
    {
        alliance[i] = 0;
        horde[i] = 0;
    }

    std::map<uint8, uint32> perRace;
    std::map<uint8, uint32> perClass;
    for (uint8 race = RACE_HUMAN; race < MAX_RACES; ++race)
    {
        perRace[race] = 0;
    }

    for (uint8 cls = CLASS_WARRIOR; cls < MAX_CLASSES; ++cls)
    {
        perClass[cls] = 0;
    }

    uint32 dps = 0;
    uint32 heal = 0;
    uint32 tank = 0;
    uint32 active = 0;
    uint32 update = 0;
    uint32 randomize = 0;
    uint32 teleport = 0;
    uint32 changeStrategy = 0;
    uint32 dead = 0;
    uint32 revive = 0;
    for (PlayerBotMap::iterator i = playerBots.begin(); i != playerBots.end(); ++i)
    {
        Player* bot = i->second;
        if (IsAlliance(bot->getRace()))
            alliance[bot->getLevel() / 10]++;
        else
            horde[bot->getLevel() / 10]++;

        perRace[bot->getRace()]++;
        perClass[bot->getClass()]++;

        if (bot->GetPlayerbotAI()->IsActive())
            active++;

        if (bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<bool>("random bot update")->Get())
            update++;

        uint32 botId = (uint32)bot->GetGUID().GetRawValue();
        if (!GetEventValue(botId, "randomize"))
            randomize++;

        if (!GetEventValue(botId, "teleport"))
            teleport++;

        if (!GetEventValue(botId, "change_strategy"))
            changeStrategy++;

        if (bot->isDead())
        {
            dead++;
            if (!GetEventValue(botId, "dead"))
                revive++;
        }

        uint32 spec = AiFactory::GetPlayerSpecTab(bot);
        switch (bot->getClass())
        {
            case CLASS_DRUID:
                if (spec == 2)
                    heal++;
                else
                    dps++;
                break;
            case CLASS_PALADIN:
                if (spec == 1)
                    tank++;
                else if (spec == 0)
                    heal++;
                else
                    dps++;
                break;
            case CLASS_PRIEST:
                if (spec != 2)
                    heal++;
                else
                    dps++;
                break;
            case CLASS_SHAMAN:
                if (spec == 2)
                    heal++;
                else
                    dps++;
                break;
            case CLASS_WARRIOR:
                if (spec == 2)
                    tank++;
                else
                    dps++;
                break;
            default:
                dps++;
                break;
        }
    }

    sLog->outString("Per level:");
	uint32 maxLevel = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	for (uint8 i = 0; i < 10; ++i)
    {
        if (!alliance[i] && !horde[i])
            continue;

        uint32 from = i*10;
        uint32 to = min(from + 9, maxLevel);
        if (!from)
            from = 1;

        sLog->outString("    %d..%d: %d alliance, %d horde", from, to, alliance[i], horde[i]);
    }

    sLog->outString("Per race:");
    for (uint8 race = RACE_HUMAN; race < MAX_RACES; ++race)
    {
        if (perRace[race])
            sLog->outString("    %s: %d", ChatHelper::formatRace(race).c_str(), perRace[race]);
    }

    sLog->outString("Per class:");
    for (uint8 cls = CLASS_WARRIOR; cls < MAX_CLASSES; ++cls)
    {
        if (perClass[cls])
            sLog->outString("    %s: %d", ChatHelper::formatClass(cls).c_str(), perClass[cls]);
    }

    sLog->outString("Per role:");
    sLog->outString("    tank: %d", tank);
    sLog->outString("    heal: %d", heal);
    sLog->outString("    dps: %d", dps);

    sLog->outString("Active bots: %d", active);
    sLog->outString("Dead bots: %d", dead);
    sLog->outString("Bots to:");
    sLog->outString("    update: %d", update);
    sLog->outString("    randomize: %d", randomize);
    sLog->outString("    teleport: %d", teleport);
    sLog->outString("    change_strategy: %d", changeStrategy);
    sLog->outString("    revive: %d", revive);
}

double RandomPlayerbotMgr::GetBuyMultiplier(Player* bot)
{
    uint32 id = bot->GetGUID().GetCounter();
    uint32 value = GetEventValue(id, "buymultiplier");
    if (!value)
    {
        value = urand(50, 120);
        uint32 validIn = urand(sPlayerbotAIConfig->minRandomBotsPriceChangeInterval, sPlayerbotAIConfig->maxRandomBotsPriceChangeInterval);
        SetEventValue(id, "buymultiplier", value, validIn);
    }

    return (double)value / 100.0;
}

double RandomPlayerbotMgr::GetSellMultiplier(Player* bot)
{
    uint32 id = bot->GetGUID().GetCounter();
    uint32 value = GetEventValue(id, "sellmultiplier");
    if (!value)
    {
        value = urand(80, 250);
        uint32 validIn = urand(sPlayerbotAIConfig->minRandomBotsPriceChangeInterval, sPlayerbotAIConfig->maxRandomBotsPriceChangeInterval);
        SetEventValue(id, "sellmultiplier", value, validIn);
    }

    return (double)value / 100.0;
}

void RandomPlayerbotMgr::AddTradeDiscount(Player* bot, Player* master, int32 value)
{
    if (!master)
        return;

    uint32 discount = GetTradeDiscount(bot, master);
    int32 result = (int32)discount + value;
    discount = (result < 0 ? 0 : result);

    SetTradeDiscount(bot, master, discount);
}

void RandomPlayerbotMgr::SetTradeDiscount(Player* bot, Player* master, uint32 value)
{
    if (!master)
        return;

    uint32 botId =  bot->GetGUID().GetCounter();
    uint32 masterId =  master->GetGUID().GetCounter();

    std::ostringstream name;
    name << "trade_discount_" << masterId;
    SetEventValue(botId, name.str(), value, sPlayerbotAIConfig->maxRandomBotInWorldTime);
}

uint32 RandomPlayerbotMgr::GetTradeDiscount(Player* bot, Player* master)
{
    if (!master)
        return 0;

    uint32 botId =  bot->GetGUID().GetCounter();
    uint32 masterId = master->GetGUID().GetCounter();

    std::ostringstream name;
    name << "trade_discount_" << masterId;
    return GetEventValue(botId, name.str());
}

std::string RandomPlayerbotMgr::HandleRemoteCommand(std::string const& request)
{
    std::string::iterator pos = find(request.begin(), request.end(), ',');
    if (pos == request.end())
    {
        std::ostringstream out;
        out << "invalid request: " << request;
        return out.str();
    }

    std::string command = std::string(request.begin(), pos);
    ObjectGuid guid = ObjectGuid::Create<HighGuid::Player>(atoi(std::string(pos + 1, request.end()).c_str()));
    Player* bot = GetPlayerBot(guid);
    if (!bot)
        return "invalid guid";

    PlayerbotAI* botAI = bot->GetPlayerbotAI();
    if (!botAI)
        return "invalid guid";

    return botAI->HandleRemoteCommand(command);
}

void RandomPlayerbotMgr::ChangeStrategy(Player* player)
{
    uint32 bot = player->GetGUID().GetCounter();

    if (frand(0.f, 100.f) > sPlayerbotAIConfig->randomBotRpgChance)
    {
        sLog->outDetail("Changing strategy for bot %s to grinding", player->GetName());
        ScheduleTeleport(bot, 30);
    }
    else
    {
        sLog->outDetail("Changing strategy for bot %s to RPG", player->GetName());
        RandomTeleportForRpg(player);
    }

    ScheduleChangeStrategy(bot);
}

void RandomPlayerbotMgr::RandomTeleportForRpg(Player* bot)
{
    uint32 race = bot->getRace();
    sLog->outDetail("Random teleporting bot %s for RPG (%d locations available)", bot->GetName(), rpgLocsCache[race].size());
    RandomTeleport(bot, rpgLocsCache[race]);
}

void RandomPlayerbotMgr::Remove(Player* bot)
{
    ObjectGuid owner = bot->GetGUID();
    CharacterDatabase.PExecute("delete from ai_playerbot_random_bots where owner = 0 and bot = '%u'", owner.GetCounter());
    eventCache[owner.GetCounter()].clear();

    LogoutPlayerBot(owner);
}
