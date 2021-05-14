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
#include "strategy/AiObjectContext.h"

std::vector<std::string> split(std::string const& s, char delim);
void split(std::vector<std::string>& dest, std::string const& str, char const* delim);
#ifndef WIN32
int strcmpi(std::string s1, std::string s2);
#endif

#define CAST_ANGLE_IN_FRONT (2 * M_PI_F / 3)
#define EMOTE_ANGLE_IN_FRONT (2 * M_PI_F / 6)

#define AI_VALUE(type, name) context->GetValue<type>(name)->Get()
#define AI_VALUE2(type, name, param) context->GetValue<type>(name, param)->Get()

// Ultranix: missing death knighta
// Ultranix: sLog->outdebug
// Ultranix: NULL --> nullptr
// Ultranix: RACE_DRAENEI
