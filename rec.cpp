#include "rec.h"
#include "QtSql/QSqlQuery"
#include <QtDebug>
#include <QObject>
Rec::Rec()
{
id = 0; raison=""; emplacement="";
}


Rec::Rec(int id,QString raison, QString emplacement)
{this->id=id;this->raison=raison; this->emplacement=emplacement;}
int Rec::getid()    {return id;}
QString Rec::getraison()    {return raison;}
QString Rec::getemplacement()   {return  emplacement;}
void Rec::setid(int id) {this->id=id;}
void Rec::setraison(QString raison) {this->raison=raison;}
void Rec::setemplacement(QString emplacement)   {this->emplacement=emplacement;}



bool Rec::ajout()
{

    QSqlQuery query;
  QString id_string= QString::number(id);
         query.prepare("INSERT INTO rec (id, raison, emplacement) "
                       "VALUES (:id,:raison, :emplacement)");
         query.bindValue(":id",id_string);
         query.bindValue(":raison",raison);
         query.bindValue(":emplacement", emplacement);

        return query.exec();

}



bool Rec::supprimer(int)
{
    QSqlQuery query;
         query.prepare(" Delete from REC where ID=:id");
         query.bindValue(0, id);

        return query.exec();


}

QSqlQueryModel* Rec::affiche()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM Rec");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("raison"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("emplacement"));


  return  model;
}

bool Rec::modifier(int, QString, QString)
{
    QSqlQuery query;
    QString sID= QString::number(id);

    query.prepare("update Rec set raison=:raison,emplacement=:emplacement where id=:id");
    query.bindValue(":idformation", sID);
    query.bindValue(":idformateur", raison);
    query.bindValue(":dateformation",emplacement);
    return query.exec();
}
QSqlQueryModel * Rec::recherche(const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from Rec where ((ID || RAISON || EMPLACEMENT) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("raison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("emplacement "));

    return model;
}

QSqlQueryModel* Rec::triID()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM Rec ORDER BY ID ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("raison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("emplacement"));

    return model;
}
QSqlQueryModel* Rec::triEMP()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM Rec ORDER BY EMPLACEMENT ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("raison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("emplacement"));

    return model;
}

