/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Common.h"

class ObjectGuid;
class Player;
class WorldPacket;

class Event
{
	public:
        Event(Event const& other) : source(other.source), param(other.param), packet(other.packet), owner(other.owner) { }
        Event() { }
        Event(std::string const& source) : source(source) { }
        Event(std::string const& source, std::string const& param, Player* owner = NULL) : source(source), param(param), owner(owner) { }
        Event(std::string const& source, WorldPacket& packet, Player* owner = NULL) : source(source), packet(packet), owner(owner) { }
        virtual ~Event() { }

        std::string const& getSource() { return source; }
        std::string const& getParam() { return param; }
        WorldPacket& getPacket() { return packet; }
        ObjectGuid getObject();
        Player* getOwner() { return owner; }
        bool operator! () const { return source.empty(); }

    protected:
        std::string source;
        std::string param;
        WorldPacket packet;
        ObjectGuid object;
        Player* owner;
};
