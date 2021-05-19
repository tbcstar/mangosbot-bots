#include "botpch.h"
#include "../../playerbot.h"
#include "DruidActions.h"

using namespace ai;

bool CastCasterFormAction::Execute(Event event)
{
    botAI->RemoveShapeshift();
    return true;
}

NextAction** CastAbolishPoisonAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison"), nullptr), CastSpellAction::getPrerequisites());
}

NextAction** CastAbolishPoisonOnPartyAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison on party"), nullptr), CastSpellAction::getPrerequisites());
}

Value<Unit*>* CastEntanglingRootsCcAction::GetTargetValue()
{
    return context->GetValue<Unit*>("cc target", "entangling roots");
}

bool CastEntanglingRootsCcAction::Execute(Event event)
{
    return botAI->CastSpell("entangling roots", GetTarget());
}

Value<Unit*>* CastHibernateCcAction::GetTargetValue()
{
    return context->GetValue<Unit*>("cc target", "hibernate");
}

bool CastHibernateCcAction::Execute(Event event)
{
    return botAI->CastSpell("hibernate", GetTarget());
}
