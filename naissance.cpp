#include "naissance.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
naissance::naissance()
{
    this->CIN=0;
    this->nom="";
    this->prenom="";
    this->lieu_de_naissance="";
    this->nom_pere="";
    this->prenom_pere="";
    this->nom_dela_mere="";
    this->prenom_dela_mere="";
    this->nationalite="";
    this->sexe="";
    this->identite_de_declarant="";
    this->identite_de_officier="";
    this->observations="";
    this->note="";
    this->date_de_naissance=QDate::currentDate();
    this->date_de_declaration=QDate::currentDate();

}
naissance::naissance(int CIN,QString nom,QString prenom,QString lieu_de_naissance,QString nom_pere,QString prenom_pere,QString nom_dela_mere,QString prenom_dela_mere,QString nationalite,QString sexe,QString identite_de_declarant,QString identite_de_officier,QString observations,QString note,QDate date_de_naissance,QDate date_de_declaration)
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
    this->lieu_de_naissance=lieu_de_naissance;
    this->nom_pere=nom_pere;
    this->prenom_pere=prenom_pere;
    this->nom_dela_mere=nom_dela_mere;
    this->prenom_dela_mere=prenom_dela_mere;
    this->nationalite=nationalite;
    this->sexe=sexe;
    this->identite_de_declarant=identite_de_declarant;
    this->identite_de_officier=identite_de_officier;
    this->observations=observations;
    this->note=note;
    this->date_de_naissance=date_de_naissance;
    this->date_de_declaration=date_de_declaration;

}
bool naissance::ajouter(){

    QSqlQuery query;

    query.prepare("insert into naissance (CIN,nom,prenom,lieu_de_naissance,nom_pere,prenom_pere,nom_dela_mere,prenom_dela_mere,nationalite,sexe,identite_de_declarant,identite_de_officier,observations,note,date_de_naissance,date_de_declaration)"
                  "values(:CIN,:nom,:prenom,:lieu_de_naissance,:nom_pere,:prenom_pere,:nom_dela_mere,:prenom_dela_mere,:nationalite,:sexe,:identite_de_declarant,:identite_de_officier,:observations,:note,:date_de_naissance,:date_de_declaration)");
    QString CINS=QString::number(CIN);
    query.bindValue(":CIN",CINS);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":lieu_de_naissance",lieu_de_naissance);
    query.bindValue(":nom_pere",nom_pere);
    query.bindValue(":prenom_pere",prenom_pere);
    query.bindValue(":nom_dela_mere",nom_dela_mere);
    query.bindValue(":prenom_dela_mere",prenom_dela_mere);
    query.bindValue(":nationalite",nationalite);
    query.bindValue(":sexe",sexe);
    query.bindValue(":identite_de_declarant",identite_de_declarant);
    query.bindValue(":identite_de_officier",identite_de_officier);
    query.bindValue(":observations",observations);
    query.bindValue(":note",note);
    query.bindValue(":date_de_naissance",date_de_naissance);
    query.bindValue(":date_de_declaration",date_de_declaration);

    return query.exec();
}
QSqlQueryModel * naissance::afficher(){

    QSqlQueryModel * query = new QSqlQueryModel();
    query->setQuery("select * from naissance");

    query->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    query->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    query->setHeaderData(3,Qt::Horizontal,QObject::tr("lieu_de_naissance"));
    query->setHeaderData(4,Qt::Horizontal,QObject::tr("nom_pere"));
    query->setHeaderData(5,Qt::Horizontal,QObject::tr("prenom_pere"));
    query->setHeaderData(6,Qt::Horizontal,QObject::tr("nom_dela_mere"));
    query->setHeaderData(7,Qt::Horizontal,QObject::tr("prenom_dela_mere"));
    query->setHeaderData(8,Qt::Horizontal,QObject::tr("nationalite"));
    query->setHeaderData(9,Qt::Horizontal,QObject::tr("sexe"));
    query->setHeaderData(10,Qt::Horizontal,QObject::tr("identite_de_declarant"));
    query->setHeaderData(11,Qt::Horizontal,QObject::tr("identite_de_officier"));
    query->setHeaderData(12,Qt::Horizontal,QObject::tr("observations"));
    query->setHeaderData(13,Qt::Horizontal,QObject::tr("note"));
    query->setHeaderData(14,Qt::Horizontal,QObject::tr("date_de_naissance"));
    query->setHeaderData(15,Qt::Horizontal,QObject::tr("date_de_declaration"));

    return query;

}
bool naissance::supprimer(int cingiven)
{
    QSqlQuery query;

    query.prepare("Delete from naissance where CIN=:CIN");
    QString cingivenString=QString::number(cingiven);
    query.bindValue(":CIN",cingivenString);
    return query.exec();

}
bool naissance::modifier(){
    QSqlQuery query1;
    query1.prepare("UPDATE naissance set nom=:nom,prenom=:prenom,lieu_de_naissance=:lieu_de_naissance,nom_pere=:nom_pere,prenom_pere=:prenom_pere,nom_dela_mere=:nom_dela_mere,prenom_dela_mere=:prenom_dela_mere,nationalite=:nationalite,sexe=:sexe,identite_de_declarant=:identite_de_declarant,identite_de_officier=:identite_de_officier,observations=:observations,note=:note,date_de_naissance=:date_de_naissance,date_de_declaration=:date_de_declaration WHERE CIN=:CIN");

    query1.bindValue(":nom",nom);
    query1.bindValue(":prenom",prenom);
    query1.bindValue(":lieu_de_naissance",lieu_de_naissance);
    query1.bindValue(":nom_pere",nom_pere);
    query1.bindValue(":prenom_pere",prenom_pere);
    query1.bindValue(":nom_dela_mere",nom_dela_mere);
    query1.bindValue(":prenom_dela_mere",prenom_dela_mere);
    query1.bindValue(":nationalite",nationalite);
    query1.bindValue(":sexe",sexe);
    query1.bindValue(":identite_de_declarant",identite_de_declarant);
    query1.bindValue(":identite_de_officier",identite_de_officier);
    query1.bindValue(":observations",observations);
    query1.bindValue(":note",note);
    query1.bindValue(":date_de_naissance",date_de_naissance);
    query1.bindValue(":date_de_declaration",date_de_declaration);



    return (query1.exec());
}
