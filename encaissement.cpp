#include "encaissement.h"
#include<QMessageBox>
#include <QDebug>
#include<QSqlQuery>
//testgit
encaissement ::encaissement()
{

    id_employe=0 ;
    methode_encaissement="";
    remarque_encaissement="";
    montant_encaissement="";


}

encaissement ::encaissement(QString methode_encaissement ,QString montant_encaissement,int id_employe,QString remarque_encaissement)
{

    this -> methode_encaissement=methode_encaissement;
    this -> montant_encaissement=montant_encaissement;
    this -> id_employe=id_employe;
    this -> remarque_encaissement=remarque_encaissement;

}

int encaissement :: get_id_employe(){return id_employe;}
QString encaissement :: get_methode_encaissement(){return methode_encaissement;}
QString encaissement :: get_remarque_encaissement(){return remarque_encaissement;}
QString encaissement :: get_montant_encaissement(){return montant_encaissement;}
bool encaissement :: ajouter()
{
   QSqlQuery query;
   query.prepare("insert into encaissement (date_encaissement,methode_encaissement,id_employe,montant_encaissement,remarque_encaissement) values(sysdate,:methode_encaissement,:id_employe,:montant_encaissement,:remarque_encaissement)");
   query.bindValue(":id_employe",id_employe);
   query.bindValue(":methode_encaissement",methode_encaissement);
   query.bindValue(":remarque_encaissement",remarque_encaissement);
   query.bindValue(":montant_encaissement",montant_encaissement);
   return query.exec();

//c est  la fonction ajouter de table encaissement
}


QSqlQueryModel *encaissement:: afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;

}
bool encaissement :: modifier()
{
   QSqlQuery query;
   query.prepare("update encaissement set id_employe=:id_employe , methode_encaissement=:methode_encaissement , remarque_encaissement=:remarque_encaissement , montant_encaissement=:montant_encaissement where code_encaissement=:code_encaissement ");
   query.bindValue(":id_employe",id_employe);
   query.bindValue(":methode_encaissement",methode_encaissement);
   query.bindValue(":remarque_encaissement",remarque_encaissement);
   query.bindValue(":montant_encaissement",montant_encaissement);
   return query.exec();
}

QSqlQueryModel *encaissement:: afficher_asc()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by code_encaissement ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;

}


QSqlQueryModel *encaissement:: afficher_dec()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by code_encaissement desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;

}

bool encaissement :: supprimer(QString code_supprimer)
{
    QSqlQuery query ;
    QString code=code_supprimer;
    query.prepare("delete from encaissement where code_encaissement='"+code+"'");
    return query.exec();

}

QSqlQueryModel *encaissement:: rechercher(QString q)
{

    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement where code_encaissement like '%"+q+"%' or methode_encaissement like '%"+q+"%' or id_employe like '%"+q+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;


}

QSqlQueryModel *encaissement:: afficher_asc_id()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by id_employe ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;

}
QSqlQueryModel *encaissement::afficher_dec_id()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by id_employe desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_asc_methode()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by methode_encaissement  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_dec_methode()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by methode_encaissement  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_asc_date()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by date_encaissement  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_dec_date()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by date_encaissement desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("méthode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employé"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remarque"));
    return model ;
}
QSqlQueryModel *encaissement:: afficher_ang()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;

}
QSqlQueryModel *encaissement::afficher_dec_date_ang()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by date_encaissement desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_asc_date_ang()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by date_encaissement  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_dec_method()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by methode_encaissement  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amunt"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_asc_method()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by methode_encaissement  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_dec_id_ang()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by id_employe desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;
}
QSqlQueryModel *encaissement::afficher_asc_id_ang()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by id_employe desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;
}
QSqlQueryModel *encaissement:: rechercher_ang(QString q)
{

    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement where code_encaissement like '%"+q+"%' or methode_encaissement like '%"+q+"%' or id_employe like '%"+q+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("methode"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;


}
QSqlQueryModel *encaissement:: afficher_asc_ang()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by code_encaissement ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;

}


QSqlQueryModel *encaissement:: afficher_dec_ang()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model-> setQuery("select * from encaissement order by code_encaissement desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("method"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("remark"));
    return model ;

}
