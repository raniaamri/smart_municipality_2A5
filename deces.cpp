#include "deces.h"

deces::deces()
{
    this->CINd=0;
    this->nomd="";
    this->prenomd="";
    this->lieu_de_naissanced="";
    this->nom_pered="";
    this->prenom_pered="";
    this->nom_dela_mered="";
    this->prenom_dela_mered="";
    this->nationalited="";
    this->sexed="";
    this->identite_de_declarantd="";
    this->identite_de_officierd="";
    this->observationsd="";
    this->noted="";
    this->date_de_naissanced=QDate::currentDate();
    this->date_de_declaration_dedeces=QDate::currentDate();
    this->lieu_de_deces="";
    this->date_de_deces=QDate::currentDate();

}
deces::deces(int CINd,QString nomd,QString prenomd,QString lieu_de_naissanced,QString nom_pered,QString prenom_pered,QString nom_dela_mered,QString prenom_dela_mered,QString nationalited,QString sexed,QString identite_de_declarantd,QString identite_de_officierd,QString observationsd,QString noted,QString lieu_de_deces,QDate date_de_naissanced,QDate date_de_declaration_dedeces,QDate date_de_deces)
{
    this->CINd=CINd;
    this->nomd=nomd;
    this->prenomd=prenomd;
    this->lieu_de_naissanced=lieu_de_naissanced;
    this->nom_pered=nom_pered;
    this->prenom_pered=prenom_pered;
    this->nom_dela_mered=nom_dela_mered;
    this->prenom_dela_mered=prenom_dela_mered;
    this->nationalited=nationalited;
    this->sexed=sexed;
    this->identite_de_declarantd=identite_de_declarantd;
    this->identite_de_officierd=identite_de_officierd;
    this->observationsd=observationsd;
    this->noted=noted;
    this->date_de_naissanced=date_de_naissanced;
    this->date_de_declaration_dedeces=date_de_declaration_dedeces;
    this->date_de_deces=date_de_deces;
    this->lieu_de_deces=lieu_de_deces;
}
bool deces::ajouter_deces(){

    QSqlQuery query;

    query.prepare("insert into naissance (CINd,nomd,prenomd,lieu_de_naissanced,nom_pered,prenom_pered,nom_dela_mered,prenom_dela_mered,nationalited,sexed,identite_de_declarantd,identite_de_officierd,observationsd,noted,date_de_naissanced,date_de_declarationd,date_de_deces,lieu_de_deces)"
                  "values(:CINd,:nomd,:prenomd,:lieu_de_naissanced,:nom_pered,:prenom_pered,:nom_dela_mered,:prenom_dela_mered,:nationalited,:sexed,:identite_de_declarantd,:identite_de_officierd,:observationsd,:noted,:date_de_naissanced,:date_de_declarationd,:date_de_deces,:lieu_de_deces)");
    QString CINSd=QString::number(CINd);
    query.bindValue(":CINd",CINSd);
    query.bindValue(":nomd",nomd);
    query.bindValue(":prenomd",prenomd);
    query.bindValue(":lieu_de_naissanced",lieu_de_naissanced);
    query.bindValue(":nom_pered",nom_pered);
    query.bindValue(":prenom_pered",prenom_pered);
    query.bindValue(":nom_dela_mered",nom_dela_mered);
    query.bindValue(":prenom_dela_mered",prenom_dela_mered);
    query.bindValue(":nationalited",nationalited);
    query.bindValue(":sexed",sexed);
    query.bindValue(":identite_de_declarantd",identite_de_declarantd);
    query.bindValue(":identite_de_officierd",identite_de_officierd);
    query.bindValue(":observationsd",observationsd);
    query.bindValue(":noted",noted);
    query.bindValue(":date_de_naissanced",date_de_naissanced);
    query.bindValue(":date_de_declaration_dedeces",date_de_declaration_dedeces);
    query.bindValue(":date_de_deces",date_de_deces);
    query.bindValue(":lieu_de_deces",lieu_de_deces);


    return query.exec();
}
QSqlQueryModel * deces::afficher_deces(){

    QSqlQueryModel * query = new QSqlQueryModel();
    query->setQuery("select * from deces");
    query->setHeaderData(0,Qt::Horizontal,QObject::tr("CINd"));
    query->setHeaderData(1,Qt::Horizontal,QObject::tr("Nomd"));
    query->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenomd"));
    query->setHeaderData(3,Qt::Horizontal,QObject::tr("lieu_de_naissanced"));
    query->setHeaderData(4,Qt::Horizontal,QObject::tr("nom_pered"));
    query->setHeaderData(5,Qt::Horizontal,QObject::tr("prenom_pered"));
    query->setHeaderData(6,Qt::Horizontal,QObject::tr("nom_dela_mered"));
    query->setHeaderData(7,Qt::Horizontal,QObject::tr("prenom_dela_mered"));
    query->setHeaderData(8,Qt::Horizontal,QObject::tr("nationalited"));
    query->setHeaderData(9,Qt::Horizontal,QObject::tr("sexed"));
    query->setHeaderData(10,Qt::Horizontal,QObject::tr("identite_de_declarantd"));
    query->setHeaderData(11,Qt::Horizontal,QObject::tr("identite_de_officierd"));
    query->setHeaderData(12,Qt::Horizontal,QObject::tr("observationsd"));
    query->setHeaderData(13,Qt::Horizontal,QObject::tr("noted"));
    query->setHeaderData(14,Qt::Horizontal,QObject::tr("date_de_naissanced"));
    query->setHeaderData(15,Qt::Horizontal,QObject::tr("date_de_declaration_dedeces"));
    query->setHeaderData(16,Qt::Horizontal,QObject::tr("date_de_deces"));
    query->setHeaderData(17,Qt::Horizontal,QObject::tr("lieu_de_deces"));

    return query;

}
bool deces::supprimer_deces(int cingivend)
{
    QSqlQuery query;

    query.prepare("Delete from deces where CINd=:CINd");
    QString cingivenStringd=QString::number(cingivend);
    query.bindValue(":CINd",cingivenStringd);
    return query.exec();

}
bool deces::modifier_deces(){
    QSqlQuery query1;
    query1.prepare("UPDATE deces set nomd=:nomd,prenomd=:prenomd,lieu_de_naissanced=:lieu_de_naissanced,nom_pered=:nom_pered,prenom_pered=:prenom_pered,nom_dela_mered=:nom_dela_mered,prenom_dela_mered=:prenom_dela_mered,nationalited=:nationalited,sexed=:sexed,identite_de_declarantd=:identite_de_declarantd,identite_de_officierd=:identite_de_officierd,observationsd=:observationsd,noted=:noted,date_de_naissanced=:date_de_naissanced,date_de_declaration_dedeces=:date_de_declaration_dedeces,date_de_deces=:date_de_deces,lieu_de_deces=:lieu_de_deces WHERE CINd=:CINd");
    query1.bindValue(":CINd",CINd);
    query1.bindValue(":nomd",nomd);
    query1.bindValue(":prenomd",prenomd);
    query1.bindValue(":lieu_de_naissanced",lieu_de_naissanced);
    query1.bindValue(":nom_pered",nom_pered);
    query1.bindValue(":prenom_pered",prenom_pered);
    query1.bindValue(":nom_dela_mered",nom_dela_mered);
    query1.bindValue(":prenom_dela_mered",prenom_dela_mered);
    query1.bindValue(":nationalited",nationalited);
    query1.bindValue(":sexed",sexed);
    query1.bindValue(":identite_de_declarantd",identite_de_declarantd);
    query1.bindValue(":identite_de_officierd",identite_de_officierd);
    query1.bindValue(":observationsd",observationsd);
    query1.bindValue(":noted",noted);
    query1.bindValue(":date_de_naissanced",date_de_naissanced);
    query1.bindValue(":date_de_declaration_dedeces",date_de_declaration_dedeces);
    query1.bindValue(":date_de_deces",date_de_deces);
    query1.bindValue(":lieu_de_deces",lieu_de_deces);



    return (query1.exec());
}

