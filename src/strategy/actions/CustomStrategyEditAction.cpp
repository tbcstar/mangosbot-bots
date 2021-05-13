#include "botpch.h"
#include "../../playerbot.h"
#include "CustomStrategyEditAction.h"
#include "../CustomStrategy.h"


using namespace ai;


bool CustomStrategyEditAction::Execute(Event event)
{
    string text = event.getParam();
    int pos = text.find(" ");
    if (pos == string::npos) return PrintHelp();
    string name = text.substr(0, pos);
    text = text.substr(pos + 1);

    pos = text.find(" ");
    if (pos == string::npos) pos = text.size();
    string idx = text.substr(0, pos);
    text = pos >= text.size() ? "" : text.substr(pos + 1);

    return idx == "?" ? Print(name) : Edit(name, atoi(idx.c_str()), text);
}

bool CustomStrategyEditAction::PrintHelp()
{
    botAI->TellMaster("=== Custom strategies ===");

    uint32 owner = (uint32)botAI->GetBot()->GetGUID().GetCounter();
    QueryResult* results = CharacterDatabase.PQuery("SELECT distinct name FROM ai_playerbot_custom_strategy WHERE owner = '%u'",
            owner);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            string name = fields[0].GetString();
            botAI->TellMaster(name);
        } while (results->NextRow());

        delete results;
    }
    botAI->TellMaster("Usage: cs <name> <idx> <command>");
    return false;
}

bool CustomStrategyEditAction::Print(string name)
{
    ostringstream out; out << "=== " << name << " ===";
    botAI->TellMaster(out.str());

    uint32 owner = (uint32)botAI->GetBot()->GetGUID().GetCounter();
    QueryResult* results = CharacterDatabase.PQuery("SELECT idx, action_line FROM ai_playerbot_custom_strategy WHERE name = '%s' and owner = '%u' order by idx",
            name.c_str(), owner);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 idx = fields[0].GetUInt32();
            string action = fields[1].GetString();

            PrintActionLine(idx, action);
        } while (results->NextRow());

        delete results;
    }
    return true;
}

bool CustomStrategyEditAction::Edit(string name, uint32 idx, string command)
{
    uint32 owner = (uint32)botAI->GetBot()->GetGUID().GetCounter();
    QueryResult* results = CharacterDatabase.PQuery("SELECT action_line FROM ai_playerbot_custom_strategy WHERE name = '%s' and owner = '%u' and idx = '%u'",
            name.c_str(), owner, idx);
    if (results)
    {
        if (command.empty())
        {
            CharacterDatabase.DirectPExecute("DELETE FROM ai_playerbot_custom_strategy WHERE name = '%s' and owner = '%u' and idx = '%u'",
                        name.c_str(), owner, idx);
        }
        else
        {
            CharacterDatabase.DirectPExecute("UPDATE ai_playerbot_custom_strategy SET action_line = '%s' WHERE name = '%s' and owner = '%u' and idx = '%u'",
                        command.c_str(), name.c_str(), owner, idx);
        }
        delete results;
    }
    else
    {
        CharacterDatabase.DirectPExecute("INSERT INTO ai_playerbot_custom_strategy (name, owner, idx, action_line) VALUES ('%s', '%u', '%u', '%s')",
                    name.c_str(), owner, idx, command.c_str());
    }

    PrintActionLine(idx, command);

    ostringstream ss; ss << "custom::" << name;
    Strategy* strategy = botAI->GetAiObjectContext()->GetStrategy(ss.str());
    if (strategy)
    {
        CustomStrategy *cs = dynamic_cast<CustomStrategy*>(strategy);
        if (cs)
        {
            cs->Reset();
            botAI->ReInitCurrentEngine();
        }
    }
    return true;
}

bool CustomStrategyEditAction::PrintActionLine(uint32 idx, string command)
{
    ostringstream out; out << "#" << idx << " " << command;
    botAI->TellMaster(out.str());
    return true;
}
