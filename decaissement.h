#ifndef DECAISSEMENT_H
#define DECAISSEMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "QDate"

class decaissement
{
public :
    decaissement();
   decaissement(int,QString,QString,int,QString);
    int get_code_decaissement();
    int get_id_em_dec();
    QString get_methode_decaissement();
    QString get_remarque_decaissement();
   QString get_montant_decaissement();
    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier();
    QSqlQueryModel *afficher_asc();
    QSqlQueryModel *afficher_dec();
     bool supprimer(QString);
     QSqlQueryModel *rechercher(QString);
private :
    int code_decaissement, id_em_dec ;
    QString methode_decaissement  , remarque_decaissement;
    QString montant_decaissement;
};

#endif // DECAISSEMENT_H
