#ifndef DEMANDES_H
#define DEMANDES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class demandes
{
public:
    demandes();
    demandes(int,QString,QString,QString);
    QString get_nom(){return nom;}
    bool ajouter();
    bool Modifier();
    QSqlQueryModel *sortid_up();
    QSqlQueryModel *sortid_down();
    bool supprimer(int);
    QSqlQueryModel *afficher();
    QSqlQueryModel * rechercher (const QString &aux);

private :
    int id_demande;
    QString prenom;
    QString nom;
    QString etat;
};

#endif // DEMANDES_H
