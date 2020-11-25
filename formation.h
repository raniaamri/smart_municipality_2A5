#ifndef FORMATION_H
#define FORMATION_H

#include <QString>
#include <QSqlQueryModel>
class formation
{
public:
    formation();
    formation(int,int,QString);
    int getidformation();
    int getidformateur();
    QString getdateformation();
    void setidformation(int);
    void setidformateur(int);
    void setdateformation(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel * rechercher (const QString &aux);
    bool supprimer(int);
    bool modifier(int,int,QString);
    QSqlQueryModel* trie();


private:
    int idformation,idformateur;
    QString dateformation;
};


#endif // FORMATION_H
