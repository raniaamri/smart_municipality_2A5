#include "connection.h"

Connection::Connection()
{}

bool Connection::ouvrirConnection()
{ db=QSqlDatabase::addDatabase("QODBC");

db.setDatabaseName("Source_Projet2A");
db.setUserName("haithem");
db.setPassword("haithem1");

if (db.open())
return true;
    return  false;
}

void Connection::fermerConnection()
{db.close();}
