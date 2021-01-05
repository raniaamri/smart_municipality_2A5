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
  QString surface_string= QString::number(surface);
  QString id_string= QString::number(id_cadastre);
         query.prepare("INSERT INTO cadastre (id_cadastre,NOM,PRENOM,surface) "
                       "VALUES (:id_cadastre,:nom,:prenom,:surface)");
         query.bindValue(":id_cadastre",id_string);
         query.bindValue(":nom",nom);
         query.bindValue(":prenom",prenom);
         query.bindValue(":surface",surface_string);
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
bool cadastre::Modifier(int id_cadastre,QString nom,QString prenom,float surface)
{
    QSqlQuery query;
    QString surface_string= QString::number(surface);
        QString res= QString::number(id_cadastre);
        query.prepare("update cadastre set nom=:nom, prenom=:prenom, surface=:surface where id_cadastre=:id_cadastre");
        query.bindValue(":id_cadastre", res);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":surface", surface_string);
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
QSqlQueryModel * cadastre::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from cadastre where ((ID_CADASTRE || NOM || PRENOM || SURFACE ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_cadastre"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("surface"));

    return model;
}
