#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQueryModel>
class Employe
{
public:
    Employe();
    Employe(int,int,QString,QString,QString);
    int getid();
    int getsalaire();
    QString getnom();
    QString getprenom();
    QString getdate();
    void setid(int);
    void setsalaire(int);
    void setnom(QString);
    void setprenom(QString);
    void setdate(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel * rechercher (const QString &aux);
    bool supprimer(int);
    bool modifier(int,int,QString,QString,QString);
    QSqlQueryModel* trie();


private:
    int id,salaire;
    QString nom, prenom, date_de_naissance;
};

#endif // EMPLOYE_H
