#ifndef NAISSANCE_H
#define NAISSANCE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>


class naissance
{
private:
    int CIN;
    QString nom,prenom,lieu_de_naissance,nom_pere,prenom_pere,nom_dela_mere,prenom_dela_mere,nationalite,sexe,identite_de_declarant;
    QString    identite_de_officier,observations,note;
    QDate date_de_naissance,date_de_declaration;
public:
    naissance();
    naissance(int CIN,QString nom,QString prenom,QString lieu_de_naissance,QString nom_pere,QString prenom_pere,QString nom_dela_mere,QString prenom_dela_mere,QString nationalite,QString sexe,QString identite_de_declarant,QString identite_de_officier,QString observations,QString note,QDate date_de_naissance,QDate date_de_declaration);

    //les getters
    int getCIN(){return CIN;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getlieu_de_naissance(){return lieu_de_naissance;}
    QString getnom_pere(){return nom_pere;}
    QString getprenom_pere(){return prenom_pere;}
    QString getnom_dela_mere(){return nom_dela_mere;}
    QString getprenom_dela_mere(){return prenom_dela_mere;}
    QString getnationalite(){return nationalite;}
    QString getsexe(){return sexe;}
    QString getidentite_de_declarant(){return identite_de_declarant;}
    QString getidentite_de_officier(){return identite_de_officier;}
    QString getobservations(){return observations;}
    QString getnote(){return note;}
    QDate getdate_de_naissance(){return date_de_naissance;}
    QDate getdate_de_declaration(){return date_de_declaration;}
    /*------------------------------------------------------------------------------------------------------*/

    //les setters
    void setCIN(int CIN){this->CIN=CIN;}
    void setNom(QString nom){this->nom=nom;}
    void setPrenom(QString prenom){this->prenom=prenom;}
    void setlieu_de_naissance(QString lieu_de_naissance){this->lieu_de_naissance=lieu_de_naissance;}
    void setnom_pere(QString nom_pere){this->nom_pere=nom_pere;}
    void setprenom_pere(QString prenom_pere){this->prenom_pere=prenom_pere;}
    void setnom_dela_mere(QString nom_dela_mere){this->nom_dela_mere=nom_dela_mere;}
    void setprenom_dela_mere(QString prenom_dela_mere){this->prenom_dela_mere=prenom_dela_mere;}
    void setnationalite(QString nationalite){this->nationalite=nationalite;}
    void setsexe(QString sexe){this->sexe=sexe;}
    void setidentite_de_declarant(QString identite_de_declarant){this->identite_de_declarant=identite_de_declarant;}
    void setidentite_de_officier(QString identite_de_officier){this->identite_de_officier=identite_de_officier;}
    void setobservations(QString observations){this->observations=observations;}
    void setnote(QString note){this->note=note;}
    void setdate_de_naissance(QDate date_de_naissance){this->date_de_naissance=date_de_naissance;}
    void setdate_de_declaration(QDate date_de_declaration){this->date_de_declaration=date_de_declaration;}
    /*------------------------------------------------------------------------------------------------------*/

    //les methodes
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * afficher_tri_nom();
    QSqlQueryModel * afficher_tri_prenom();
    QSqlQueryModel * tri_tri();
    QSqlQueryModel * recherche_dynamique(QString);


};

#endif // NAISSANCE_H
