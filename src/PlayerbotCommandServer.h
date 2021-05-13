/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PlayerbotCommandServer_H
#define _PlayerbotCommandServer_H

class PlayerbotCommandServer
{
    public:
        PlayerbotCommandServer() { }
        virtual ~PlayerbotCommandServer() { }
        static PlayerbotCommandServer* instance()
        {
            static PlayerbotCommandServer instance;
            return &instance;
        }

        void Start();
};

#define sPlayerbotCommandServer PlayerbotCommandServer::instance()

#endif
