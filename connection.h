#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include<QDebug>
#include <QSqlQuery>
#include<iostream>
using namespace std;
class connection
{
private:
    QSqlDatabase db;
public:
    connection();

};

#endif // CONNECTION_H
