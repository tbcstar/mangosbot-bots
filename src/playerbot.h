/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

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
