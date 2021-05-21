#include "botpch.h"
#include "../../playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockActions.h"

using namespace botAI;

bool DemonArmorTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return !botAI->HasAura("demon skin", target) &&
		!botAI->HasAura("demon armor", target) &&
		!botAI->HasAura("fel armor", target);
}

bool SpellstoneTrigger::IsActive() 
{
    return BuffTrigger::IsActive() && AI_VALUE2(uint8, "item count", getName()) > 0;
}
