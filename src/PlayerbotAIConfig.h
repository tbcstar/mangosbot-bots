/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Common.h"

class PlayerbotAIConfig
{
    public:
        PlayerbotAIConfig() { };
        static PlayerbotAIConfig* instance()
        {
            static PlayerbotAIConfig instance;
            return &instance;
        }

        bool Initialize();
        bool IsInRandomAccountList(uint32 id);
        bool IsInRandomQuestItemList(uint32 id);
        bool IsInPvpProhibitedZone(uint32 id);

        bool enabled;
        bool allowGuildBots;
        uint32 globalCoolDown, reactDelay, maxWaitForMove, expireActionTime, dispelAuraDuration, passiveDelay, repeatDelay,
            errorDelay, rpgDelay, sitDelay, returnDelay, lootDelay;
        float sightDistance, spellDistance, reactDistance, grindDistance, lootDistance, shootDistance,
            fleeDistance, tooCloseDistance, meleeDistance, followDistance, whisperDistance, contactDistance,
            aoeRadius, rpgDistance, targetPosRecalcDistance, farDistance, healDistance, aggroDistance;
        uint32 criticalHealth, lowHealth, mediumHealth, almostFullHealth;
        uint32 lowMana, mediumMana;

        uint32 openGoSpell;
        bool randomBotAutologin;
        bool botAutologin;
        std::string randomBotMapsAsString;
        std::vector<uint32> randomBotMaps;
        std::vector<uint32> randomBotQuestItems;
        std::vector<uint32> randomBotAccounts;
        std::vector<uint32> randomBotSpellIds;
        std::vector<uint32> randomBotQuestIds;
        uint32 randomBotTeleportDistance;
        float randomGearLoweringChance;
        float randomBotMaxLevelChance;
        float randomBotRpgChance;
        uint32 minRandomBots, maxRandomBots;
        uint32 randomBotUpdateInterval, randomBotCountChangeMinInterval, randomBotCountChangeMaxInterval;
        uint32 minRandomBotInWorldTime, maxRandomBotInWorldTime;
        uint32 minRandomBotRandomizeTime, maxRandomBotRandomizeTime;
        uint32 minRandomBotChangeStrategyTime, maxRandomBotChangeStrategyTime;
        uint32 minRandomBotReviveTime, maxRandomBotReviveTime;
        uint32 minRandomBotPvpTime, maxRandomBotPvpTime;
        uint32 randomBotsPerInterval;
        uint32 minRandomBotsPriceChangeInterval, maxRandomBotsPriceChangeInterval;
        bool randomBotJoinLfg;
        bool randomBotLoginAtStartup;
        uint32 randomBotTeleLevel;
        bool logInGroupOnly, logValuesPerTick;
        bool fleeingEnabled;
        bool summonAtInnkeepersEnabled;
        std::string combatStrategies, nonCombatStrategies;
        std::string randomBotCombatStrategies, randomBotNonCombatStrategies;
        uint32 randomBotMinLevel, randomBotMaxLevel;
        float randomChangeMultiplier;
        uint32 specProbability[MAX_CLASSES][3];
        std::string commandPrefix, commandSeparator;
        std::string randomBotAccountPrefix;
        uint32 randomBotAccountCount;
        bool deleteRandomBotAccounts;
        uint32 randomBotGuildCount;
        bool deleteRandomBotGuilds;
        std::vector<uint32> randomBotGuilds;
        std::vector<uint32> pvpProhibitedZoneIds;

        bool guildTaskEnabled;
        uint32 minGuildTaskChangeTime, maxGuildTaskChangeTime;
        uint32 minGuildTaskAdvertisementTime, maxGuildTaskAdvertisementTime;
        uint32 minGuildTaskRewardTime, maxGuildTaskRewardTime;
        uint32 guildTaskAdvertCleanupTime;
        uint32 guildTaskKillTaskDistance;

        uint32 iterationsPerTick;

        uint32 commandServerPort;
        bool perfMonEnabled;
};

#define sPlayerbotAIConfig PlayerbotAIConfig::instance()

