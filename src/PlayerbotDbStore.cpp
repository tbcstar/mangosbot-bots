/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PlayerbotDbStore.h"
#include "Playerbot.h"

#include <iostream>

void PlayerbotDbStore::Load(PlayerbotAI* botAI)
{
    ObjectGuid::LowType guid = botAI->GetBot()->GetGUID().GetCounter();

    QueryResult results = PlayerbotDatabase.PQuery("SELECT `key`,`value` FROM `ai_playerbot_db_store` WHERE `guid` = '%u'", guid);
    if (results)
    {
        botAI->ClearStrategies(BOT_STATE_COMBAT);
        botAI->ClearStrategies(BOT_STATE_NON_COMBAT);
        botAI->ChangeStrategy("+chat", BOT_STATE_COMBAT);
        botAI->ChangeStrategy("+chat", BOT_STATE_NON_COMBAT);

        std::vector<std::string> values;
        do
        {
            Field* fields = results->Fetch();
            std::string key = fields[0].GetString();
            std::string value = fields[1].GetString();

            if (key == "value")
                values.push_back(value);
            else if (key == "co")
                botAI->ChangeStrategy(value, BOT_STATE_COMBAT);
            else if (key == "nc")
                botAI->ChangeStrategy(value, BOT_STATE_NON_COMBAT);
            else if (key == "dead")
                botAI->ChangeStrategy(value, BOT_STATE_DEAD);
        } while (results->NextRow());

        botAI->GetAiObjectContext()->Load(values);
    }
}

void PlayerbotDbStore::Save(PlayerbotAI* botAI)
{
    ObjectGuid::LowType guid = botAI->GetBot()->GetGUID().GetCounter();

    Reset(botAI);

    std::vector<std::string> data = botAI->GetAiObjectContext()->Save();
    for (std::vector<std::string>::iterator i = data.begin(); i != data.end(); ++i)
    {
        SaveValue(guid, "value", *i);
    }

    SaveValue(guid, "co", FormatStrategies("co", botAI->GetStrategies(BOT_STATE_COMBAT)));
    SaveValue(guid, "nc", FormatStrategies("nc", botAI->GetStrategies(BOT_STATE_NON_COMBAT)));
    SaveValue(guid, "dead", FormatStrategies("dead", botAI->GetStrategies(BOT_STATE_DEAD)));
}

std::string PlayerbotDbStore::FormatStrategies(std::string const& type, std::vector<std::string> strategies)
{
    std::ostringstream out;
    for (std::vector<std::string>::iterator i = strategies.begin(); i != strategies.end(); ++i)
        out << "+" << (*i).c_str() << ",";

    std::string res = out.str();
    return res.substr(0, res.size() - 1);
}

void PlayerbotDbStore::Reset(PlayerbotAI* botAI)
{
    ObjectGuid::LowType guid = botAI->GetBot()->GetGUID().GetCounter();
    uint32 account = sObjectMgr->GetPlayerAccountIdByGUID(guid);
    PlayerbotDatabase.PExecute("DELETE FROM `ai_playerbot_db_store` WHERE `guid` = '%u'", guid);
}

void PlayerbotDbStore::SaveValue(uint32 guid, std::string const& key, std::string const& value)
{
    PlayerbotDatabase.PExecute("INSERT INTO `ai_playerbot_db_store` (`guid`, `key`, `value`) VALUES ('%u', '%s', '%s')", guid, key.c_str(), value.c_str());
}
