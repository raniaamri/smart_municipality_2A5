#include "connection.h"

Connection::Connection()
{

}



bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("SM-BD");
    db.setUserName("rania");
    db.setPassword("rania");
    if(db.open())
        test=true;
    return test;

}
