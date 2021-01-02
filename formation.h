#ifndef FORMATION_H
#define FORMATION_H

#include <QString>
#include <QSqlQueryModel>
#include<QDateTime>
#include<QTime>
class formation
{
public:
    formation();
    formation(int,int,QDateTime,int);
    int getidformation();
    int getidformateur();
    QDateTime getdateformation();
    int getduree();
    void setidformation(int);
    void setidformateur(int);
    void setdateformation(QDateTime);
    void setduree(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel * rechercher (const QString &aux);
    bool supprimer(int);
    bool modifier(int,int,QDateTime,int);
    QSqlQueryModel *  trie(const QString &critere, const QString &mode );


private:
    int idformation,idformateur;
    QDateTime dateformation;
    int duree;
};


#endif // FORMATION_H
