/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Creature.h"
#include "DatabaseEnvFwd.h"
#include "Gameobject.h"
#include "Group.h"
#include "Guild.h"
#include "MotionMaster.h"
#include "Pet.h"
#include "SharedDefines.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "World.h"
#include "WorldPacket.h"

#include "Event.h"
#include "Playerbot.h"
#include "PlayerbotAI.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotMgr.h"
#include "RandomPlayerbotMgr.h"
