/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 * Copyright (C) 2021+ WarheadCore <https://github.com/WarheadCore>
 */

#include "PlayerbotDatabase.h"
#include "MySQLPreparedStatement.h"

void PlayerbotDatabaseConnection::DoPrepareStatements()
{
    if (!m_reconnecting)
        m_stmts.resize(MAX_PLAYERBOTDATABASE_STATEMENTS);
}

PlayerbotDatabaseConnection::PlayerbotDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo)
{
}

PlayerbotDatabaseConnection::PlayerbotDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo)
{
}

PlayerbotDatabaseConnection::~PlayerbotDatabaseConnection()
{
}
