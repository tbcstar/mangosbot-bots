#include "botpch.h"
#include "../../playerbot.h"
#include "TellLosAction.h"


using namespace ai;

bool TellLosAction::Execute(Event event)
{
    string param = event.getParam();

    if (param.empty() || param == "targets")
    {
        ListUnits("--- Targets ---", *context->GetValue<list<ObjectGuid> >("possible targets"));
        ListUnits("--- Targets (All) ---", *context->GetValue<list<ObjectGuid> >("all targets"));
    }

    if (param.empty() || param == "npcs")
    {
        ListUnits("--- NPCs ---", *context->GetValue<list<ObjectGuid> >("nearest npcs"));
    }

    if (param.empty() || param == "corpses")
    {
        ListUnits("--- Corpses ---", *context->GetValue<list<ObjectGuid> >("nearest corpses"));
    }

    if (param.empty() || param == "gos" || param == "game objects")
    {
        ListGameObjects("--- Game objects ---", *context->GetValue<list<ObjectGuid> >("nearest game objects"));
    }

    if (param.empty() || param == "players")
    {
        ListUnits("--- Friendly players ---", *context->GetValue<list<ObjectGuid> >("nearest friendly players"));
    }

    return true;
}

void TellLosAction::ListUnits(string title, list<ObjectGuid> units)
{
    botAI->TellMaster(title);

    for (list<ObjectGuid>::iterator i = units.begin(); i != units.end(); i++)
    {
        Unit* unit = botAI->GetUnit(*i);
        if (unit)
            botAI->TellMaster(unit->GetName());
    }

}
void TellLosAction::ListGameObjects(string title, list<ObjectGuid> gos)
{
    botAI->TellMaster(title);

    for (list<ObjectGuid>::iterator i = gos.begin(); i != gos.end(); i++)
    {
        GameObject* go = botAI->GetGameObject(*i);
        if (go)
            botAI->TellMaster(chat->formatGameobject(go));
    }
}
