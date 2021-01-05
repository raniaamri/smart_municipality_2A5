#include "equipement.h"
#include <QMessageBox>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

equipement::equipement()
{
ID_E=0;
NOM="";
REFERENCE="";
}


equipement::equipement(int id,QString nom,QString reference)
{
ID_E=id;
NOM=nom;
REFERENCE=reference;
}

int equipement::getID_E()
{return ID_E;}

QString equipement::get_NOM()
{return NOM;}


QString equipement::get_REFERENCE()
{return REFERENCE;}


void equipement::setid_e(int id_e) {this->ID_E=id_e;}
void equipement::setnom(QString nom) {this->NOM=nom;}
void equipement::setreference(QString reference) {this->REFERENCE=reference;}







bool equipement::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(ID_E);
    query.prepare("INSERT INTO  equipement(ID_E,NOM,REFERENCE) VALUES(:ID_E, :NOM,  :REFERENCE)");
    query.bindValue(":ID_E",res);
    query.bindValue(":NOM",NOM);
    query.bindValue(":REFERENCE",REFERENCE);

    return query.exec();
}



QSqlQueryModel * equipement::Afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from equipement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFERENCE"));


    return model;
}



bool equipement::modifier(int, QString, QString)
{
    QSqlQuery query;
    QString Mid= QString::number(ID_E);

    query.prepare("update equipement set nom=:nom,reference=:reference where id_e=:id_e");
    query.bindValue(":id_e", Mid);
    query.bindValue(":nom", NOM);
    query.bindValue(":reference", REFERENCE);
    return query.exec();
}


QSqlQueryModel * equipement::afficher_equipement()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select ID_E from equipement");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_E"));


            return model;


}


bool equipement::supprimer(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("delete from equipement where ID_E= :ID_E ");
    query.bindValue(":ID_E", res);

    return    query.exec();
}




QSqlQueryModel * equipement::recherche(const QString &ress)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from equipement where ((ID_E || NOM|| REFERENCE) LIKE '%"+ress+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_e"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference "));

    return model;
}






QSqlQueryModel *  equipement::trier(const QString &critere, const QString &mode )
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from equipement order by "+critere+" "+mode+"");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_E"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("REFERENCE"));
    return model;
}







/*QTextStream out(&strStream);
//QSqlQuery Query;
//Query.prepare("select * from equipement");
//Query.exec();
//const int rowCount = Query.size();
const int columnCount = Query.record().count();

out <<  "<html>\n"
    "<head>\n"
   // "<meta Content=\"Text/html; charset=Windows-1251\">\n"
  <<   QString ( " <title>% liste des demandes </title> \ n " ). arg ( " demandes " )
    <<  "</head>\n"
    "<body bgcolor=#ffffff link=#5000A0>\n"
    "<center><table border=1 cellspacing=0 cellpadding=2>\n"
// " <center><img src = 'C:/Users/soulayma/Desktop/test.png' width = '100' height = '100'></center>  "
                            " <h1><center> Liste des demandes</center> </h1> ";

// headers
out << "<thead><tr bgcolor=#f0f0f0>";
for (int column = 0; column < columnCount; column++)
  out << QString("<th>%1</th>").arg(Query.record().fieldName(column));
out << "</tr></thead>\n";

while (Query.next()) {
  out << "<tr>";
  for (int column = 0; column < columnCount; column++) {
    QString data = Query.value(column).toString();
    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
  }
  out << "</tr>\n";
}

out <<  "</table></center>\n"
    "</body>\n"
    "</html>\n";

QTextDocument * document = new  QTextDocument ();
                      document-> setHtml (strStream);

                      QPrinter QPrinter;

                      QPrintDialog * dialog = new  QPrintDialog (& QPrinter, NULL );
                      if (dialog-> exec () == QDialog::Accepted) {
                          document-> print (& QPrinter);

                          export pdf;

*/

