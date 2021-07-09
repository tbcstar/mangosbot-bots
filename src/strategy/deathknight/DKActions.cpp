/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DKActions.h"
#include "Playerbot.h"

NextAction** CastDeathchillAction::getPrerequisites()
{
    return NextAction::merge(NextAction::array(0, new NextAction("frost presence"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastDarkCommandAction::getPrerequisites()
{
    return NextAction::merge(NextAction::array(0, new NextAction("blood presence"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastUnholyMeleeSpellAction::getPrerequisites()
{
    return NextAction::merge(NextAction::array(0, new NextAction("unholy presence"), NULL), CastMeleeSpellAction::getPrerequisites());
}

NextAction** CastFrostMeleeSpellAction::getPrerequisites()
{
    return NextAction::merge(NextAction::array(0, new NextAction("frost presence"), NULL), CastMeleeSpellAction::getPrerequisites());
}

NextAction** CastBloodMeleeSpellAction::getPrerequisites()
{
    return NextAction::merge(NextAction::array(0, new NextAction("blood presence"), NULL), CastMeleeSpellAction::getPrerequisites());
}
