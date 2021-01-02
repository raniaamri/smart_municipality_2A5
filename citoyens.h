#ifndef CITOYENS_H
#define CITOYENS_H
#include "QString"
#include <QtSql/QSqlQueryModel>

class Cit
{
public:
    Cit();
    Cit(int,QString,QString,QString);

    void setidC(int);
    void setnomC(QString);
    void setprenomC(QString);
    void setdateC(QString);

    int getidC();
    QString getnomC();
    QString getprenomC();
    QString getdateC();

    bool Cajout();
    QSqlQueryModel* Caffiche();
    QSqlQueryModel * Crecherche (const QString &aux);
    bool Csupprimer(int);
    bool Cmodifier(int,QString,QString,QString);
    QSqlQueryModel* CtriIDasc();
    QSqlQueryModel* CtriIDdesc();
    QSqlQueryModel* CtriNOMasc();
    QSqlQueryModel* CtriNOMdesc();




private:
    int idC;
    QString nomC,prenomC,dateC;
};
#endif // CITOYENS_H
