#ifndef ENCAISSEMENT_H
#define ENCAISSEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "QDate"

class encaissement
{
public :
    encaissement();
    encaissement(int,QString,QString,int,QString);
    int get_code_encaissemen();
    int get_id_employe();
    QString get_methode_encaissement();
    QString get_remarque_encaissement();
   QString get_montant_encaissement();
    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier();
    QSqlQueryModel *afficher_asc();
    QSqlQueryModel *afficher_dec();
    bool supprimer(QString);
    QSqlQueryModel *rechercher(QString);
private :
    int code_encaissement, id_employe ;
    QString methode_encaissement  , remarque_encaissement;
    QString montant_encaissement;
};




























#endif // ENCAISSEMENT_H
