#include "connection.h"
#include"QSqlDatabase"
#include <QDebug>
connection::connection()
{

}
bool connection::createConnection()
{
    qDebug()<<"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm";
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_2A");
    db.setUserName("hanen");
    db.setPassword("hanen");
    if(db.open())
        test=true;
    return test;
}
