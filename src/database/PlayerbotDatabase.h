/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 * Copyright (C) 2021+ WarheadCore <https://github.com/WarheadCore>
 */

#ifndef _PLAYERBOTDATABASE_H
#define _PLAYERBOTDATABASE_H

#include "MySQLConnection.h"

enum PlayerbotDatabaseStatements : uint32
{
    /*  Naming standard for defines:
        {DB}_{SEL/INS/UPD/DEL/REP}_{Summary of data changed}
        When updating more than one field, consider looking at the calling function
        name for a suiting suffix.
    */

    MAX_PLAYERBOTDATABASE_STATEMENTS
};

class AC_DATABASE_API PlayerbotDatabaseConnection : public MySQLConnection
{
    public:
        typedef PlayerbotDatabaseStatements Statements;

        //- Constructors for sync and async connections
        PlayerbotDatabaseConnection(MySQLConnectionInfo& connInfo);
        PlayerbotDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo);
        ~PlayerbotDatabaseConnection();
};

#endif
