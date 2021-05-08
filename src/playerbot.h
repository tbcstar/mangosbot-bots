/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Chat.h"
#include "Common.h"
#include "Creature.h"
#include "Group.h"
#include "Guild.h"
#include "MotionMaster.h"
#include "ObjectMgr.h"
#include "SharedDefines.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "World.h"
#include "WorldPacket.h"

#include "PlayerbotAI.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotMgr.h"
#include "RandomPlayerbotMgr.h"

std::vector<std::string> split(const std::string& s, char delim);
void split(std::vector<std::string>& dest, std::string const& str, const char* delim);
#ifndef WIN32
int strcmpi(std::string s1, std::string s2);
#endif
