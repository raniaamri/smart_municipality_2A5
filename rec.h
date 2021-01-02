#ifndef REC_H
#define REC_H
#include "QString"
#include <QtSql/QSqlQueryModel>

class Rec
{
public:
    Rec();
    Rec(int,QString,QString);

    void setid(int);
    void setraison(QString);
    void setemplacement(QString);

    int getid();
    QString getraison();
    QString getemplacement();

    bool ajout();
    QSqlQueryModel* affiche();
    QSqlQueryModel * recherche (const QString &aux);
    bool supprimer(int);
    bool modifier(int,QString,QString);
    QSqlQueryModel* triID();
    QSqlQueryModel* triEMP();




private:
    int id;
    QString raison,emplacement;
};

#endif // REC_H
