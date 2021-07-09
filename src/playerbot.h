/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Creature.h"
#include "DatabaseEnv.h"
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

#include "PlayerbotAI.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotMgr.h"
#include "RandomPlayerbotMgr.h"
#include "AiObjectContext.h"

std::vector<std::string> split(std::string const& s, char delim);
void split(std::vector<std::string>& dest, std::string const& str, char const* delim);
#ifndef WIN32
int strcmpi(char const* s1, char const* s2);
#endif

#define CAST_ANGLE_IN_FRONT (2 * M_PI_F / 3)
#define EMOTE_ANGLE_IN_FRONT (2 * M_PI_F / 6)

#define AI_VALUE(type, name) context->GetValue<type>(name)->Get()
#define AI_VALUE2(type, name, param) context->GetValue<type>(name, param)->Get()

// Ultranix: missing death knight
// Ultranix: sLog->outdebug
// Ultranix: RACE_DRAENEI and RACE_BLOOD_ELF
// Ultranix: eots
// Ultranix: "... botAI"
// Ultranix: strategy for dk
// Ultranix: new sockets and threading
// Ultranix: check bigints in database
// Ultranix .c_str for strings in logs
// Ultranix: NULL
// Ultranix: check bg packets
// Ultranix: update config with default values from playerbotconfig.cpp
// Ultranix: IKE_PATHFINDER
