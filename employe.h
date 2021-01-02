#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQueryModel>
#include<QThread>
#include<QSound>
#include<QDate>
class Employe
{
public:
    Employe();
    Employe(int,int,QString,QString,QDate);
    int getid();
    int getsalaire();
    QString getnom();
    QString getprenom();
    QDate getdate();
    void setid(int);
    void setsalaire(int);
    void setnom(QString);
    void setprenom(QString);
    void setdate(QDate);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel * rechercher (const QString &aux);
    bool supprimer(int);
    bool modifier(int,int,QString,QString,QDate);
    QSqlQueryModel *  trie(const QString &critere, const QString &mode );
    QSqlQueryModel * afficher_employe ();


private:


    int id,salaire;
    QString nom, prenom;
    QDate date_de_naissance;
};
#endif // EMPLOYE_H

