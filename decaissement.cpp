 #include "decaissement.h"
#include<QMessageBox>
#include <QDebug>
#include<QSqlQuery>
decaissement :: decaissement()
{

    id_em_dec=0 ;
    methode_decaissement="";
    remarque_decaissement="";
    montant_decaissement="";


}

decaissement ::decaissement(QString methode_decaissement ,QString montant_decaissement,int id_em_dec,QString remarque_decaissement)
{

    this -> methode_decaissement=methode_decaissement;
    this -> montant_decaissement=montant_decaissement;
    this -> id_em_dec=id_em_dec;
    this -> remarque_decaissement=remarque_decaissement;

}

int decaissement :: get_id_em_dec(){return id_em_dec;}
QString decaissement :: get_methode_decaissement(){return methode_decaissement;}
QString decaissement :: get_remarque_decaissement(){return remarque_decaissement;}
QString decaissement :: get_montant_decaissement(){return montant_decaissement;}
bool decaissement :: ajouter()
{
   QSqlQuery query;
   query.prepare("insert into decaissement (date_decaissement,methode,id_employe,montant_decaissement,remarque_decaissement) values(sysdate,:methode_decaissement,:id_em_dec,:montant_decaissement,:remarque_decaissement)");
   query.bindValue(":id_em_dec",id_em_dec);
   query.bindValue(":methode_decaissement",methode_decaissement);
   query.bindValue(":remarque_decaissement",remarque_decaissement);
   query.bindValue(":montant_decaissement",montant_decaissement);
   return query.exec();

//c est  la fonction ajouter de table decaissement
}


QSqlQueryModel *decaissement:: afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;

}
bool decaissement :: modifier()
{
   QSqlQuery query;
   query.prepare("update decaissement set id_employe=:id_em_dec , methode=:methode_decaissement , remarque_decaissement=:remarque_decaissement , montant_decaissement=:montant_decaissement where code_decaissement=:code_decaissement ");
   query.bindValue(":id_em_dec",id_em_dec);
   query.bindValue(":methode_decaissement",methode_decaissement);
   query.bindValue(":remarque_decaissement",remarque_decaissement);
   query.bindValue(":montant_decaissement",montant_decaissement);
   return query.exec();


}

QSqlQueryModel *decaissement:: afficher_asc()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement order by code_decaissement  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;

}


QSqlQueryModel *decaissement:: afficher_dec()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement order by code_decaissement desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;

}
bool decaissement :: supprimer(QString code_supprimer)
{
    QSqlQuery query ;
    QString code=code_supprimer;
    query.prepare("delete from decaissement where code_decaissement='"+code+"'");
    return query.exec();

}

QSqlQueryModel *decaissement:: rechercher(QString q)
{

    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement where code_decaissement like '%"+q+"%' or methode like '%"+q+"%' or id_employe like '%"+q+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;


}
QSqlQueryModel *decaissement:: afficher_asc_id()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement order by id_employe  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
return model ;
}
QSqlQueryModel *decaissement::afficher_dec_id()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement order by id_employe desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
return model ;
}
QSqlQueryModel *decaissement::afficher_asc_methode()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement order by methode ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
return model ;
}
QSqlQueryModel *decaissement::afficher_dec_methode()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement order by methode desc  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
return model ;
}
QSqlQueryModel *decaissement::afficher_asc_date()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement order by date_decaissement  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
return model ;
}
QSqlQueryModel *decaissement::afficher_dec_date()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from decaissement order by date_decaissement desc  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("employé"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
return model ;
}
