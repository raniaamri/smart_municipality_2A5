#include "cadastre.h"
#include<QDebug>
cadastre::cadastre()
{
 id_cadastre=0;
}
cadastre::cadastre(int i,QString n,QString p,float s)
{
    id_cadastre=i;
    nom=n;
    prenom=p;
    surface=s;

}

bool cadastre::ajouter()
{

    QSqlQuery query;
    QString i;

     query.exec("select id_cadastre from cadastre where id_cadastre = ( select max(id_cadastre) from cadastre);");
      if (query.next()) {
            i = query.value(0).toString();
            qDebug() << i <<endl;
        }
    QString res= QString::number(surface);

    query.prepare("INSERT INTO cadastre(id_cadastre,NOM,PRENOM,surface)"
                  "VALUES (:id_cadastre,:nom,:prenom,:surface)");
    query.bindValue(":id_cadastre",(i.toInt()+1));
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":surface",res);

    return query.exec();

}
QSqlQueryModel *cadastre:: afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from cadastre");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_cadastre"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("surface"));
    return model;
}
bool cadastre::Modifier()
{
    QSqlQuery query;
    QString i;
    query.exec("select id_cadastre from cadastre where id_cadastre = ( select max(id_cadastre) from cadastre);");
     if (query.next()) {
           i = query.value(0).toString();
           qDebug() << i <<endl;
       }
    QString res0 =QString::number(surface);
    query.prepare(" UPDATE cadastre SET nom=:nom, prenom=:prenom, surface=:surface WHERE nom=:nom ");
    query.bindValue(":id_cadastre",i);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":surface",res0);
    return query.exec();
}
bool cadastre:: supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from cadastre where id_cadastre=:id_cadastre");
    query.bindValue(":id_cadastre",id);
    return query.exec();
}
QSqlQueryModel *cadastre::sortid_up()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from cadastre ORDER BY id_cadastre ASC ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_cadastre"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("surface"));
    return model;
}
QSqlQueryModel *cadastre::sortid_down()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from cadastre ORDER BY id_cadastre DESC ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_cadastre"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("surface"));
    return model;
}

