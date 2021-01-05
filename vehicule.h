#ifndef VEHICULE_H
#define VEHICULE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDebug>




class vehicule
{
    int ID_V;
    QString NOM,REFERENCE;
public:
    vehicule();
    vehicule(int,QString,QString);

    void setid_v(int);
    void setnom(QString);
    void setreference(QString);

    int getID_V();
    QString get_NOM();
    QString get_REFERENCE();


    bool ajouter();
    QSqlQueryModel * Afficher();
    QSqlQueryModel * Afficher_vehicule();

    bool supprimer(int);
    bool modifier(int, QString, QString);
    void chercher();
    QSqlQueryModel * recherche (int etat,QString champ,QString valeur);




   // QString test_tri2(int);
   // QSqlQueryModel* tri (int);
   // QString test_recherche2(int);
   // QSqlQueryModel* recherche_vehicule(QString,int);
   // QSqlQueryModel* rechercheemail_S (QString);
   // QString test_modifier2(int);
   // bool modifier(QString,QString,int);
};

#endif // VEHICULE_H

