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
    encaissement(QString,QString,int,QString);
    int get_id_employe();
    QString get_methode_encaissement();
    QString get_remarque_encaissement();
   QString get_montant_encaissement();
    bool ajouter();
    QSqlQueryModel *afficher();
     QSqlQueryModel *afficher_ang();
    bool modifier();
    QSqlQueryModel *afficher_asc();
    QSqlQueryModel *afficher_dec();
    QSqlQueryModel *afficher_asc_ang();
    QSqlQueryModel *afficher_dec_ang();
    bool supprimer(QString);
    QSqlQueryModel *rechercher(QString);
    QSqlQueryModel *rechercher_ang(QString);
    QSqlQueryModel *afficher_asc_id();
    QSqlQueryModel *afficher_dec_id();
    QSqlQueryModel *afficher_asc_id_ang();
    QSqlQueryModel *afficher_dec_id_ang();
    QSqlQueryModel *afficher_asc_methode();
    QSqlQueryModel *afficher_dec_methode();
    QSqlQueryModel *afficher_asc_method();
    QSqlQueryModel *afficher_dec_method();
    QSqlQueryModel *afficher_asc_date();
    QSqlQueryModel *afficher_asc_date_ang();
    QSqlQueryModel *afficher_dec_date();
     QSqlQueryModel *afficher_dec_date_ang();
private :
    int id_employe ;
    QString methode_encaissement  , remarque_encaissement;
    QString montant_encaissement;
};




























#endif // ENCAISSEMENT_H
