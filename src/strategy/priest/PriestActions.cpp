#include "botpch.h"
#include "../../playerbot.h"
#include "PriestActions.h"

using namespace botAI;


NextAction** CastAbolishDiseaseAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("cure disease"), nullptr), CastSpellAction::getAlternatives());
}

NextAction** CastAbolishDiseaseOnPartyAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("cure disease on party"), nullptr), CastSpellAction::getAlternatives());
}

