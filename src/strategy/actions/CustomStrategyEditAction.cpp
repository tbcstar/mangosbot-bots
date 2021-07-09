/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CustomStrategyEditAction.h"
#include "CustomStrategy.h"
#include "Event.h"
#include "Playerbot.h"

bool CustomStrategyEditAction::Execute(Event event)
{
    std::string text = event.getParam();
    uint32 pos = text.find(" ");
    if (pos == std::string::npos)
        return PrintHelp();

    std::string const& name = text.substr(0, pos);
    text = text.substr(pos + 1);

    pos = text.find(" ");
    if (pos == std::string::npos)
        pos = text.size();

    std::string const& idx = text.substr(0, pos);
    text = pos >= text.size() ? "" : text.substr(pos + 1);

    return idx == "?" ? Print(name) : Edit(name, atoi(idx.c_str()), text);
}

bool CustomStrategyEditAction::PrintHelp()
{
    botAI->TellMaster("=== Custom strategies ===");

    uint32 owner = botAI->GetBot()->GetGUID().GetCounter();
    QueryResult results = PlayerbotDatabase.PQuery("SELECT DISTINCT name FROM ai_playerbot_custom_strategy WHERE owner = '%u'", owner);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            std::string const& name = fields[0].GetString();
            botAI->TellMaster(name);
        } while (results->NextRow());
    }

    botAI->TellMaster("Usage: cs <name> <idx> <command>");
    return false;
}

bool CustomStrategyEditAction::Print(std::string const& name)
{
    std::ostringstream out;
    out << "=== " << name << " ===";
    botAI->TellMaster(out.str());

    uint32 owner = botAI->GetBot()->GetGUID().GetCounter();
    QueryResult results = PlayerbotDatabase.PQuery("SELECT idx, action_line FROM ai_playerbot_custom_strategy WHERE name = '%s' AND owner = '%u' ORDER BY idx",
            name.c_str(), owner);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 idx = fields[0].GetUInt32();
            std::string const& action = fields[1].GetString();

            PrintActionLine(idx, action);
        } while (results->NextRow());
    }

    return true;
}

bool CustomStrategyEditAction::Edit(std::string const& name, uint32 idx, std::string const& command)
{
    uint32 owner = botAI->GetBot()->GetGUID().GetCounter();
    QueryResult results = PlayerbotDatabase.PQuery("SELECT action_line FROM ai_playerbot_custom_strategy WHERE name = '%s' AND owner = '%u' AND idx = '%u'",
        name.c_str(), owner, idx);
    if (results)
    {
        if (command.empty())
        {
            PlayerbotDatabase.DirectPExecute("DELETE FROM ai_playerbot_custom_strategy WHERE name = '%s' AND owner = '%u' AND idx = '%u'",
                name.c_str(), owner, idx);
        }
        else
        {
            PlayerbotDatabase.DirectPExecute("UPDATE ai_playerbot_custom_strategy SET action_line = '%s' WHERE name = '%s' AND owner = '%u' AND idx = '%u'",
                command.c_str(), name.c_str(), owner, idx);
        }
    }
    else
    {
        PlayerbotDatabase.DirectPExecute("INSERT INTO ai_playerbot_custom_strategy (name, owner, idx, action_line) VALUES ('%s', '%u', '%u', '%s')",
            name.c_str(), owner, idx, command.c_str());
    }

    PrintActionLine(idx, command);

    std::ostringstream ss;
    ss << "custom::" << name;

    if (Strategy* strategy = botAI->GetAiObjectContext()->GetStrategy(ss.str()))
    {
        if (CustomStrategy* cs = dynamic_cast<CustomStrategy*>(strategy))
        {
            cs->Reset();
            botAI->ReInitCurrentEngine();
        }
    }

    return true;
}

bool CustomStrategyEditAction::PrintActionLine(uint32 idx, std::string const& command)
{
    std::ostringstream out;
    out << "#" << idx << " " << command;
    botAI->TellMaster(out.str());
    return true;
}
