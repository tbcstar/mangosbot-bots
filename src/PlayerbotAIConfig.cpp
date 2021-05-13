/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PlayerbotAIConfig.h"
#include "Config.h"
#include "Playerbot.h"
#include "PlayerbotFactory.h"
#include "RandomItemMgr.h"
#include "RandomPlayerbotFactory.h"

/*

#include "AccountMgr.h"


*/

template <class T>
void LoadList(std::string const& value, T& list)
{
    std::vector<std::string> ids = split(value, ',');
    for (std::vector<std::string>::iterator i = ids.begin(); i != ids.end(); i++)
    {
        uint32 id = atoi((*i).c_str());
        if (!id)
            continue;

        list.push_back(id);
    }
}

bool PlayerbotAIConfig::Initialize()
{
    sLog->outString("Initializing AI Playerbot by ike3, based on the original Playerbot by blueboy");

    if (!sConfigMgr->SetSource(SYSCONFDIR"aiplayerbot.conf"))
    {
        sLog->outString("AI Playerbot is Disabled. Unable to open configuration file aiplayerbot.conf");
        return false;
    }

    enabled = sConfigMgr->GetBoolDefault("AiPlayerbot.Enabled", true);
    if (!enabled)
    {
        sLog->outString("AI Playerbot is Disabled in aiplayerbot.conf");
        return false;
    }

    globalCoolDown = sConfigMgr->GetIntDefault("AiPlayerbot.GlobalCooldown", 500);
    maxWaitForMove = sConfigMgr->GetIntDefault("AiPlayerbot.MaxWaitForMove", 3000);
    expireActionTime = sConfigMgr->GetIntDefault("AiPlayerbot.ExpireActionTime", 5000);
    dispelAuraDuration = sConfigMgr->GetIntDefault("AiPlayerbot.DispelAuraDuration", 7000);
    reactDelay = sConfigMgr->GetIntDefault("AiPlayerbot.ReactDelay", 100);
    passiveDelay = sConfigMgr->GetIntDefault("AiPlayerbot.PassiveDelay", 4000);
    repeatDelay = sConfigMgr->GetIntDefault("AiPlayerbot.RepeatDelay", 5000);
    errorDelay = sConfigMgr->GetIntDefault("AiPlayerbot.ErrorDelay", 5000);
    rpgDelay = sConfigMgr->GetIntDefault("AiPlayerbot.RpgDelay", 3000);
    sitDelay = sConfigMgr->GetIntDefault("AiPlayerbot.SitDelay", 30000);
    returnDelay = sConfigMgr->GetIntDefault("AiPlayerbot.ReturnDelay", 7000);
    lootDelay = sConfigMgr->GetIntDefault("AiPlayerbot.LootDelayDelay", 750);

    farDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.FarDistance", 20.0f);
    sightDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.SightDistance", 75.0f);
    spellDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.SpellDistance", 22.0f);
    shootDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.ShootDistance", 25.0f);
    healDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.HealDistance", 20.0f);
    lootDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.LootDistance", 15.0f);
    fleeDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.FleeDistance", 7.5f);
    aggroDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.AggroDistance", 22.0f);
    tooCloseDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.TooCloseDistance", 5.0f);
    meleeDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.MeleeDistance", 1.5f);
    followDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.FollowDistance", 1.5f);
    whisperDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.WhisperDistance", 6000.0f);
    contactDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.ContactDistance", 0.5f);
    aoeRadius = sConfigMgr->GetFloatDefault("AiPlayerbot.AoeRadius", 5.0f);
    rpgDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.RpgDistance", 80.0f);
    grindDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.GrindDistance", 75.0f);
    reactDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.ReactDistance", 150.0f);

    criticalHealth = sConfigMgr->GetIntDefault("AiPlayerbot.CriticalHealth", 20);
    lowHealth = sConfigMgr->GetIntDefault("AiPlayerbot.LowHealth", 50);
    mediumHealth = sConfigMgr->GetIntDefault("AiPlayerbot.MediumHealth", 70);
    almostFullHealth = sConfigMgr->GetIntDefault("AiPlayerbot.AlmostFullHealth", 85);
    lowMana = sConfigMgr->GetIntDefault("AiPlayerbot.LowMana", 15);
    mediumMana = sConfigMgr->GetIntDefault("AiPlayerbot.MediumMana", 40);

    randomGearLoweringChance = sConfigMgr->GetFloatDefault("AiPlayerbot.RandomGearLoweringChance", 0.15);
    randomBotMaxLevelChance = sConfigMgr->GetFloatDefault("AiPlayerbot.RandomBotMaxLevelChance", 0.15);
    randomBotRpgChance = sConfigMgr->GetFloatDefault("AiPlayerbot.RandomBotRpgChance", 0.35);

    iterationsPerTick = sConfigMgr->GetIntDefault("AiPlayerbot.IterationsPerTick", 100);

    allowGuildBots = sConfigMgr->GetBoolDefault("AiPlayerbot.AllowGuildBots", true);

    randomBotMapsAsString = sConfigMgr->GetStringDefault("AiPlayerbot.RandomBotMaps", "0,1,530,571");
    LoadList<std::vector<uint32> >(randomBotMapsAsString, randomBotMaps);
    LoadList<std::vector<uint32> >(sConfigMgr->GetStringDefault("AiPlayerbot.RandomBotQuestItems", "6948,5175,5176,5177,5178"), randomBotQuestItems);
    LoadList<std::vector<uint32>>(sConfigMgr->GetStringDefault("AiPlayerbot.RandomBotSpellIds", "54197"), randomBotSpellIds);
    LoadList<std::vector<uint32>>(sConfigMgr->GetStringDefault("AiPlayerbot.PvpProhibitedZoneIds", "2255,656,2361,2362,2363,976,35,2268"), pvpProhibitedZoneIds);
    LoadList<std::vector<uint32>>(sConfigMgr->GetStringDefault("AiPlayerbot.RandomBotQuestIds", "7848"), randomBotQuestIds);

    botAutologin = sConfigMgr->GetBoolDefault("AiPlayerbot.BotAutologin", false);
    randomBotAutologin = sConfigMgr->GetBoolDefault("AiPlayerbot.RandomBotAutologin", true);
    minRandomBots = sConfigMgr->GetIntDefault("AiPlayerbot.MinRandomBots", 50);
    maxRandomBots = sConfigMgr->GetIntDefault("AiPlayerbot.MaxRandomBots", 200);
    randomBotUpdateInterval = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotUpdateInterval", 60);
    randomBotCountChangeMinInterval = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotCountChangeMinInterval", 24 * 3600);
    randomBotCountChangeMaxInterval = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotCountChangeMaxInterval", 3 * 24 * 3600);
    minRandomBotInWorldTime = sConfigMgr->GetIntDefault("AiPlayerbot.MinRandomBotInWorldTime", 24 * 3600);
    maxRandomBotInWorldTime = sConfigMgr->GetIntDefault("AiPlayerbot.MaxRandomBotInWorldTime", 14 * 24 * 3600);
    minRandomBotRandomizeTime = sConfigMgr->GetIntDefault("AiPlayerbot.MinRandomBotRandomizeTime", 2 * 3600);
    maxRandomBotRandomizeTime = sConfigMgr->GetIntDefault("AiPlayerbot.MaxRandomRandomizeTime", 14 * 24 * 3600);
    minRandomBotChangeStrategyTime = sConfigMgr->GetIntDefault("AiPlayerbot.MinRandomBotChangeStrategyTime", 1800);
    maxRandomBotChangeStrategyTime = sConfigMgr->GetIntDefault("AiPlayerbot.MaxRandomBotChangeStrategyTime", 2 * 3600);
    minRandomBotReviveTime = sConfigMgr->GetIntDefault("AiPlayerbot.MinRandomBotReviveTime", 60);
    maxRandomBotReviveTime = sConfigMgr->GetIntDefault("AiPlayerbot.MaxRandomReviveTime", 300);
    randomBotTeleportDistance = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotTeleportDistance", 100);
    randomBotsPerInterval = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotsPerInterval", 50);
    minRandomBotsPriceChangeInterval = sConfigMgr->GetIntDefault("AiPlayerbot.MinRandomBotsPriceChangeInterval", 2 * 3600);
    maxRandomBotsPriceChangeInterval = sConfigMgr->GetIntDefault("AiPlayerbot.MaxRandomBotsPriceChangeInterval", 48 * 3600);
    randomBotJoinLfg = sConfigMgr->GetBoolDefault("AiPlayerbot.RandomBotJoinLfg", true);
    logInGroupOnly = sConfigMgr->GetBoolDefault("AiPlayerbot.LogInGroupOnly", true);
    logValuesPerTick = sConfigMgr->GetBoolDefault("AiPlayerbot.LogValuesPerTick", false);
    fleeingEnabled = sConfigMgr->GetBoolDefault("AiPlayerbot.FleeingEnabled", true);
    summonAtInnkeepersEnabled = sConfigMgr->GetBoolDefault("AiPlayerbot.SummonAtInnkeepersEnabled", true);
    randomBotMinLevel = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotMinLevel", 1);
    randomBotMaxLevel = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotMaxLevel", 255);
    randomBotLoginAtStartup = sConfigMgr->GetBoolDefault("AiPlayerbot.RandomBotLoginAtStartup", true);
    randomBotTeleLevel = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotTeleLevel", 5);
    openGoSpell = sConfigMgr->GetIntDefault("AiPlayerbot.OpenGoSpell", 6477);

    randomChangeMultiplier = sConfigMgr->GetFloatDefault("AiPlayerbot.RandomChangeMultiplier", 1.0);

    randomBotCombatStrategies = sConfigMgr->GetStringDefault("AiPlayerbot.RandomBotCombatStrategies", "+dps,+dps assist,-threat");
    randomBotNonCombatStrategies = sConfigMgr->GetStringDefault("AiPlayerbot.RandomBotNonCombatStrategies", "+grind,+loot,+rpg,+custom::say");
    combatStrategies = sConfigMgr->GetStringDefault("AiPlayerbot.CombatStrategies", "+custom::say");
    nonCombatStrategies = sConfigMgr->GetStringDefault("AiPlayerbot.NonCombatStrategies", "+custom::say,+return");

    commandPrefix = sConfigMgr->GetStringDefault("AiPlayerbot.CommandPrefix", "");
    commandSeparator = sConfigMgr->GetStringDefault("AiPlayerbot.CommandSeparator", "\\\\");

    commandServerPort = sConfigMgr->GetIntDefault("AiPlayerbot.CommandServerPort", 0);
    perfMonEnabled = sConfigMgr->GetBoolDefault("AiPlayerbot.PerfMonEnabled", false);

    for (uint32 cls = 0; cls < MAX_CLASSES; ++cls)
    {
        for (uint32 spec = 0; spec < 3; ++spec)
        {
            std::ostringstream os;
            os << "AiPlayerbot.RandomClassSpecProbability." << cls << "." << spec;
            specProbability[cls][spec] = sConfigMgr->GetIntDefault(os.str().c_str(), 33);
        }
    }

    randomBotAccountPrefix = sConfigMgr->GetStringDefault("AiPlayerbot.RandomBotAccountPrefix", "rndbot");
    randomBotAccountCount = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotAccountCount", 50);
    deleteRandomBotAccounts = sConfigMgr->GetBoolDefault("AiPlayerbot.DeleteRandomBotAccounts", false);
    randomBotGuildCount = sConfigMgr->GetIntDefault("AiPlayerbot.RandomBotGuildCount", 50);
    deleteRandomBotGuilds = sConfigMgr->GetBoolDefault("AiPlayerbot.DeleteRandomBotGuilds", false);

    guildTaskEnabled = sConfigMgr->GetBoolDefault("AiPlayerbot.EnableGuildTasks", true);
    minGuildTaskChangeTime = sConfigMgr->GetIntDefault("AiPlayerbot.MinGuildTaskChangeTime", 3 * 24 * 3600);
    maxGuildTaskChangeTime = sConfigMgr->GetIntDefault("AiPlayerbot.MaxGuildTaskChangeTime", 4 * 24 * 3600);
    minGuildTaskAdvertisementTime = sConfigMgr->GetIntDefault("AiPlayerbot.MinGuildTaskAdvertisementTime", 60);
    maxGuildTaskAdvertisementTime = sConfigMgr->GetIntDefault("AiPlayerbot.MaxGuildTaskAdvertisementTime", 12 * 3600);
    minGuildTaskRewardTime = sConfigMgr->GetIntDefault("AiPlayerbot.MinGuildTaskRewardTime", 30);
    maxGuildTaskRewardTime = sConfigMgr->GetIntDefault("AiPlayerbot.MaxGuildTaskRewardTime", 120);
    guildTaskAdvertCleanupTime = sConfigMgr->GetIntDefault("AiPlayerbot.GuildTaskAdvertCleanupTime", 300);
    guildTaskKillTaskDistance = sConfigMgr->GetIntDefault("AiPlayerbot.GuildTaskKillTaskDistance", 2000);

    targetPosRecalcDistance = sConfigMgr->GetFloatDefault("AiPlayerbot.TargetPosRecalcDistance", 0.1f);

    RandomPlayerbotFactory::CreateRandomBots();
    PlayerbotFactory::Init();
    sRandomItemMgr->Init();
    sRandomItemMgr->InitAfterAhBot();

    sLog->outString("---------------------------------------");
    sLog->outString("        AI Playerbot initialized       ");
    sLog->outString("---------------------------------------");
    sLog->outString();

    return true;
}

bool PlayerbotAIConfig::IsInRandomAccountList(uint32 id)
{
    return find(randomBotAccounts.begin(), randomBotAccounts.end(), id) != randomBotAccounts.end();
}

bool PlayerbotAIConfig::IsInRandomQuestItemList(uint32 id)
{
    return find(randomBotQuestItems.begin(), randomBotQuestItems.end(), id) != randomBotQuestItems.end();
}

bool PlayerbotAIConfig::IsInPvpProhibitedZone(uint32 id)
{
    return find(pvpProhibitedZoneIds.begin(), pvpProhibitedZoneIds.end(), id) != pvpProhibitedZoneIds.end();
}
