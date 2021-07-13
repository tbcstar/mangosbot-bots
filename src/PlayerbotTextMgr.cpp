/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PlayerbotTextMgr.h"
#include "Playerbot.h"

void replaceAll(std::string& str, std::string const& from, std::string const& to);

void PlayerbotTextMgr::LoadTemplates()
{
    LOG_INFO("playerbots", "Loading playerbot texts...");

    QueryResult results = PlayerbotDatabase.PQuery("SELECT `key`,`text` FROM `playerbot_text`");
    uint32 count = 0;
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            std::string const& key = fields[0].GetString();
            std::string const& text = fields[1].GetString();
            templates[key].push_back(text);
            ++count;
        } while (results->NextRow());
    }

    LOG_INFO("playerbots", "%d playerbot texts loaded", count);
}

std::string PlayerbotTextMgr::Format(std::string const& key, std::map<std::string, std::string> placeholders)
{
    if (templates.empty())
        LoadTemplates();

    std::vector<std::string>& list = templates[key];
    if (list.empty())
    {
        std::ostringstream out;
        out << "Unknown text: " << key;
        return out.str();
    }

    std::string str = list[urand(0, list.size() - 1)];
    for (std::map<std::string, std::string>::iterator i = placeholders.begin(); i != placeholders.end(); ++i)
        replaceAll(str, i->first, i->second);

    return str;
}
