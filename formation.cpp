#include "formation.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
formation::formation()
{
idformation=0; idformateur=0; dateformation="";
}

formation::formation(int idformation,int idformateur, QString dateformation)
{this->idformation=idformation;this->idformateur=idformateur; this->dateformation=dateformation;}
int formation::getidformation(){return idformation;}
int formation::getidformateur(){return idformateur;}
QString formation::getdateformation(){return  dateformation;}
void formation::setidformation(int idformation){this->idformation=idformation;}
void formation::setidformateur(int idformateur){this->idformateur=idformateur;}
void formation::setdateformation(QString dateformation){this->dateformation=dateformation;}

bool formation::ajouter()
{

    QSqlQuery query;
  QString idformation_string= QString::number(idformation);
  QString idformateur_string=QString::number(idformateur);
         query.prepare("INSERT INTO FORMATION (idformation, idformateur, dateformation) "
                       "VALUES (:idformation,:idformateur, :dateformation)");
         query.bindValue(":idformation",idformation_string);
         query.bindValue(":idformateur",idformateur_string);
         query.bindValue(":dateformation", dateformation);

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


  return  model;
}


bool formation::modifier(int idformation, int idformateur, QString dateformation)
{
    QSqlQuery query;
    QString res= QString::number(idformation);
    QString sl= QString::number(idformateur);
    query.prepare("update formation set idformation=:idformation,idformateur=:idformateur,dateformation=:dateformation where idformation=:idformation");
    query.bindValue(":idformation", res);
    query.bindValue(":idformateur", sl);
    query.bindValue(":dateformation",dateformation);
    return query.exec();
}
QSqlQueryModel * formation::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from formation where ((IDFORMATION || IDFORMATEUR || DATEFORMATION) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idformation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("idformateur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dateformation "));

    return model;
}
QSqlQueryModel* formation::trie()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM formation ORDER BY salaire ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idformation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("idformateur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dateformation"));

    return model;
}
