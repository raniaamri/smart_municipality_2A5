#include "connection.h"
#include <QSqlDatabase>
#include<QDebug>
#include <QSqlQuery>
#include<iostream>
#include <QSqlError>
using namespace std;
connection::connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet2A5");
    db.setUserName("soulayma");
    db.setPassword("soulayma");
    if(db.open())
    {
        cout<<"succes"<<endl;
    }
        else
        {
        qDebug()<< db.lastError();
        cout<<"failed"<<endl;
        }
}
