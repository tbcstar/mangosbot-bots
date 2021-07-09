/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PlayerbotCommandServer.h"
#include "Playerbot.h"

#include <cstdlib>
#include <iostream>

bool ReadLine(ACE_SOCK_Stream& client_stream, std::string* buffer, std::string* line)
{
    // Do the real reading from fd until buffer has '\n'.
    std::string::iterator pos;
    while ((pos = find(buffer->begin(), buffer->end(), '\n')) == buffer->end())
    {
        char buf[33];
        size_t n = client_stream.recv_n(buf, 1, 0);
        if (n == -1)
            return false;

        buf[n] = 0;
        *buffer += buf;
    }

    *line = string(buffer->begin(), pos);
    *buffer = string(pos + 1, buffer->end());
    return true;
}

class PlayerbotCommandServerThread: public ACE_Task <ACE_MT_SYNCH>
{
    public:
        int svc(void)
        {
            if (!sPlayerbotAIConfig->commandServerPort)
            {
                return 0;
            }

            std::ostringstream s;
            s << "Starting Playerbot Command Server on port " << sPlayerbotAIConfig->commandServerPort;
            LOG_INFO("playerbots", "%s", s.str().c_str());

            ACE_INET_Addr server(sPlayerbotAIConfig->commandServerPort);
            ACE_SOCK_Acceptor client_responder(server);

		    while (true)
		    {
			    ACE_SOCK_Stream client_stream;
			    ACE_Time_Value timeout(5);
			    ACE_INET_Addr client;
			    if (-1 != client_responder.accept(client_stream, &client, &timeout))
			    {
				    string buffer, request;
				    while (ReadLine(client_stream, &buffer, &request))
				    {
					    string response = sRandomPlayerbotMgr->HandleRemoteCommand(request) + "\n";
					    client_stream.send_n(response.c_str(), response.size(), 0);
					    request = "";
				    }
				    client_stream.close();
			    }
		    }

            return 0;
        }
};


void PlayerbotCommandServer::Start()
{
    PlayerbotCommandServerThread *thread = new PlayerbotCommandServerThread();
    thread->activate();
}

