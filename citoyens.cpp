#include "Citoyens.h"
#include "QtSql/QSqlQuery"
#include <QtDebug>
#include <QObject>
Cit::Cit()
{
idC = 0; nomC=""; prenomC="", dateC="";
}


Cit::Cit(int idC,QString nomC, QString prenomC, QString dateC)
{this->idC=idC;this->nomC=nomC; this->prenomC=prenomC;this->dateC=dateC;}
int Cit::getidC()    {return idC;}
QString Cit::getnomC()    {return nomC;}
QString Cit::getprenomC()   {return  prenomC;}
QString Cit::getdateC()   {return  dateC;}

void Cit::setidC(int idC) {this->idC=idC;}
void Cit::setnomC(QString nomC) {this->nomC=nomC;}
void Cit::setprenomC(QString prenomC) {this->prenomC=prenomC;}
void Cit::setdateC(QString dateC) {this->nomC=dateC;}

bool Cit::Cajout()
{

    QSqlQuery query;
  QString id_string= QString::number(idC);
         query.prepare("INSERT INTO cit (idc, nomc, prenomc, datec) "
                       "VALUES (:idc,:nomc, :prenomc, :datec)");
         query.bindValue(":idc",id_string);
         query.bindValue(":nomc",nomC);
         query.bindValue(":prenomc",prenomC);
         query.bindValue(":datec",dateC);

        return query.exec();

}



bool Cit::Csupprimer(int)
{
    QSqlQuery query;
         query.prepare(" Delete from CIT where IDC=:idc");
         query.bindValue(0, idC);

        return query.exec();
}

QSqlQueryModel* Cit::Caffiche()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM CIT");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomc"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenomc"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("datec"));


  return  model;
}

bool Cit::Cmodifier(int, QString, QString, QString)
{
    QSqlQuery query;
    QString sIDC= QString::number(idC);

    query.prepare("update CIT set nomc=:nomc,prenomc=:prenomc,datec=:datec where idc=:idc");
    query.bindValue(":idc", sIDC);
    query.bindValue(":nomc", nomC);
    query.bindValue(":prenomc",prenomC);
    query.bindValue(":datec",dateC);
    return query.exec();
}


QSqlQueryModel * Cit::Crecherche(const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from CIT where ((IDC || NOMC || PRENOMC) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomc"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenomc "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("datec "));

    return model;
}

QSqlQueryModel* Cit::CtriIDasc()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM CIT ORDER BY IDC ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomc"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenomc"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("datec"));

    return model;
}
QSqlQueryModel* Cit::CtriIDdesc()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM CIT ORDER BY IDC DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomc"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenomc"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("datec"));

    return model;
}

QSqlQueryModel* Cit::CtriNOMasc()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM CIT ORDER BY NOMC ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomc"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenomc"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("datec"));

    return model;
}
QSqlQueryModel* Cit::CtriNOMdesc()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM CIT ORDER BY NOMC DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomc"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenomc"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("datec"));

    return model;
}
