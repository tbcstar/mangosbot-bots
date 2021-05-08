#include "botpch.h"
#include "../../playerbot.h"
#include "TellTargetAction.h"

#include "../../ServerFacade.h"
#include "ThreatManager.h"


using namespace ai;

bool TellTargetAction::Execute(Event event)
{
    Unit* target = context->GetValue<Unit*>("current target")->Get();
    if (target)
    {
        ostringstream out;
		out << "Attacking " << target->GetName();
        botAI->TellMaster(out);

        context->GetValue<Unit*>("old target")->Set(target);
    }
    return true;
}

bool TellAttackersAction::Execute(Event event)
{
    botAI->TellMaster("--- Attackers ---");

    list<ObjectGuid> attackers = context->GetValue<list<ObjectGuid> >("attackers")->Get();
    for (list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); i++)
    {
        Unit* unit = botAI->GetUnit(*i);
        if (!unit || !sServerFacade->IsAlive(unit))
            continue;

        botAI->TellMaster(unit->GetName());
    }

    botAI->TellMaster("--- Threat ---");
    HostileReference *ref = sServerFacade->GetHostileRefManager(bot).getFirst();
    if (!ref)
        return true;

    while( ref )
    {
        ThreatManager *threatManager = ref->getSource();
        Unit *unit = threatManager->getOwner();
        float threat = ref->getThreat();

        ostringstream out; out << unit->GetName() << " (" << threat << ")";
        botAI->TellMaster(out);

        ref = ref->next();
    }
    return true;
}
