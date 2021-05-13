/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RandomPlayerbotFactory.h"
#include "AccountMgr.h"
#include "GuildMgr.h"
#include "Playerbot.h"
#include "PlayerbotFactory.h"

std::map<uint8, std::vector<uint8>> RandomPlayerbotFactory::availableRaces;

RandomPlayerbotFactory::RandomPlayerbotFactory(uint32 accountId) : accountId(accountId)
{
    availableRaces[CLASS_WARRIOR].push_back(RACE_HUMAN);
    availableRaces[CLASS_WARRIOR].push_back(RACE_NIGHTELF);
    availableRaces[CLASS_WARRIOR].push_back(RACE_GNOME);
    availableRaces[CLASS_WARRIOR].push_back(RACE_DWARF);
    availableRaces[CLASS_WARRIOR].push_back(RACE_ORC);
    availableRaces[CLASS_WARRIOR].push_back(RACE_UNDEAD_PLAYER);
    availableRaces[CLASS_WARRIOR].push_back(RACE_TAUREN);
    availableRaces[CLASS_WARRIOR].push_back(RACE_TROLL);

    availableRaces[CLASS_PALADIN].push_back(RACE_HUMAN);
    availableRaces[CLASS_PALADIN].push_back(RACE_DWARF);

    availableRaces[CLASS_ROGUE].push_back(RACE_HUMAN);
    availableRaces[CLASS_ROGUE].push_back(RACE_DWARF);
    availableRaces[CLASS_ROGUE].push_back(RACE_NIGHTELF);
    availableRaces[CLASS_ROGUE].push_back(RACE_GNOME);
    availableRaces[CLASS_ROGUE].push_back(RACE_ORC);
    availableRaces[CLASS_ROGUE].push_back(RACE_TROLL);

    availableRaces[CLASS_PRIEST].push_back(RACE_HUMAN);
    availableRaces[CLASS_PRIEST].push_back(RACE_DWARF);
    availableRaces[CLASS_PRIEST].push_back(RACE_NIGHTELF);
    availableRaces[CLASS_PRIEST].push_back(RACE_TROLL);
    availableRaces[CLASS_PRIEST].push_back(RACE_UNDEAD_PLAYER);

    availableRaces[CLASS_MAGE].push_back(RACE_HUMAN);
    availableRaces[CLASS_MAGE].push_back(RACE_GNOME);
    availableRaces[CLASS_MAGE].push_back(RACE_UNDEAD);
    availableRaces[CLASS_MAGE].push_back(RACE_TROLL);

    availableRaces[CLASS_WARLOCK].push_back(RACE_HUMAN);
    availableRaces[CLASS_WARLOCK].push_back(RACE_GNOME);
    availableRaces[CLASS_WARLOCK].push_back(RACE_UNDEAD);
    availableRaces[CLASS_WARLOCK].push_back(RACE_ORC);

    availableRaces[CLASS_SHAMAN].push_back(RACE_ORC);
    availableRaces[CLASS_SHAMAN].push_back(RACE_TAUREN);
    availableRaces[CLASS_SHAMAN].push_back(RACE_TROLL);

    availableRaces[CLASS_HUNTER].push_back(RACE_DWARF);
    availableRaces[CLASS_HUNTER].push_back(RACE_NIGHTELF);
    availableRaces[CLASS_HUNTER].push_back(RACE_ORC);
    availableRaces[CLASS_HUNTER].push_back(RACE_TAUREN);
    availableRaces[CLASS_HUNTER].push_back(RACE_TROLL);

    availableRaces[CLASS_DRUID].push_back(RACE_NIGHTELF);
    availableRaces[CLASS_DRUID].push_back(RACE_TAUREN);
}

bool RandomPlayerbotFactory::CreateRandomBot(uint8 cls)
{
    sLog->outDebug( "Creating new random bot for class %d", cls);

    uint8 gender = rand() % 2 ? GENDER_MALE : GENDER_FEMALE;

    uint8 race = availableRaces[cls][urand(0, availableRaces[cls].size() - 1)];
    std::string name = CreateRandomBotName(gender);
    if (name.empty())
        return false;

    std::vector<uint8> skinColors, facialHairTypes;
    std::vector<std::pair<uint8,uint8>> faces, hairs;
    for (CharSectionsMap::const_iterator itr = sCharSectionMap.begin(); itr != sCharSectionMap.end(); ++itr)
    {
        CharSectionsEntry const* entry = itr->second;
        if (entry->RaceID != race || entry->SexID != gender)
            continue;

        switch (entry->BaseSection)
        {
            case SECTION_TYPE_SKIN:
                skinColors.push_back(entry->ColorIndex);
                break;
            case SECTION_TYPE_FACE:
                faces.push_back(pair<uint8,uint8>(entry->VariationIndex, entry->ColorIndex));
                break;
            case SECTION_TYPE_FACIAL_HAIR:
                facialHairTypes.push_back(entry->VariationIndex);
                break;
            case SECTION_TYPE_HAIR:
                hairs.push_back(pair<uint8,uint8>(entry->VariationIndex, entry->ColorIndex));
                break;
        }
    }

    uint8 skinColor = skinColors[urand(0, skinColors.size() - 1)];
    std::pair<uint8, uint8> face = faces[urand(0, faces.size() - 1)];
    std::pair<uint8, uint8> hair = hairs[urand(0, hairs.size() - 1)];

	bool excludeCheck = (race == RACE_TAUREN) || (gender == GENDER_FEMALE && race != RACE_NIGHTELF && race != RACE_UNDEAD_PLAYER);
	uint8 facialHair = excludeCheck ? 0 : facialHairTypes[urand(0, facialHairTypes.size() - 1)];

	WorldSession* session = new WorldSession(accountId, NULL, SEC_PLAYER, EXPANSION_WRATH_OF_THE_LICH_KING, time_t(0), LOCALE_enUS, 0, false, false, 0);

    std::unique_ptr<CharacterCreateInfo> characterInfo = std::make_unique<CharacterCreateInfo>(name, race, cls, gender, face.second, face.first, hair.first, hair.second, facialHair, 0, WorldPacket());

    Player* player = new Player(session);
    player->GetMotionMaster()->Initialize();
	if (!player->Create(sObjectMgr->GetGenerator<HighGuid::Player>().Generate(), characterInfo.get()))
    {
        player->CleanupsBeforeDelete();
        player->DeleteFromDB(player->GetGUID().GetCounter(), accountId, true, true);

        delete session;
        delete player;
        sLog->outError("Unable to create random bot for account %d - name: \"%s\"; race: %u; class: %u", accountId, name.c_str(), race, cls);
        return false;
    }

    player->setCinematic(2);
    player->SetAtLoginFlag(AT_LOGIN_NONE);
    player->SaveToDB(true, false);

    sLog->outDebug("Random bot created for account %d - name: \"%s\"; race: %u; class: %u", accountId, name.c_str(), race, cls);

    return true;
}

std::string RandomPlayerbotFactory::CreateRandomBotName(uint8 gender)
{
    std::string botName = "";

    QueryResult result = CharacterDatabase.Query("SELECT MAX(name_id) FROM ai_playerbot_names");
    if (!result)
    {
        sLog->outError("No more names left for random bots");
        return std::move(botName);
    }

    Field* fields = result->Fetch();
    uint32 maxId = fields[0].GetUInt32();

    result = CharacterDatabase.PQuery("SELECT n.name FROM ai_playerbot_names n "
        "LEFT OUTER JOIN characters e ON e.name = n.name WHERE e.guid IS NULL AND n.gender = '%u' ORDER BY RAND() LIMIT 1", gender);
    if (!result)
    {
        sLog->outError("No more names left for random bots");
        return std::move(botName);
    }

	fields = result->Fetch();
    botName = fields[0].GetString();

    return std::move(botName);
}

void RandomPlayerbotFactory::CreateRandomBots()
{
    if (sPlayerbotAIConfig->deleteRandomBotAccounts)
    {
        sLog->outString("Deleting random bot accounts...");

        QueryResult results = LoginDatabase.PQuery("SELECT id FROM account WHERE username LIKE '%s%%'", sPlayerbotAIConfig->randomBotAccountPrefix.c_str());
        if (results)
        {
            do
            {
                Field* fields = results->Fetch();
                AccountMgr::DeleteAccount(fields[0].GetUInt32());
            } while (results->NextRow());
        }

        CharacterDatabase.Execute("DELETE FROM ai_playerbot_random_bots");

        sLog->outString("Random bot accounts deleted");
    }

    for (uint32 accountNumber = 0; accountNumber < sPlayerbotAIConfig->randomBotAccountCount; ++accountNumber)
    {
        std::ostringstream out;
        out << sPlayerbotAIConfig->randomBotAccountPrefix << accountNumber;
        std::string accountName = out.str();

        QueryResult results = LoginDatabase.PQuery("SELECT id FROM account WHERE username = '%s'", accountName.c_str());
        if (results)
        {
            continue;
        }

        std::string password = "";
        for (uint8 i = 0; i < 10; i++)
        {
            password += (char)urand('!', 'z');
        }

        AccountMgr::CreateAccount(accountName, password);

        sLog->outDebug("Account %s created for random bots", accountName.c_str());
    }

    LoginDatabase.PExecute("UPDATE account SET expansion = '%u' WHERE username LIKE '%s%%'", EXPANSION_WRATH_OF_THE_LICH_KING, sPlayerbotAIConfig->randomBotAccountPrefix.c_str());

    uint32 totalRandomBotChars = 0;
    for (uint32 accountNumber = 0; accountNumber < sPlayerbotAIConfig->randomBotAccountCount; ++accountNumber)
    {
        std::ostringstream out;
        out << sPlayerbotAIConfig->randomBotAccountPrefix << accountNumber;
        std::string accountName = out.str();

        QueryResult results = LoginDatabase.PQuery("SELECT id FROM account WHERE username = '%s'", accountName.c_str());
        if (!results)
            continue;

        Field* fields = results->Fetch();
        uint32 accountId = fields[0].GetUInt32();

        sPlayerbotAIConfig->randomBotAccounts.push_back(accountId);

        uint32 count = AccountMgr::GetCharactersCount(accountId);
        if (count >= 10)
        {
            totalRandomBotChars += count;
            continue;
        }

        RandomPlayerbotFactory factory(accountId);
        for (uint8 cls = CLASS_WARRIOR; cls < MAX_CLASSES; ++cls)
        {
            if (cls != 10)
                factory.CreateRandomBot(cls);
        }

        totalRandomBotChars += AccountMgr::GetCharactersCount(accountId);
    }

    sLog->outString("%d random bot accounts with %d characters available", sPlayerbotAIConfig->randomBotAccounts.size(), totalRandomBotChars);
}

void RandomPlayerbotFactory::CreateRandomGuilds()
{
    std::vector<uint32> randomBots;

    QueryResult results = CharacterDatabase.PQuery("SELECT `bot` FROM ai_playerbot_random_bots WHERE event = 'add'");

    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 bot = fields[0].GetUInt32();
            randomBots.push_back(bot);
        } while (results->NextRow());
    }

    if (sPlayerbotAIConfig->deleteRandomBotGuilds)
    {
        sLog->outString("Deleting random bot guilds...");
        for (std::vector<uint32>::iterator i = randomBots.begin(); i != randomBots.end(); ++i)
        {
            if (Guild* guild = sGuildMgr->GetGuildByLeader(ObjectGuid::Create<HighGuid::Player>(*i)))
                guild->Disband();
        }

        sLog->outString("Random bot guilds deleted");
    }

    uint32 guildNumber = 0;
    GuidVector availableLeaders;
    for (std::vector<uint32>::iterator i = randomBots.begin(); i != randomBots.end(); ++i)
    {
        ObjectGuid leader = ObjectGuid::Create<HighGuid::Player>(*i);
        if (Guild* guild = sGuildMgr->GetGuildByLeader(leader))
        {
            ++guildNumber;
            sPlayerbotAIConfig->randomBotGuilds.push_back(guild->GetId());
        }
        else
        {
            Player* player = ObjectAccessor::FindPlayer(leader);
            if (player && !player->GetGuildId())
                availableLeaders.push_back(leader);
        }
    }

    for (; guildNumber < sPlayerbotAIConfig->randomBotGuildCount; ++guildNumber)
    {
        std::string const& guildName = CreateRandomGuildName();
        if (guildName.empty())
            break;

        if (availableLeaders.empty())
        {
            sLog->outError("No leaders for random guilds available");
            break;
        }

        uint32 index = urand(0, availableLeaders.size() - 1);
        ObjectGuid leader = availableLeaders[index];
        Player* player = ObjectAccessor::FindPlayer(leader);
        if (!player)
        {
            sLog->outError("Cannot find player for leader %u", leader);
            break;
        }

        Guild* guild = new Guild();
        if (!guild->Create(player, guildName))
        {
            sLog->outError("Error creating guild %s", guildName.c_str());
            delete guild;
            break;
        }

        sGuildMgr->AddGuild(guild);
        sPlayerbotAIConfig->randomBotGuilds.push_back(guild->GetId());
    }

    sLog->outString("%d random bot guilds available", guildNumber);
}

std::string RandomPlayerbotFactory::CreateRandomGuildName()
{
    std::string guildName = "";

    QueryResult result = CharacterDatabase.Query("SELECT MAX(name_id) FROM ai_playerbot_guild_names");
    if (!result)
    {
        sLog->outError("No more names left for random guilds");
        return std::move(guildName);
    }

    Field* fields = result->Fetch();
    uint32 maxId = fields[0].GetUInt32();

    uint32 id = urand(0, maxId);
    result = CharacterDatabase.PQuery("SELECT n.name FROM ai_playerbot_guild_names n "
            "LEFT OUTER JOIN guild e ON e.name = n.name WHERE e.guildid IS NULL AND n.name_id >= '%u' LIMIT 1", id);
    if (!result)
    {
        sLog->outError("No more names left for random guilds");
        return std::move(guildName);
    }

    fields = result->Fetch();
    guildName = fields[0].GetString();

    return std::move(guildName);
}

