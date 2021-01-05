#include "vehicule.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

vehicule::vehicule()
{
ID_V=0;
NOM="";
REFERENCE="";
}


vehicule::vehicule(int id_v,QString nom,QString reference)
{
ID_V=id_v;
NOM=nom;
REFERENCE=reference;
}


int vehicule::getID_V()
{ return ID_V;}
QString vehicule::get_NOM()
{return NOM;}
QString vehicule::get_REFERENCE()
{return REFERENCE;}


void vehicule::setid_v(int id_v) {this->ID_V=id_v;}
void vehicule::setnom(QString nom) {this->NOM=nom;}
void vehicule::setreference(QString reference) {this->REFERENCE=reference;}









bool vehicule::ajouter()
{
    QSqlQuery query;
    QString ress=QString::number(ID_V);
    query.prepare("INSERT INTO  vehicule(ID_V,NOM,REFERENCE) VALUES(:ID_V, :NOM, :REFERENCE)");
    query.bindValue(":ID_V",ress);
    query.bindValue(":NOM",NOM);
    query.bindValue(":REFERENCE",REFERENCE);

    return query.exec();
}



QSqlQueryModel * vehicule::Afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from vehicule");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFERENCE"));


    return model;
}

QSqlQueryModel * vehicule::Afficher_vehicule()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from vehicule");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    return model;


}

bool vehicule::supprimer(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("delete from vehicule where ID_V= :ID_V ");
    query.bindValue(":ID_V", res);

    return    query.exec();
}





bool vehicule::modifier(int, QString, QString)
{
    QSqlQuery query;
    QString Mid= QString::number(ID_V);

    query.prepare("update vehicule set nom=:nom,reference=reference where id_v=:id_v");
    query.bindValue(":id_v", Mid);
    query.bindValue(":nom", NOM);
    query.bindValue(":reference",REFERENCE);
    return query.exec();
}



void vehicule::chercher()
{
    QSqlQuery query1;
    query1.prepare("SELECT nom,reference FROM equipement WHERE id_v =:id_v");
    query1.bindValue(":id_v",ID_V);
    query1.exec();
    while(query1.next())
    {
    NOM = query1.value(0).toString();
    REFERENCE = query1.value(0).toString();

    }
    }



QSqlQueryModel * vehicule:: recherche(int etat,QString champ,QString valeur)
{
    QSqlQueryModel * model=new QSqlQueryModel();

    QSqlQuery query;
    if(etat==0)
   { query.prepare("SELECT * FROM vehicule WHERE ("+champ+" LIKE :valeur) order by id_v");}
    else   { query.prepare("SELECT * FROM vehicule WHERE ("+champ+" LIKE :valeur) order by id_v desc");}
    valeur="%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_V"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference"));
    return model;

}










