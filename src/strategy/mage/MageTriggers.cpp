#include "botpch.h"
#include "../../playerbot.h"
#include "MageTriggers.h"
#include "MageActions.h"

using namespace ai;

bool MageArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !botAI->HasAura("ice armor", target) &&
        !botAI->HasAura("frost armor", target) &&
        !botAI->HasAura("molten armor", target) &&
        !botAI->HasAura("mage armor", target);
}
