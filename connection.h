#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>

class Connection
{
private:
    QSqlDatabase db;
public:
    Connection();
    bool ouvrirConnection();
    void fermerConnection();

};

#endif // CONNECTION_H
