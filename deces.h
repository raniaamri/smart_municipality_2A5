#ifndef DECES_H
#define DECES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class deces
{
private:
    int CINd;
    QString nomd,prenomd,lieu_de_naissanced,nom_pered,prenom_pered,nom_dela_mered,prenom_dela_mered,nationalited,sexed,identite_de_declarantd;
    QString    identite_de_officierd,observationsd,noted,lieu_de_deces;
    QDate date_de_naissanced,date_de_declaration_dedeces,date_de_deces;
public:
    deces();
    deces(int CINd,QString nomd,QString prenomd,QString lieu_de_naissanced,QString nom_pered,QString prenom_pered,QString nom_dela_mered,QString prenom_dela_mered,QString nationalited,QString sexed,QString identite_de_declarantd,QString identite_de_officierd,QString observationsd,QString noted,QString lieu_de_deces,QDate date_de_naissanced,QDate date_de_declaration_dedeces,QDate date_de_deces);

    //les getters
    int getCINd(){return CINd;}
    QString getNomd(){return nomd;}
    QString getPrenomd(){return prenomd;}
    QString getlieu_de_naissanced(){return lieu_de_naissanced;}
    QString getnom_pered(){return nom_pered;}
    QString getprenom_pered(){return prenom_pered;}
    QString getnom_dela_mered(){return nom_dela_mered;}
    QString getprenom_dela_mered(){return prenom_dela_mered;}
    QString getnationalited(){return nationalited;}
    QString getsexed(){return sexed;}
    QString getidentite_de_declarantd(){return identite_de_declarantd;}
    QString getidentite_de_officierd(){return identite_de_officierd;}
    QString getobservationsd(){return observationsd;}
    QString getnoted(){return noted;}
    QDate getdate_de_naissanced(){return date_de_naissanced;}
    QDate getdate_de_declarationd(){return date_de_declaration_dedeces;}
    QDate getdate_de_deces(){return date_de_deces;}
    QString getlieu_de_deces(){return lieu_de_deces;}

    /*------------------------------------------------------------------------------------------------------*/

    //les setters
    void setCINd(int CINd){this->CINd=CINd;}
    void setNomd(QString nomd){this->nomd=nomd;}
    void setPrenomd(QString prenomd){this->prenomd=prenomd;}
    void setlieu_de_naissanced(QString lieu_de_naissanced){this->lieu_de_naissanced=lieu_de_naissanced;}
    void setnom_pered(QString nom_pered){this->nom_pered=nom_pered;}
    void setprenom_pered(QString prenom_pered){this->prenom_pered=prenom_pered;}
    void setnom_dela_mered(QString nom_dela_mered){this->nom_dela_mered=nom_dela_mered;}
    void setprenom_dela_mered(QString prenom_dela_mered){this->prenom_dela_mered=prenom_dela_mered;}
    void setnationalited(QString nationalited){this->nationalited=nationalited;}
    void setsexed(QString sexed){this->sexed=sexed;}
    void setidentite_de_declarantd(QString identite_de_declarantd){this->identite_de_declarantd=identite_de_declarantd;}
    void setidentite_de_officierd(QString identite_de_officierd){this->identite_de_officierd=identite_de_officierd;}
    void setobservationsd(QString observationsd){this->observationsd=observationsd;}
    void setnoted(QString noted){this->noted=noted;}
    void setdate_de_naissanced(QDate date_de_naissanced){this->date_de_naissanced=date_de_naissanced;}
    void setdate_de_declarationd(QDate date_de_declaration_dedeces){this->date_de_declaration_dedeces=date_de_declaration_dedeces;}
    void setdate_de_deces(QDate date_de_deces){this->date_de_deces=date_de_deces;}
    void setlieu_de_deces(QString lieu_de_deces){this->lieu_de_deces=lieu_de_deces;}
    /*------------------------------------------------------------------------------------------------------*/

    //les methodes
    bool ajouter_deces();
    QSqlQueryModel * afficher_deces();
    bool supprimer_deces(int);
    bool modifier_deces();


};

#endif // DECES_H
