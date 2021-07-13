/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CustomStrategy.h"
#include "Playerbot.h"

#include <regex>

std::map<std::string, std::string> CustomStrategy::actionLinesCache;

NextAction* toNextAction(std::string const& action)
{
    std::vector<std::string> tokens = split(action, '!');
    if (tokens.size() == 2 && !tokens[0].empty())
        return new NextAction(tokens[0], atof(tokens[1].c_str()));
    else if (tokens.size() == 1 && !tokens[0].empty())
        return new NextAction(tokens[0], ACTION_NORMAL);

    LOG_ERROR("playerbots", "Invalid action '%s'", action.c_str());
    return nullptr;
}

NextAction** toNextActionArray(std::string const& actions)
{
    std::vector<std::string> tokens = split(actions, ',');
    NextAction** res = new NextAction*[tokens.size() + 1];

    uint32 index = 0;
    for (std::vector<std::string>::iterator i = tokens.begin(); i != tokens.end(); ++i)
    {
        if (NextAction* na = toNextAction(*i))
            res[index++] = na;
    }

	res[index++] = nullptr;
    return res;
}

TriggerNode* toTriggerNode(std::string const& actionLine)
{
    std::vector<std::string> tokens = split(actionLine, '>');
    if (tokens.size() == 2)
        return new TriggerNode(tokens[0], toNextActionArray(tokens[1]));

    LOG_ERROR("playerbots", "Invalid action line '%s'", actionLine.c_str());
    return nullptr;
}

CustomStrategy::CustomStrategy(PlayerbotAI* botAI) : Strategy(botAI), Qualified()
{
}

void CustomStrategy::InitTriggers(std::vector<TriggerNode*> &triggers)
{
    if (actionLines.empty())
    {
        if (actionLinesCache[qualifier].empty())
        {
            LoadActionLines((uint32)botAI->GetBot()->GetGUID().GetCounter());
            if (actionLines.empty())
                LoadActionLines(0);
        }
        else
        {
            std::vector<std::string> tokens = split(actionLinesCache[qualifier], '\n');
            std::regex tpl("\\(nullptr,\\s*'.+',\\s*'(.+)'\\)(,|;)");
            for (std::vector<std::string>::iterator i = tokens.begin(); i != tokens.end(); ++i)
            {
                std::string const& line = *i;
                for (std::sregex_iterator j = std::sregex_iterator(line.begin(), line.end(), tpl); j != std::sregex_iterator(); ++j)
                {
                    std::smatch match = *j;
                    std::string const& actionLine = match[1].str();
                    if (!actionLine.empty())
                        actionLines.push_back(actionLine);
                }
            }
        }
    }

    for (std::vector<std::string>::iterator i = actionLines.begin(); i != actionLines.end(); ++i)
    {
        if (TriggerNode* tn = toTriggerNode(*i))
            triggers.push_back(tn);
    }
}

void CustomStrategy::LoadActionLines(uint32 owner)
{
    QueryResult results = PlayerbotDatabase.PQuery("SELECT action_line FROM playerbot_custom_strategy WHERE name = '%s' AND owner = '%u' ORDER BY idx",
            qualifier.c_str(), owner);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            std::string const& action = fields[0].GetString();
            actionLines.push_back(action);
        } while (results->NextRow());
    }
}

void CustomStrategy::Reset()
{
    actionLines.clear();
    actionLinesCache[qualifier].clear();
}
