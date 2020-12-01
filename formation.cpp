#include "formation.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QTime>
#include<QDateTime>
formation::formation()
{
idformation=0; idformateur=0;
}
formation::formation(int idformation,int idformateur, QDateTime dateformation, int duree)
{this->idformation=idformation;this->idformateur=idformateur; this->dateformation=dateformation;this->duree=duree;}
int formation::getidformation(){return idformation;}
int formation::getidformateur(){return idformateur;}
QDateTime formation::getdateformation(){return  dateformation;}
int formation::getduree(){return duree;}
void formation::setidformation(int idformation){this->idformation=idformation;}
void formation::setidformateur(int idformateur){this->idformateur=idformateur;}
void formation::setdateformation(QDateTime dateformation){this->dateformation=dateformation;}
void formation::setduree(int duree){this->duree=duree;}

bool formation::ajouter()
{

    QSqlQuery query;
  QString idformation_string= QString::number(idformation);
  QString idformateur_string=QString::number(idformateur);
  QString duree_string=QString::number(duree);

         query.prepare("INSERT INTO FORMATION (idformation, idformateur, dateformation,duree) "
                       "VALUES (:idformation,:idformateur, :dateformation, :duree)");
         query.bindValue(":idformation",idformation_string);
         query.bindValue(":idformateur",idformateur_string);
         query.bindValue(":dateformation", dateformation);
         query.bindValue(":duree",duree_string);

        return query.exec();

}
bool formation::supprimer(int idformation)
{
    QSqlQuery query;
         query.prepare(" Delete from formation where IDFORMATION=:idformation");
         query.bindValue(0, idformation);

        return query.exec();


}
QSqlQueryModel* formation::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM formation");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("idformation"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("idformateur"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("dateformation"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));



  return  model;
}


bool formation::modifier(int idformation, int idformateur, QDateTime dateformation, int duree)
{
    QSqlQuery query;
    QString res= QString::number(idformation);
    QString sl= QString::number(idformateur);
    QString dur= QString::number(duree);
    query.prepare("update formation set idformation=:idformation,idformateur=:idformateur,dateformation=:dateformation,duree=:duree where idformation=:idformation");
    query.bindValue(":idformation", res);
    query.bindValue(":idformateur", sl);
    query.bindValue(":dateformation",dateformation);
    query.bindValue(":duree",dur);

    return query.exec();
}
QSqlQueryModel * formation::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from formation where ((IDFORMATION || IDFORMATEUR || DATEFORMATION || DUREE ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idformation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("idformateur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dateformation "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree "));


    return model;
}
QSqlQueryModel* formation::trie()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM formation ORDER BY salaire ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idformation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("idformateur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dateformation"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));



    return model;
}
