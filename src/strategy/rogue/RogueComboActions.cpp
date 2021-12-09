/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RogueComboActions.h"
#include "Playerbot.h"

bool CastComboAction::isUseful()
{
	return CastMeleeSpellAction::isUseful() && AI_VALUE2(uint8, "combo", "self target") < 5;
}