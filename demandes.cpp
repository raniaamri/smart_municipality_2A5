#include "demandes.h"
#include<QDebug>
demandes::demandes()
{
   id_demande=0;
}
demandes::demandes(int i,QString n,QString p,QString e)
{
    id_demande=i;
    nom=n;
    prenom=p;
    etat=e;

}

bool demandes::ajouter()
{

    QSqlQuery query;
    QString i;

     query.exec("select id_demande from demandes where id_demande = ( select max(id_demande) from demandes);");
      if (query.next()) {
            i = query.value(0).toString();
            qDebug() << i <<endl;
        }
   // QString res= QString::number(id_user);

    query.prepare("INSERT INTO demandes(ID_demande,NOM,PRENOM,etat)"
                  "VALUES (:id_demande,:nom,:prenom,:etat)");
    query.bindValue(":id_demande",(i.toInt()+1));
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":etat",etat);

    return query.exec();

}
QSqlQueryModel *demandes:: afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from demandes");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_demande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    return model;
}
bool demandes::Modifier()
{
    QSqlQuery query;
    QString i;
    query.exec("select id_demande from demandes where id_demande = ( select max(id_demande) from demandes);");
     if (query.next()) {
           i = query.value(0).toString();
           qDebug() << i <<endl;
       }
   // QString res0 =QString::number(id_demandes);
    query.prepare(" UPDATE demandes SET nom=:nom, prenom=:prenom, etat=:etat WHERE nom=:nom ");
    query.bindValue(":id_demande",i);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":etat",etat);
    return query.exec();
}
bool demandes:: supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from demandes where id_demande=:id_demande");
    query.bindValue(":id_demande",id);
    return query.exec();
}
QSqlQueryModel *demandes::sortid_up()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from demandes ORDER BY id_demande ASC ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_demande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    return model;
}
QSqlQueryModel *demandes::sortid_down()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from demandes ORDER BY id_demande DESC ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_demande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    return model;
}
QSqlQueryModel *demandes::rechercher(const QString &aux)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from demandes where ((ID_DEMANDE || PRENOM || NOM || ETAT) LIKE '%"+aux+"%')");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_demande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));

    return model;
}

