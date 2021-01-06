#include"statequi.h"
#include"lestat.h"
#include"vehicule.h"
#include"email.h"
#include"equipement.h"
#include"arduino.h"
#include"stat2.h"
#include"cadastre.h"
#include"demandes.h"
#include"encaissement.h"
#include "ressources_humaines.h"
#include "ui_ressources_humaines.h"
#include "statistique.h"
#include "ui_statistique.h"
#include "employe.h"
#include"deces.h"
#include"naissance.h"
#include "formation.h"
#include"rec.h"
#include"citoyens.h"
#include"decaissement.h"
#include <QMessageBox>
#include <QComboBox>
#include <QTabWidget>
#include <QObject>
#include <QSqlTableModel>
#include <QPrinter>
#include <QPrintDialog>
#include<QPropertyAnimation>
#include<QEasingCurve>
#include<QParallelAnimationGroup>
#include<QGraphicsOpacityEffect>
#include<QSound>
#include <QtMultimedia>
#include<QWidget>
#include<QMediaPlayer>
#include<QDate>
#include <QTextDocument>
#include <QTextStream>
#include<QMenu>
#include<QDialogButtonBox>
#include <QFile>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include<QBarSet>

Ressources_Humaines::Ressources_Humaines(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ressources_Humaines)
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint );



/*controle de saisie*/
ui->le_id->setValidator(new QIntValidator(100, 999, this));
ui->le_id_supp->setValidator(new QIntValidator(100, 999, this));
ui->le_supprimerformation->setValidator(new QIntValidator(100, 999, this));
ui->le_salaire->setValidator(new QIntValidator(100,99999, this));
ui->le_nom->setMaxLength(10);
ui->le_prenom->setMaxLength(10);
ui->le_idformation->setValidator(new QIntValidator(100,999, this));
ui->le_duree->setValidator(new QIntValidator(1,10, this));
//affichage tab
ui->tabdemandes->setModel(dem.afficher());
ui->tabcadastre->setModel(ca.afficher());
/*setting up the widget page + les icones*/
ui->main_stacked->setCurrentIndex(2);
ui->side_stacked->setCurrentIndex(0);
ui->stackedWidget_2->setCurrentIndex(0);
ui->pushButton_7->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-change-userclicked-64.png"));
ui->pushButton_8->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-file-64.png"));
ui->pushButton_11->setIcon(QIcon("C:/Users/user/Documents/smartM/icons/16x16/cil-arrow-left.png"));
ui->retour_menu->setIcon(QIcon("C:/Users/user/Documents/smartM/icons/16x16/cil-arrow-left.png"));
ui->encaissement_pb_2->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/encaissementOUI.png"));
ui->decaissement_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/decaissementNON.png"));
ui->stat_encaissement->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/statistiques.png"));
ui->pushButton_15->setIcon(QIcon("C:/Users/user/Documents/smartM/icons/16x16/cil-arrow-left.png"));
ui->retourmenu->setIcon(QIcon("C:/Users/user/Documents/smartM/icons/16x16/cil-arrow-left.png"));
ui->RRETOUR->setIcon(QIcon("C:/Users/user/Documents/smartM/icons/16x16/cil-arrow-left.png"));
ui->recla_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/reclaOUI.png"));
ui->cit_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/citoy_NON.png"));
ui->naissanceside->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/naissanceOUI.png"));
ui->decesside->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/deathNON.png"));
ui->demande->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/demandeOUI.png"));
ui->cadastre->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/cadastreNON.png"));
ui->toV->setIcon(QIcon("C:/Users/user/Documents/sm_integration/iconet/vehiculeOFF.png"));
ui->toE->setIcon(QIcon("C:/Users/user/Documents/sm_integration/iconet/EONN.png"));
ui->backA->setIcon(QIcon("C:/Users/user/Documents/smartM/icons/16x16/cil-arrow-left.png"));

/*auto movie = new QMovie(this);
movie->setFileName("C:/Users/user/Documents/smartMunicipality/iconet/Mfinnances.gif");
connect(movie, &QMovie::frameChanged, [=]{
 ui->menu_fn->setIcon(movie->currentPixmap());
});
movie->start();

auto movie2 = new QMovie(this);
movie2->setFileName("C:/Users/user/Desktop/giphy.gif");
connect(movie2, &QMovie::frameChanged, [=]{
 ui->menu_rh->setIcon(movie2->currentPixmap());
    movie2->setScaledSize(this->size());

});
movie2->start();
*/
int ret=A.connect_arduino();
   switch(ret)
   {
   case(0):qDebug()<<"arduino is available and connected to :"<<A.getarduino_port_name();
       break;
   case(1):qDebug()<<"arduino is available but not connected to :"<<A.getarduino_port_name();
       break;
   case(-1):qDebug()<<"arduino is not available";
   }
   QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label1()));

}


void Ressources_Humaines::update_label1()
{


temp=QString::fromStdString(A.read_from_arduino().toStdString());
if(temp.length()>=4)
{
    QStringRef humidity(&temp,2,2);

    QStringRef temperature(&temp,0,2);
    int tempe=temperature.toInt();
    int hum=humidity.toInt();
    qDebug()<<"temperature="<<temperature;
    qDebug()<<"humidity="<<humidity;
    QSqlQuery qry;
    qry.prepare("insert into historique_temp values(sysdate,:tempe ,:hum)");
    qry.bindValue(":tempe",tempe);
    qry.bindValue(":hum",hum);
    qry.exec();

    ui->ard->setModel(A.afficher());
    ui->ard->setColumnWidth(0,180);
    ui->ard->setColumnWidth(1,180);

    ui->ard->setColumnWidth(2,180);


   if(hum>70)
   {

       QMessageBox::warning(nullptr, QObject::tr("erreur"),
                         QObject::tr("Humidité a depassé 70.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
   }
}
}





void Ressources_Humaines::update_label(){
data=A.read_from_arduino();
if(data=="1") ui->labelArduino/*arduino*/->setText("ON");
else if (data=="0") ui->labelArduino/*arduino*/->setText("OFF");
}

Ressources_Humaines::~Ressources_Humaines()
{

    delete ui;
}





void Ressources_Humaines::on_ajouter_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();

    /*CRUD AJOUTER*/
    int id=ui->le_id->text().toInt();
    int salaire=ui->le_salaire->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
     QDate date_de_naissance=ui->dateEdit->date();
 Employe E(id,salaire,nom,prenom,date_de_naissance);
 bool test=E.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tableView->setModel(E.afficher());
 }
 else
 {
         const int DeltaPos = 10;

         QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
         animation->setDuration(500);

         if (ui->stackedWidget_2->currentIndex() == 0) {
            /* Animation Ressources_Humaines*/
             int oldX = pos().x();
             animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(10)));
             animation->setKeyValueAt(0.0, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.1, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.2, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.3, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.4, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.5, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.6, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.7, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.8, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.9, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(1.0, QPoint(oldX, pos().y()));
         } else {
             int oldY = pos().y();
             animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(10)));
             animation->setKeyValueAt(0.0, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.1, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.2, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.3, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.4, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.5, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.6, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.7, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.8, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.9, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(1.0, QPoint(pos().x(), oldY));
         }
         animation->start(QAbstractAnimation::DeleteWhenStopped);
         /*message d'erreur*/
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}
}

void Ressources_Humaines::on_pushButton_3_clicked()
{

        /*sound */

    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();
        /*CRUD SUPPRIMER*/
    Employe E1; E1.setid(ui->le_id_supp->text().toInt());
    bool test=E1.supprimer(E1.getid());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tableView->setModel(E.afficher());
    ui->comboBox_2->setModel(E.afficher_employe());
    ui->combo_idemp_decaissement->setModel((E.afficher_employe()));
    }
    else{
        /*message d'erreur*/

        msgBox.setText("Echec de suppression");
        msgBox.exec();
    }

}


void Ressources_Humaines::on_pushButton_7_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();

    /*setting up page employe*/
    ui->stackedWidget_2->setCurrentIndex(0);

    /*chnaging icons*/
    ui->pushButton_7->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-change-userclicked-64.png"));
        ui->pushButton_8->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-file-64.png"));

       /* fade in effect lel stacked widget*/
        QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
        ui->stackedWidget_2->setGraphicsEffect(eff);
        QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
        a->setDuration(350);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        a->start(QPropertyAnimation::DeleteWhenStopped);


}

void Ressources_Humaines::on_pushButton_8_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();

    /*setting up page formation*/
    ui->stackedWidget_2->setCurrentIndex(1);

    /*chnaging icons*/
    ui->pushButton_7->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-change-user-64.png"));
    ui->pushButton_8->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-fileclicked-64.png"));

    ui->comboBox_2->setModel(E.afficher_employe());/*aadi el id lel combobox*/

    /*fade in animation*/
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    ui->stackedWidget_2->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(350);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);



}




void Ressources_Humaines::on_modifier_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();

    /* CRUD MODIFIER*/

    int id = ui->le_id->text().toInt();
    QString nom = ui->le_nom->text();
    QString prenom= ui->le_prenom->text();
    int salaire= ui->le_salaire->text().toInt();
    QDate date_de_naissance = ui->dateEdit->date();
    Employe E(id,salaire,nom,prenom,date_de_naissance) ;
    bool test =E.modifier(id,salaire,nom,prenom,date_de_naissance);
    if(test)
    {ui->tableView->setModel(E.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier un employe"),
                                 QObject::tr("employe  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un employe"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}



void Ressources_Humaines::on_le_id_search_textChanged(const QString &arg1)
{
/*metier recherche*/

        if(ui->le_id_search->text() == "")
            {
                ui->tableView->setModel(E.afficher());
            }
            else
            {
                 ui->tableView->setModel(E.rechercher(ui->le_id_search->text()));
            }

}


void Ressources_Humaines::on_pushButton_9_clicked()
{
    /*metier tri*/

    QString critere=ui->comboBox->currentText();
        QString mode;
        if (ui->checkBox->checkState()==false)
    {
             mode="DESC";
    }
         else if(ui->checkBox_2->checkState()==false)
         {
             mode="ASC";
         }
    ui->tableView->setModel(E.trie(critere,mode));
}











void Ressources_Humaines::on_pushButton_10_clicked()
{
    /* faragh lineEdits kol*/
    ui->le_id->setText("");
    ui->le_prenom->setText("");
    ui->le_nom->setText("");
    ui->le_salaire->setText("");
    ui->le_id_supp->setText("");


}


void Ressources_Humaines::on_pb_ajouterformation_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();

    /*CRUD AJOUTER*/
    int idformation=ui->le_idformation->text().toInt();
   /*int idformateur=ui->le_idformateur->text().toInt();*/
    QDateTime dateformation=ui->dateTimeEdit->dateTime();
    int idformateur= ui->comboBox_2->currentText().toInt();
    int duree=ui->le_duree->text().toInt();
 formation F(idformation,idformateur,dateformation,duree);
 bool test=F.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tableView_2->setModel(F.afficher());
     ui->le_idformation->setText("");

 }
 else

     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}



void Ressources_Humaines::on_pb_modifierformation_clicked()
{
    /*CRUD MODIFIER*/
    int idformation = ui->le_idformation->text().toInt();
    int idformateur= ui->comboBox_2->currentText().toInt();
    QDateTime dateformation= ui->dateTimeEdit->dateTime();
    int duree= ui->le_duree->text().toInt();
    formation F(idformation,idformateur,dateformation,duree) ;
    bool test =F.modifier(idformation,idformateur,dateformation,duree);
    if(test)
    {ui->tableView_2->setModel(F.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier une formationn"),
                                 QObject::tr("formation  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une formation"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_le_searchformation_textChanged(const QString &arg1)
{
    /* METIER RECHERCHE*/
    if(ui->le_searchformation->text() == "")
        {
            ui->tableView_2->setModel(F.afficher());
        }
        else
        {
             ui->tableView_2->setModel(F.rechercher(ui->le_searchformation->text()));
        }
}

void Ressources_Humaines::on_pb_supprimerformation_clicked()
{
    /*CRUD SUPPRIMER*/

    formation F1; F1.setidformation(ui->le_supprimerformation->text().toInt());
    bool test=F1.supprimer(F1.getidformation());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tableView_2->setModel(F.afficher());

    }
    else{
        msgBox.setText("Echec de suppression");
        msgBox.exec();
    }
}




void Ressources_Humaines::on_pushButton_2_clicked()
{
    /*select from table w aadi lel lineEdit*/
    int row=ui->tableView->selectionModel()->currentIndex().row();
           QString id=ui->tableView->model()->index(row,0).data().toString();
          /* QString idformateur=ui->tableView_2->model()->index(row,1).data().toString();*/
           QString salaire=ui->tableView->model()->index(row,1).data().toString();
           QString nom=ui->tableView->model()->index(row,2).data().toString();
           QString prenom=ui->tableView->model()->index(row,3).data().toString();
           QDate date_de_naissance=ui->tableView->model()->index(row,4).data().toDate();

           if(row==-1)
           {
               QMessageBox ::information(nullptr,QObject::tr("selectionner un employe"),
                                                 QObject::tr("aucune selection.\n"
                                                     "click ok to exit"),QMessageBox::Ok);
           }
           else
           {
               ui->le_id->setText(id);
               ui->le_salaire->setText(salaire);
               ui->le_nom->setText(nom);
               ui->le_prenom->setText(prenom);
               ui->dateEdit->setDate(date_de_naissance);

           }
}

void Ressources_Humaines::on_export_2_clicked()
{
        /*impression pdf*/

        {
            QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tableView->model()->rowCount();
                    const int columnCount =ui->tableView->model()->columnCount();

                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("employe")
                            <<  "</head>\n"
                            "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                                "<img src='C:/Users/user/Documents/Ressources_Humaines/icons/logo.jpg' width='100' height='100'>\n"
                                "<h1>Liste des employes</h1>"



                                "<table border=1 cellspacing=0 cellpadding=2>\n";


                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tableView->isColumnHidden(column)) {
                                       QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";

                           QTextDocument *document = new QTextDocument();
                           document->setHtml(strStream);

                           QPrinter printer;

                           QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                           if (dialog->exec() == QDialog::Accepted) {
                               document->print(&printer);
                        }
        }


}

void Ressources_Humaines::on_pushButton_12_clicked()
{
    /*METIER TRI*/
    QString critere=ui->combo_boxtri->currentText();
        QString mode;
         if (ui->cbdsc->checkState()==false)
    {
             mode="DESC";
    }
         else if(ui->cbasc->checkState()==false)
         {
             mode="ASC";
         }
    ui->tableView_2->setModel(F.trie(critere,mode));
}

void Ressources_Humaines::on_pushButton_6_clicked()
{
    /*IMPRESSION PDF*/
    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView_2->model()->rowCount();
                const int columnCount =ui->tableView_2->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("formation")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                            "<img src='C:/Users/user/Documents/Municipality_Project/icons/logo.jpg' width='100' height='100'>\n"
                            "<h1>Liste des formations</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableView_2->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView_2->isColumnHidden(column)) {
                                   QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);
                    }
    }

}

void Ressources_Humaines::on_pushButton_11_clicked()
{
    ui->main_stacked->setCurrentIndex(0);
    ui->side_stacked->setCurrentIndex(0);
}

void Ressources_Humaines::on_pushButton_clicked()
{
    close();
}




void Ressources_Humaines::on_pushButton_4_clicked()
{
    if (Ressources_Humaines::isMaximized())
           showNormal();

        else
         showMaximized();

    }

void Ressources_Humaines::on_pushButton_5_clicked()
{
    Ressources_Humaines::showMinimized();
}

void Ressources_Humaines::on_menu_rh_clicked()
{
    ui->main_stacked->setCurrentIndex(1);
    ui->side_stacked->setCurrentIndex(1);
}

void Ressources_Humaines::on_encaissement_pb_clicked()
{
    int code_encaissement=ui->code_encaissement->text().toInt() ;
    int id_employe=ui->combo_idemp_encaissement->currentText().toInt();
    QString methode_encaissement=ui->combo_mehode_encaissement->currentText();
    QString remarque_encaissement=ui->remarque_encaissement->text();
    QString montant_encaissement=ui->montant_encaissement->text();
    encaissement en(code_encaissement,methode_encaissement, montant_encaissement ,id_employe , remarque_encaissement);
    bool test=en.ajouter();
    if(ui->code_encaissement->text().isEmpty()||ui->comboBox->currentText()=="choix id"||ui->code_encaissement->text().contains(QRegExp("^[1-9]"))==0||ui->montant_encaissement->text().isEmpty()||ui->combo_mehode_encaissement->currentText()=="choix")
    {QMessageBox::warning(nullptr, QObject::tr("erreur"),
                              QObject::tr("verifier les champs.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);}
    else{
    if(test)
    {
       ui->tabe_encaissement->setModel(en.afficher());
       QMessageBox::information(nullptr, QObject::tr("Ajouter encaissement"),
       QObject::tr("encaissement ajoutée.\n"
       "Click Cancel to exit."), QMessageBox::Cancel);

    }
    }
}

void Ressources_Humaines::on_supprimer_encaissement_clicked()
{
    int row=ui->tabe_encaissement->selectionModel()->currentIndex().row();
    QString code_supprimer=ui->tabe_encaissement->model()->index(row,0).data().toString();
    bool test=en.supprimer(code_supprimer);
    if(row==-1)
    { QMessageBox::critical(nullptr, QObject::tr("Supprimer"),
                            QObject::tr("Erreur selectionnez visite que vous voulez le supprimer!.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {
    if(test)
    {
        ui->tabe_encaissement->setModel(en.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                    QObject::tr("encaissement supprimé.\n"
                                "Click Cancel" ),QMessageBox::Cancel);
    }
    }
}

void Ressources_Humaines::on_menu_fn_clicked()
{
    ui->main_stacked->setCurrentIndex(1);
    ui->side_stacked->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void Ressources_Humaines::on_chercher_encaissement_textChanged(const QString &arg1)
{
    if(ui->chercher_encaissement->text() == "")
        {
            ui->tabe_encaissement->setModel(en.afficher());
        }
        else
        {
             ui->tabe_encaissement->setModel(en.rechercher(ui->chercher_encaissement->text()));
        }
}

void Ressources_Humaines::on_trier_encaissement_clicked()
{
    /*METIER TRI*/
    QString critere=ui->combobox_tri_encaissement->currentText();
        QString mode;
         if (ui->ASC_encaissement->checkState()==false)
    {
             mode="DESC";
    }
         else if(ui->DESC_encaissement->checkState()==false)
         {
             mode="ASC";
         }
    ui->tabe_encaissement->setModel(en.trie(critere,mode));
}

void Ressources_Humaines::on_stat_encaissement_clicked()
{
    stat=new statistique(this);
    stat->show();
}

void Ressources_Humaines::on_decaissement_pb_valider_clicked()
{
    int code_decaissement=ui->code_decaissement->text().toInt() ;
   int id_em_dec=ui->combo_idemp_decaissement->currentText().toInt();
   QString methode_decaissement=ui->combo_mehode_decaissement->currentText();
    QString remarque_decaissement=ui->remarque_decaissement->text();
    QString montant_decaissement=ui->montant_decaissement->text();
    decaissement de(code_decaissement,methode_decaissement, montant_decaissement ,id_em_dec , remarque_decaissement);
    bool test=de.ajouter();
    if(ui->code_decaissement->text().isEmpty()||ui->code_decaissement->text().contains(QRegExp("^[1-9]"))==0||ui->combo_idemp_decaissement->currentText()=="choix id"||ui->montant_decaissement->text().isEmpty()||ui->combo_mehode_decaissement->currentText()=="choix")
    {QMessageBox::warning(nullptr, QObject::tr("erreur"),
                              QObject::tr("verifier les champs.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);}
    else{
    if(test)
    {
       ui->tabe_decaissement->setModel(dc.afficher());
       QMessageBox::information(nullptr, QObject::tr("Ajouter decaissement"),
       QObject::tr("decaissement ajoutée.\n"
       "Click Cancel to exit."), QMessageBox::Cancel);

    }
    }
}

void Ressources_Humaines::on_supprimer_decaissement_clicked()
{
    int row=ui->tabe_decaissement->selectionModel()->currentIndex().row();
    QString code_supprimer=ui->tabe_decaissement->model()->index(row,0).data().toString();
    bool test=dc.supprimer(code_supprimer);
    if(row==-1)
    { QMessageBox::critical(nullptr, QObject::tr("Supprimer"),
                            QObject::tr("Erreur selectionnez que vous voulez le supprimer!.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {
    if(test)
    {
        ui->tabe_decaissement->setModel(dc.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                    QObject::tr("decaissement supprimé.\n"
                                "Click Cancel" ),QMessageBox::Cancel);
    }
    }
}

void Ressources_Humaines::on_chercher_decaissement_textChanged(const QString &arg1)
{
    if(ui->chercher_decaissement->text() == "")
        {
            ui->tabe_decaissement->setModel(dc.afficher());
        }
        else
        {
             ui->tabe_decaissement->setModel(dc.rechercher(ui->chercher_decaissement->text()));
        }
}

void Ressources_Humaines::on_trier_decaissement_clicked()
{
    /*METIER TRI*/
    QString critere=ui->combobox_tri_decaissement->currentText();
        QString mode;
         if (ui->ASC_decaisssement->checkState()==false)
    {
             mode="DESC";
    }
         else if(ui->DESC_decaissement->checkState()==false)
         {
             mode="ASC";
         }
    ui->tabe_decaissement->setModel(dc.trie(critere,mode));
}

void Ressources_Humaines::on_pdf_decaissement_clicked()
{
    /*impression pdf*/

    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tabe_decaissement->model()->rowCount();
                const int columnCount =ui->tabe_decaissement->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("decaissement")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                            "<img src='C:/Users/user/Documents/Ressources_Humaines/icons/logo.jpg' width='100' height='100'>\n"
                            "<h1>Liste de decaissement</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tabe_decaissement->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tabe_decaissement->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tabe_decaissement->isColumnHidden(column)) {
                                   QString data = ui->tabe_decaissement->model()->data(ui->tabe_decaissement->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);
                    }
    }
}

void Ressources_Humaines::on_pdf_encaisssement_clicked()
{
    /*impression pdf*/

    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tabe_encaissement->model()->rowCount();
                const int columnCount =ui->tabe_encaissement->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("encaissement")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                            "<img src='C:/Users/user/Documents/Ressources_Humaines/icons/logo.jpg' width='100' height='100'>\n"
                            "<h1>Liste d'encaissement</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tabe_encaissement->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tabe_encaissement->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tabe_encaissement->isColumnHidden(column)) {
                                   QString data = ui->tabe_encaissement->model()->data(ui->tabe_encaissement->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);
                    }
    }
}

void Ressources_Humaines::on_modifier_encaissement_clicked()
{
    int code_encaissement=ui->code_encaissement->text().toInt() ;
    int id_employe=ui->combo_idemp_encaissement->currentText().toInt();
    QString methode_encaissement=ui->combo_mehode_encaissement->currentText();
    QString remarque_encaissement=ui->remarque_encaissement->text();
    QString montant_encaissement=ui->montant_encaissement->text();
    encaissement en(code_encaissement,methode_encaissement, montant_encaissement ,id_employe , remarque_encaissement);

    bool test =en.modifier();
    if(test)
    {ui->tabe_encaissement->setModel(en.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier encaissement"),
                                 QObject::tr("encaissement  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un encaissement"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_modifier_decaissement_clicked()
{
    int code_decaissement=ui->code_decaissement->text().toInt() ;
   int id_em_dec=ui->combo_idemp_decaissement->currentText().toInt();
   QString methode_decaissement=ui->combo_mehode_decaissement->currentText();
    QString remarque_decaissement=ui->remarque_decaissement->text();
    QString montant_decaissement=ui->montant_decaissement->text();
    decaissement de(code_decaissement,methode_decaissement, montant_decaissement ,id_em_dec , remarque_decaissement);

        bool test =de.modifier();
        if(test)
        {ui->tabe_decaissement->setModel(de.afficher());
            QMessageBox::information(nullptr, QObject::tr("modifier decaissement"),
                                     QObject::tr("decaissement  modifié.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("Modifier un decaissement"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_encaissement_pb_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    ui->encaissement_pb_2->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/encaissementOUI.png"));
    ui->decaissement_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/decaissementNON.png"));

}

void Ressources_Humaines::on_decaissement_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
    ui->encaissement_pb_2->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/encaissementNON.png"));
    ui->decaissement_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/decaissementOUI.png"));

}

void Ressources_Humaines::on_retour_menu_clicked()
{
    ui->main_stacked->setCurrentIndex(0);
    ui->side_stacked->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void Ressources_Humaines::on_ajouter_reclam_pb_clicked()
{
    QString raison=ui->le_reclamation->text();
    int id=ui->le_idreclam->text().toInt();
    QString emplacement=ui->combo_emplacement_reclam->currentText();

    Rec R(id,raison,emplacement);
    bool t=R.ajout();

     QMessageBox msgBox;


    if(t)
      {  msgBox.setText("Ajout avec succes.");
        ui->tab_reclam->setModel(R.affiche());
    }
    else
    {   msgBox.setText("Echec d'ajout");}
        msgBox.exec();

}

void Ressources_Humaines::on_modifier_reclam_pb_clicked()
{
    //Modifier
    int id = ui->le_idreclam->text().toInt();
    QString raison = ui->le_reclamation->text();
    QString emplacement= ui->combo_emplacement_reclam->currentText();
    Rec R(id,raison,emplacement) ;
    bool test =R.modifier(id,raison,emplacement);
    if(test)
    {ui->tab_reclam->setModel(R.affiche());
        QMessageBox::information(nullptr, QObject::tr("modifier une reclamation"),
                                 QObject::tr("reclamation  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une reclamation"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_supp_reclam_pb_clicked()
{
    //suprimer
    Rec R; R.setid(ui->le_supprimer_reclam->text().toInt());
    bool test=R.supprimer(R.getid());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tab_reclam->setModel(R.affiche());

    }
    else{
        msgBox.setText("Echec de suppression");
        msgBox.exec();
    }
}

void Ressources_Humaines::on_chercher_reclam_pb_clicked()
{
    //affichage & recherche
    if(ui->search_reclam_pb->text() == "")
        {
            ui->tab_reclam->setModel(R.affiche());
        }
        else
        {
             ui->tab_reclam->setModel(R.recherche(ui->search_reclam_pb->text()));
        }
}

void Ressources_Humaines::on_tri_pb_reclam_clicked()
{
    if (ui->combo_reclam_tri->currentText()=="ID")
    ui->tab_reclam->setModel(R.triID());
    else ui->tab_reclam->setModel(R.triEMP());
}

void Ressources_Humaines::on_export_reclam_clicked()
{
    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_reclam->model()->rowCount();
                const int columnCount =ui->tab_reclam->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("reclamation")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"

                            "<h1>Liste des reclamations</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_reclam->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_reclam->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_reclam->isColumnHidden(column)) {
                                   QString data = ui->tab_reclam->model()->data(ui->tab_reclam->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);




                    }
}

void Ressources_Humaines::on_pushButton_19_clicked()
{
    ui->main_stacked->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(4);
    ui->side_stacked->setCurrentIndex(3);


}

void Ressources_Humaines::on_ajouter_cit_clicked()
{
    //add
    int idC=ui->id_cit->text().toInt();
    QString nomC=ui->nom_cit->text();
    QString prenomC=ui->prenom_cit->text();
    QString dateC=ui->date_cit->text();

    Cit C(idC,nomC,prenomC,dateC);
    bool t=C.Cajout();

     QMessageBox msgBox;


    if(t)
      {  msgBox.setText("Ajout avec succes.");
        ui->tab_cit->setModel(C.Caffiche());
    }
    else
    {   msgBox.setText("Echec d'ajout");}
        msgBox.exec();
}


void Ressources_Humaines::on_modifier_cit_clicked()
{

    int idC = ui->id_cit->text().toInt();
    QString nomC = ui->nom_cit->text();
    QString prenomC = ui->prenom_cit->text();
    QString dateC=ui->date_cit->text();
    Cit C(idC,nomC,prenomC,dateC);
    bool test =C.Cmodifier(idC,nomC,prenomC,dateC);
    if(test)
    {ui->tab_cit->setModel(C.Caffiche());
        QMessageBox::information(nullptr, QObject::tr("modifier un Citoyen"),
                                 QObject::tr("Citoyen  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un Citoyen"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_supp_cit_clicked()
{
    //supprimer

    Cit C; C.setidC(ui->id_cit->text().toInt());
    bool test=C.Csupprimer(C.getidC());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tab_cit->setModel(C.Caffiche());

    }
    else{
        msgBox.setText("Echec de suppression");
        msgBox.exec();
    }
}

void Ressources_Humaines::on_Bshow_clicked()
{
    //affiche et recherche

    if(ui->chercher_cit->text() == "")
        {
            ui->tab_cit->setModel(C.Caffiche());
        }
        else
        {
             ui->tab_cit->setModel(C.Crecherche(ui->chercher_cit->text()));
        }
}

void Ressources_Humaines::on_B_ASC_clicked()
{
    if (ui->B_ASC->text()=="ASC") ui->B_ASC->setText("DESC");
    else if (ui->B_ASC->text()=="DESC") ui->B_ASC->setText("ASC");
}

void Ressources_Humaines::on_trier_cit_clicked()
{
    //trier
    if (ui->combocit->currentText()=="ID")

    {
        if (ui->B_ASC->text()=="ASC")
        ui->tab_cit->setModel(C.CtriIDasc());
        else
            ui->tab_cit->setModel(C.CtriIDdesc());
    }
    else
    {
        if (ui->B_ASC->text()=="ASC")
        ui->tab_cit->setModel(C.CtriNOMasc());
        else
            ui->tab_cit->setModel(C.CtriNOMdesc());
    }
}

void Ressources_Humaines::on_export_cit_clicked()
{
    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_cit->model()->rowCount();
                const int columnCount =ui->tab_cit->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("citoyen")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"

                            "<h1>Liste des citoyen</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_cit->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_cit->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_cit->isColumnHidden(column)) {
                                   QString data = ui->tab_cit->model()->data(ui->tab_cit->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);




                    }
}

void Ressources_Humaines::on_recla_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
    ui->recla_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/reclaOUI.png"));
    ui->cit_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/citoy_NON.png"));

}

void Ressources_Humaines::on_cit_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
    ui->recla_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/reclaNON.png"));
    ui->cit_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/citoy_OUI.png"));
}

void Ressources_Humaines::on_Aj_mf_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(7);
    ui->tabbaladia->setModel(na.afficher());
}

void Ressources_Humaines::on_ajout1_pb_clicked()
{
    int cin=ui->le_numeronaissance->text().toInt();
    QString nome=ui->le_nom1->text();
    QString prenome=ui->le_prenom1->text();
    QString lieu_de_naissance=ui->le_lieu->text();
    QString nomPere=ui->le_nomdupere->text();
    QString prenompere=ui->le_prenomdupere->text();
    QString nommere=ui->le_nommere->text();
    QString prenommere=ui->le_prenommere->text();
    QString nationalite=ui->le_nationalite->text();
    QString sexe=ui->le_sexe->text();
    QString tribunal=ui->tribunal->text();
    QString officier=ui->idoc->text();
    QString observations=ui->observation->toPlainText();
    QString note=ui->note->toPlainText();

    QDate date_de_naissance=ui->date_naissance->date();
    QDate date_de_declaration=ui->datedeclaration->date();

    naissance na(cin,nome,prenome,lieu_de_naissance,nomPere,prenompere,nommere,prenommere,nationalite,sexe,tribunal,officier,note,observations,date_de_naissance,date_de_declaration);
    bool test=na.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout naissance"),
                                 QObject::tr("ajout avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidget_2->setCurrentIndex(6);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout naissance"),
                              QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_pushButton_20_clicked()
{
    ui->main_stacked->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(12);
    ui->side_stacked->setCurrentIndex(6);
}

void Ressources_Humaines::on_test_clicked()
{
    ui->main_stacked->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(6);
    ui->side_stacked->setCurrentIndex(4);
}

void Ressources_Humaines::on_modif1_pb_clicked()
{
    int cin=ui->le_numeronaissance->text().toInt();
    QString nome=ui->le_nom1->text();
    QString prenome=ui->le_prenom1->text();
    QString lieu_de_naissance=ui->le_lieu->text();
    QString nomPere=ui->le_nomdupere->text();
    QString prenompere=ui->le_prenomdupere->text();
    QString nommere=ui->le_nommere->text();
    QString prenommere=ui->le_prenommere->text();
    QString nationalite=ui->le_nationalite->text();
    QString sexe=ui->le_sexe->text();
    QString tribunal=ui->tribunal->text();
    QString officier=ui->idoc->text();
    QString observations=ui->observation->toPlainText();
    QString note=ui->note->toPlainText();

    QDate date_de_naissance=ui->date_naissance->date();
    QDate date_de_declaration=ui->datedeclaration->date();

    naissance na(cin,nome,prenome,lieu_de_naissance,nomPere,prenompere,nommere,prenommere,nationalite,sexe,tribunal,officier,note,observations,date_de_naissance,date_de_declaration);
    bool test=na.modifier();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("modifier naissance"),
                                 QObject::tr("naissance  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidget_2->setCurrentIndex(6);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier naissance"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_pb_suprrr_clicked()
{
    int cin=ui->le_supppr->text().toInt();
    bool test=na.supprimer(cin);
    if(test){
        QMessageBox::information(nullptr, QObject::tr("suppression naissannce"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabbaladia->setModel(na.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("suppression naissance"),
                              QObject::tr("suppression échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);

}

void Ressources_Humaines::on_le_recherche01_textChanged(const QString &arg1)
{
    QString nom = ui->le_recherche01->text();
    ui->tabbaladia->setModel(na.recherche_dynamique(nom));
}

void Ressources_Humaines::on_trinum_pb_clicked()
{
     ui->tabbaladia->setModel(na.tri_tri());
}

void Ressources_Humaines::on_trinom_pb_clicked()
{
    ui->tabbaladia->setModel(na.afficher_tri_nom());

}

void Ressources_Humaines::on_triprenompb_clicked()
{
    ui->tabbaladia->setModel(na.afficher_tri_prenom());

}

void Ressources_Humaines::on_pdf_pb01_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tabbaladia->model()->rowCount();
    const int columnCount =ui->tabbaladia->model()->columnCount();
    //qDebug() << "App path : " << QDir::currentPath();

    out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("naissance")
        <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<img src='logo.jpg'>\n"

           "<h1>LES DONNEES D'UNE NAISSANCE </h1>"
           "<br><br><br><br>"



           "<table border=1 cellspacing=0 cellpadding=2>\n";


    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tabbaladia->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tabbaladia->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tabbaladia->isColumnHidden(column)) {
                QString data = ui->tabbaladia->model()->data(ui->tabbaladia->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
           "</body>\n"
           "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);


    //  QTextDocument document;
    // document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName("naissance.pdf");
    document->print(&printer);
    QDesktopServices::openUrl(QUrl::fromLocalFile("naissance.pdf"));
}

void Ressources_Humaines::on_naissanceside_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
    ui->naissanceside->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/naissanceOUI.png"));
    ui->decesside->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/deathNON.png"));
}

void Ressources_Humaines::on_retourmenu_clicked()
{
    ui->main_stacked->setCurrentIndex(0);
    ui->side_stacked->setCurrentIndex(0);
}

void Ressources_Humaines::on_pushButton_13_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(9);
    ui->tab_deces->setModel(de.afficher_deces());
}

void Ressources_Humaines::on_Ajouterdeces_pb_clicked()
{
    int cind=ui->le_numdeces->text().toInt();
    QString nomed=ui->nomdeces->text();
    QString prenomed=ui->le_prenomdeces->text();
    QString lieu_de_naissanced=ui->le_lieudeces->text();

    QString nomPered=ui->le_nomperedeces->text();
    QString prenompered=ui->le_prenomperedeces->text();
    QString nommered=ui->le_nommeredeces->text();
    QString prenommered=ui->le_prenommeredeces->text();
    QString nationalited=ui->le_nationalite_2->text();
    QString sexed=ui->le_sexe_deces->text();
    QString tribunald=ui->le_tribunaldeces->text();
    QString officierd=ui->le_idcdeces->text();
    QString noted=ui->notedeces->toPlainText();
    QString observationsd=ui->observationdeces->toPlainText();
    QString lieu_de_deces=ui->le_lieudeces_2->text();
    QDate date_de_naissanced=ui->datenaissancedeces->date();
    QDate date_de_declarations_dedeces=ui->datedeclarationdeces->date();
    QDate date_de_deces=ui->datedecees->date();


    deces d(cind,nomed,prenomed,lieu_de_naissanced,nomPered,prenompered,nommered,prenommered,nationalited,sexed,tribunald,officierd,noted,observationsd,lieu_de_deces,date_de_naissanced,date_de_declarations_dedeces,date_de_deces);
    bool test=d.ajouter_deces();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout deces"),
                                 QObject::tr("ajout avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidget_2->setCurrentIndex(8);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout deces"),
                              QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_decesside_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(8);
    ui->naissanceside->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/naissanceNON.png"));
    ui->decesside->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/deathOUI.png"));

}

void Ressources_Humaines::on_aj_mf_dec_clicked()
{
   ui->stackedWidget_2->setCurrentIndex(9);
    ui->tab_deces->setModel(de.afficher_deces());

}

void Ressources_Humaines::on_modifierdeces_pb_clicked()
{
    QString nomed=ui->nomdeces->text();
    QString prenomed=ui->le_prenomdeces->text();
    QString lieu_de_naissanced=ui->le_lieudeces->text();

    QString nomPered=ui->le_nomperedeces->text();
    QString prenompered=ui->le_prenomperedeces->text();
    QString nommered=ui->le_nommeredeces->text();
    QString prenommered=ui->le_prenommeredeces->text();
    QString nationalited=ui->le_nationalite_2->text();
    QString sexed=ui->le_sexe_deces->text();
    QString tribunald=ui->le_tribunaldeces->text();
    QString officierd=ui->le_idcdeces->text();
    QString noted=ui->notedeces->toPlainText();
    QString observationsd=ui->observationdeces->toPlainText();
    QString lieu_de_deces=ui->le_lieudeces_2->text();



    if(de.modifier_deces())
    {
        QMessageBox::information(nullptr, QObject::tr("modifier une deces"),
                                 QObject::tr("modification avec succès !!.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidget_2->setCurrentIndex(8);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier une deces"),
                              QObject::tr("modification échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);

}

void Ressources_Humaines::on_recherche_deces_textChanged(const QString &arg1)
{
    QString nom = ui->recherche_deces->text();
        ui->tab_deces->setModel(de.recherche_dynamique(nom));
}

void Ressources_Humaines::on_supprimerdeces_pb_clicked()
{
    int cin=ui->supprimer_deces->text().toInt();
    bool test=de.supprimer_deces(cin);
    if(test){
        QMessageBox::information(nullptr, QObject::tr("suppression deces"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_deces->setModel(de.afficher_deces());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("suppression deces"),
                              QObject::tr("suppression échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);


}

void Ressources_Humaines::on_pushButton_14_clicked()
{
    ui->tab_deces->setModel(de.afficher_tri_nom());

}

void Ressources_Humaines::on_pushButton_16_clicked()
{
    ui->tab_deces->setModel(de.afficher_tri_prenom());

}

void Ressources_Humaines::on_pushButton_15_clicked()
{
    ui->main_stacked->setCurrentIndex(0);
    ui->side_stacked->setCurrentIndex(0);
}

void Ressources_Humaines::on_Ajouter_demande_pb_clicked()
{

        int id_demande = ui->IdD->text().toInt();
        QString nom = ui->le_nomD->text();
        QString prenom = ui->le_prenomD->text();
        QString etat = ui->le_etatD->text();

    demandes dem(id_demande,prenom,nom,etat);
    bool test=dem.ajouter();
    QMessageBox msgBox;

    if(test)
      {  msgBox.setText("Ajout avec succes.");
        ui->tabdemandes->setModel(dem.afficher());
    }




}

void Ressources_Humaines::on_pushButton_17_clicked()
{   int id_demande= ui->IdD->text().toInt();
    QString nom = ui->le_nomD->text();
    QString prenom= ui->le_prenomD->text();
    QString etat= ui->le_etatD->text();
    demandes dem(id_demande,prenom,nom,etat);

    bool test =dem.Modifier(id_demande,prenom,nom,etat);
    if(test)
    {ui->tabdemandes->setModel(dem.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier une demande"),
                                 QObject::tr("demande  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une demande"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_pushButton_21_clicked()
{
    int id_demande=ui->lineEdit_8->text().toInt();
        //qDebug()<<id_demande;
        QString nom;
        QString prenom;
        QString etat;
      demandes o(id_demande,nom,prenom,etat);
        bool test=o.supprimer(id_demande);
         // notif->showMessage(tr("ouvrier Supprimé "),tr(prenom.toUtf8().constData()));
        QMessageBox::information(this, "Supprimée", "Supression reussi");
        ui->tabdemandes->setModel(dem.afficher());
}

void Ressources_Humaines::on_pushButton_27_clicked()
{
    ui->tabdemandes->setModel(dem.sortid_up());
}

void Ressources_Humaines::on_pushButton_26_clicked()
{
    ui->tabdemandes->setModel(dem.sortid_down());

}

void Ressources_Humaines::on_pushButton_22_clicked()
{
    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tabdemandes->model()->rowCount();
                const int columnCount =ui->tabdemandes->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("demandes")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                            "<img src='C:/Users/user/Documents/Ressources_Humaines/icons/logo.jpg' width='100' height='100'>\n"
                            "<h1>Liste des employes</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tabdemandes->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tabdemandes->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tabdemandes->isColumnHidden(column)) {
                                   QString data = ui->tabdemandes->model()->data(ui->tabdemandes->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);
                    }
    }

}







void Ressources_Humaines::on_AjouterC_clicked()
{

    QMessageBox msgBox;

    int id=ui->numparcelleC->text().toInt();
    QString nom = ui->nomC->text();
    QString prenom = ui->prenomC->text();
    float surface = ui->surfaceC->text().toFloat();
    cadastre ca(id,nom,prenom,surface);
    bool test=ca.ajouter();
    if(test)
      {  msgBox.setText("Ajout avec succes.");
        ui->tabcadastre->setModel(ca.afficher());
    }
}

void Ressources_Humaines::on_supprimerC_clicked()
{
    int id_cadastre=ui->supp_numPC->text().toInt();
        //qDebug()<<id_cadastre;
        QString nom;
        QString prenom;
        float surface;
      cadastre ca(id_cadastre,nom,prenom,surface);
        bool test=ca.supprimer(id_cadastre);
         // notif->showMessage(tr("ouvrier Supprimé "),tr(prenom.toUtf8().constData()));
        QMessageBox::information(this, "Supprimée", "Supression reussi");
        ui->tabcadastre->setModel(ca.afficher());
}

void Ressources_Humaines::on_modifierC_clicked()
{





    int id=ui->numparcelleC->text().toInt();
    QString nom = ui->nomC->text();
    QString prenom = ui->prenomC->text();
    float surface = ui->surfaceC->text().toFloat();
       cadastre ca(id,nom,prenom,surface);
       bool test =ca.Modifier(id,nom,prenom,surface);
       if(test)
       {ui->tabcadastre->setModel(ca.afficher());
           QMessageBox::information(nullptr, QObject::tr("modifier une cadastre"),
                                    QObject::tr("cadastre  modifié.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}
       else
           QMessageBox::critical(nullptr, QObject::tr("Modifier une cadastre"),
                                 QObject::tr("Erreur !.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

}

void Ressources_Humaines::on_pdfC_pb_clicked()
{
    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tabcadastre->model()->rowCount();
                const int columnCount =ui->tabcadastre->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("cadastre")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                            "<img src='C:/Users/user/Documents/Ressources_Humaines/icons/logo.jpg' width='100' height='100'>\n"
                            "<h1>Liste de cadastre</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tabcadastre->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tabcadastre->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tabcadastre->isColumnHidden(column)) {
                                   QString data = ui->tabcadastre->model()->data(ui->tabcadastre->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);
                    }
    }
}

void Ressources_Humaines::on_pushButton_31_clicked()
{
    QTableView *table;
            table = ui->tabcadastre;

            QString filters("CSV files (.csv);;All files (.*)");
            QString defaultFilter("CSV files (*.csv)");
            QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                               filters, &defaultFilter);
            QFile file(fileName);

            QAbstractItemModel *model =  table->model();
            if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                QTextStream data(&file);
                QStringList strList;
                for (int i = 0; i < model->columnCount(); i++) {
                    if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                        strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                    else
                        strList.append("");
                }
                data << strList.join(";") << "\n";
                for (int i = 0; i < model->rowCount(); i++) {
                    strList.clear();
                    for (int j = 0; j < model->columnCount(); j++) {

                        if (model->data(model->index(i, j)).toString().length() > 0)
                            strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                        else
                            strList.append("");
                    }
                    data << strList.join(";") + "\n";
                }
                file.close();
                QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
            }
}

void Ressources_Humaines::on_pushButton_32_clicked()
{
    ui->tabcadastre->setModel(ca.sortid_up());

}

void Ressources_Humaines::on_pushButton_33_clicked()
{
    ui->tabcadastre->setModel(ca.sortid_down());

}

void Ressources_Humaines::on_pushButton_18_clicked()
{
    ui->main_stacked->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(10);
    ui->side_stacked->setCurrentIndex(5);

}

void Ressources_Humaines::on_demande_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);
    ui->demande->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/demandeOUI.png"));
    ui->cadastre->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/cadastreNON.png"));
}

void Ressources_Humaines::on_cadastre_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(11);
    ui->demande->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/demandeNON.png"));
    ui->cadastre->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/cadastreOUI.png"));

}

void Ressources_Humaines::on_RRETOUR_clicked()
{

    ui->main_stacked->setCurrentIndex(0);
    ui->side_stacked->setCurrentIndex(0);

}

void Ressources_Humaines::on_login_pb_clicked()
{
    QString login=ui->login->text();
       QString mdp=ui->password->text();
       QSqlQuery qry;
       qry.prepare("select * from compte where login=:login and MDP=:mdp");
        qry.bindValue(":login",login);
        qry.bindValue(":mdp",mdp);
       qry.exec();
   qry.next();
   if(login.isEmpty()&& mdp.isEmpty())
   {QMessageBox :: critical(nullptr,QObject::tr("Erreur "),
                            QObject::tr("Vérifier votre login ou mot de passe\n"
                                        "click cancel to exit "),QMessageBox ::Cancel);}
   else
   {
   if(login==qry.value(0).toString() && mdp==qry.value(1).toString())
   {
       if(qry.value(0).toString()=="admin")
       {
           ui->main_stacked->setCurrentIndex(0);
           ui->login->clear();
           ui->password->clear();
           ui->menu_rh->setEnabled(1);
           ui->menu_fn->setEnabled(1);
           ui->pushButton_19->setEnabled(1);
           ui->test->setEnabled(1);
           ui->pushButton_18->setEnabled(1);
       ui->pushButton_20->setEnabled(1);



       }
       else
           if(qry.value(0).toString()=="ressources_humaines")
   {

           ui->main_stacked->setCurrentIndex(0);
           ui->menu_rh->setEnabled(1);
           ui->menu_fn->setDisabled(1);
           ui->menu_fn->setStyleSheet("border: 1px solid white");
           ui->pushButton_19->setDisabled(1);
           ui->pushButton_19->setStyleSheet("border: 1px solid white");
           ui->test->setDisabled(1);
           ui->test->setStyleSheet("border: 1px solid white");
       ui->pushButton_18->setDisabled(1);
           ui->pushButton_18->setStyleSheet("border: 1px solid white");
       ui->pushButton_20->setDisabled(1);
           ui->pushButton_20->setStyleSheet("border: 1px solid white");

           ui->login->clear();
           ui->password->clear();
           }
       else if(qry.value(0).toString()=="caissier")
           {   ui->main_stacked->setCurrentIndex(0);
               ui->menu_rh->setDisabled(1);
               ui->menu_rh->setStyleSheet("border: 1px solid white");
               ui->menu_fn->setEnabled(1);
               ui->pushButton_19->setDisabled(1);
               ui->pushButton_19->setStyleSheet("border: 1px solid white");
               ui->pushButton_18->setDisabled(1);
               ui->pushButton_18->setStyleSheet("border: 1px solid white");
           ui->pushButton_20->setDisabled(1);
               ui->pushButton_20->setStyleSheet("border: 1px solid white");
               ui->test->setDisabled(1);
               ui->test->setStyleSheet("border: 1px solid white");
               ui->login->clear();
               ui->password->clear();}

       else if(qry.value(0).toString()=="relation_publiques")
           {ui->main_stacked->setCurrentIndex(0);
               ui->menu_rh->setDisabled(1);
               ui->menu_rh->setStyleSheet("border: 1px solid white");
               ui->menu_fn->setDisabled(1);
               ui->menu_fn->setStyleSheet("border: 1px solid white");
           ui->pushButton_18->setDisabled(1);
               ui->pushButton_18->setStyleSheet("border: 1px solid white");
           ui->pushButton_20->setDisabled(1);
               ui->pushButton_20->setStyleSheet("border: 1px solid white");
               ui->test->setDisabled(1);
               ui->test->setStyleSheet("border: 1px solid white");

               ui->pushButton_19->setEnabled(1);

               ui->login->clear();
               ui->password->clear();}

   else if(qry.value(0).toString()=="municipalite")
           {ui->main_stacked->setCurrentIndex(0);
               ui->menu_rh->setDisabled(1);
               ui->menu_rh->setStyleSheet("border: 1px solid white");
               ui->menu_fn->setDisabled(1);
               ui->menu_fn->setStyleSheet("border: 1px solid white");
               ui->pushButton_19->setDisabled(1);
               ui->pushButton_19->setStyleSheet("border: 1px solid white");
               ui->pushButton_20->setDisabled(1);
               ui->pushButton_20->setStyleSheet("border: 1px solid white");
           ui->pushButton_18->setDisabled(1);
               ui->pushButton_18->setStyleSheet("border: 1px solid white");
               ui->test->setEnabled(1);
               ui->login->clear();
               ui->password->clear();}
       else if(qry.value(0).toString()=="urbanisme")
           {ui->main_stacked->setCurrentIndex(0);
               ui->menu_rh->setDisabled(1);
               ui->menu_rh->setStyleSheet("border: 1px solid white");
               ui->menu_fn->setDisabled(1);
               ui->menu_fn->setStyleSheet("border: 1px solid white");
               ui->pushButton_19->setDisabled(1);
               ui->pushButton_19->setStyleSheet("border: 1px solid white");
               ui->test->setDisabled(1);
               ui->test->setStyleSheet("border: 1px solid white");
           ui->pushButton_20->setDisabled(1);
               ui->pushButton_20->setStyleSheet("border: 1px solid white");
               ui->pushButton_18->setEnabled(1);
               ui->login->clear();
               ui->password->clear();}


   }

       else
       { QMessageBox :: critical(nullptr,QObject::tr("Erreur "),
                                 QObject::tr("Vérifier votre login ou mot de passe\n"
                                             "click cancel to exit "),QMessageBox ::Cancel);}



   }
}

void Ressources_Humaines::on_disconnect_clicked()
{
    ui->main_stacked->setCurrentIndex(2);
}

void Ressources_Humaines::on_searching_clicked()
{
    QString chercher= ui->searching->text();
    QString nom;

        QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        if(chercher != "")
        {q.prepare("select * from cadastre where nom like '%"+chercher+"%'");
            q.bindValue(":nom",chercher);
            q.exec();
            modal->setQuery(q);
            ui->tabcadastre->setModel(modal);
            ui->tabcadastre->setModel(modal);
    }
        else
        {QMessageBox::warning(this,"Probléme","recherche invalide");

}
}

void Ressources_Humaines::on_searchingAgain_clicked()
{
    QString chercher= ui->searchingAgain->text();
    QString nom;

        QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        if(chercher != "")
        {q.prepare("select * from cadastre where nom like '%"+chercher+"%'");
            q.bindValue(":nom",chercher);
            q.exec();
            modal->setQuery(q);
            ui->tabcadastre->setModel(modal);
            ui->tabcadastre->setModel(modal);
    }
        else
        {QMessageBox::warning(this,"Probléme","recherche invalide");

}
}

void Ressources_Humaines::on_recherche_dem_textChanged(const QString &arg1)
{
    if(ui->recherche_dem->text() == "")
        {
            ui->tabdemandes->setModel(dem.afficher());
        }
        else
        {
             ui->tabdemandes->setModel(dem.rechercher(ui->recherche_dem->text()));
        }
}


void Ressources_Humaines::on_rechercheC_textChanged(const QString &arg1)
{
    if(ui->rechercheC->text() == "")
        {
            ui->tabcadastre->setModel(ca.afficher());
        }
        else
        {
             ui->tabcadastre->setModel(ca.rechercher(ui->rechercheC->text()));
        }
}



void Ressources_Humaines::on_xxx_clicked()
{
    stat02=new stat2(this);
    stat02->show();
}

void Ressources_Humaines::on_ArduinoON_2_clicked()
{
    A.write_to_arduino("1");
}

void Ressources_Humaines::on_ArduinoOFF_2_clicked()
{
    A.write_to_arduino("0");
}

void Ressources_Humaines::on_ajouterequi_clicked()
{

 int ID_E=ui->IDA->text().toInt();
QString NOM=ui->NOMA->text();
QString REFERENCE=ui->REFA->text();
equipement e(ID_E,NOM,REFERENCE);
bool test=e.ajouter();
if(test)
{
    ui->TABA->setModel(e.Afficher());

    QMessageBox::information(nullptr, QObject::tr("Ajout equipement"),
                QObject::tr("ajout avec succès.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Ajout equipement"),
                QObject::tr("Ajout échoué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_pushButton_25_clicked()
{
    int ID_E=ui->IDASUPP ->text().toInt();



            bool test=e.supprimer(ID_E);
            if(test)
               {
                ui->TABA->setModel(e.Afficher());

               QMessageBox::information(nullptr,"SUPRESSION","supprimé.");}
            else
               QMessageBox::information(nullptr,"SUPRESSION","probleme suppresion");
}

void Ressources_Humaines::on_modifierequi_clicked()
{
    int ID_E=ui->IDA ->text().toInt();
    QString NOM=ui->NOMA->text();
    QString REFERENCE=ui->REFA ->text();
    equipement e(ID_E,NOM,REFERENCE);
    bool test=e.modifier(ID_E,NOM,REFERENCE);
    if(test)
    {
        ui->TABA->setModel(e.Afficher());

        QMessageBox::information(nullptr, QObject::tr("modifier equipement"),
                    QObject::tr("modification avec succès.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier equipement"),
                    QObject::tr("modification échoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ressources_Humaines::on_PDFA_clicked()
{
    /*impression pdf*/

    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->TABA->model()->rowCount();
                const int columnCount =ui->TABA->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("equipement")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                            "<img src='C:/Users/user/Documents/Ressources_Humaines/icons/logo.jpg' width='100' height='100'>\n"
                            "<h1>Liste des equipement</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->TABA->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->TABA->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->TABA->isColumnHidden(column)) {
                                   QString data = ui->TABA->model()->data(ui->TABA->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);
                    }
    }
}

void Ressources_Humaines::on_MAILINGA_clicked()
{
    email e;
    e.exec();
}

void Ressources_Humaines::on_comboV_activated(const QString &arg1)
{
    ui->searchV->setDisabled(false);
         QString champ=arg1;
    ui->checkV->setDisabled(false);
}

void Ressources_Humaines::on_ajouterV_clicked()
{
    int ID_V=ui->idV ->text().toInt();
    QString NOM=ui->nomV->text();
    QString REFERENCE=ui->refV ->text();
    vehicule v(ID_V,NOM,REFERENCE);
    bool test=v.ajouter();
    if(test)
    {
        ui->tabV->setModel(v.Afficher());

        QMessageBox::information(nullptr, QObject::tr("Ajout vehicule"),
                    QObject::tr("ajout avec succès.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout vehicule"),
                    QObject::tr("Ajout échoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void Ressources_Humaines::on_supprimerV_clicked()
{
    int ID_V=ui->IDVS ->text().toInt();


            bool test=v.supprimer(ID_V);
            if(test)
               {
                ui->tabV->setModel(v.Afficher());
               QMessageBox::information(nullptr,"SUPRESSION","supprimé.");}
            else
               QMessageBox::critical(nullptr,"SUPRESSION","probleme suppresion");

}

void Ressources_Humaines::on_modifierV_clicked()
{
    int ID_V=ui->idV->text().toInt();
    QString NOM=ui->nomV->text();
    QString REFERENCE=ui->refV ->text();
    vehicule v(ID_V,NOM,REFERENCE);
    bool test=v.modifier(ID_V,NOM,REFERENCE);
    if(test)
    {
        ui->tabV->setModel(v.Afficher_vehicule());

        QMessageBox::information(nullptr, QObject::tr("modifier vehicule"),
                    QObject::tr("modification avec succès.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier vehicule"),
                    QObject::tr("modification échoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void Ressources_Humaines::on_toV_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(13);
    ui->toV->setIcon(QIcon("C:/Users/user/Documents/sm_integration/iconet/vehiculeON.png"));
    ui->toE->setIcon(QIcon("C:/Users/user/Documents/sm_integration/iconet/EOFF.png"));
}

void Ressources_Humaines::on_toE_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(12);
    ui->toV->setIcon(QIcon("C:/Users/user/Documents/sm_integration/iconet/vehiculeOFF.png"));
    ui->toE->setIcon(QIcon("C:/Users/user/Documents/sm_integration/iconet/EONN.png"));
}

void Ressources_Humaines::on_anglais_clicked()
{
    lang="ang";
    ui->menu_rh->setText("HR");
    ui->menu_rh->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->menu_fn->setText("Finance");
    ui->menu_fn->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->pushButton_19->setText("Citizens");
    ui->pushButton_19->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->test->setText("Minicipality");
    ui->test->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->code_encaissement->setPlaceholderText("Code");
    ui->code_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->montant_encaissement->setPlaceholderText("Amount");
    ui->montant_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->remarque_encaissement->setPlaceholderText("Remark");
    ui->remarque_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->combo_mehode_encaissement->setCurrentText("Payment method");
    ui->combo_mehode_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->encaissement_pb->setText("Validate");
    ui->encaissement_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->modifier_encaissement->setText("Modify");
    ui->modifier_encaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->supprimer_encaissement->setText("Delete");
    ui->supprimer_encaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trier_encaissement->setText("Sort");
    ui->trier_encaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->chercher_encaissement->setPlaceholderText("research");
    ui->chercher_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->le_reclamation->setPlaceholderText("Claim");
    ui->le_reclamation->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->groupBox->setTitle("ADD/Modify Claim");
    ui->groupBox->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->groupBox_2->setTitle("Delete");
    ui->groupBox_2->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->groupBox_3->setTitle("Display and Sorting");
    ui->groupBox_3->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->groupBox_4->setTitle("Export into PDF");
    ui->groupBox_4->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->modifier_reclam_pb->setText("Modify");
    ui->modifier_reclam_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->ajouter_reclam_pb->setText("Add");
    ui->ajouter_reclam_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->supp_reclam_pb->setText("Delete");
    ui->supp_reclam_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->chercher_reclam_pb->setText("Search");
    ui->chercher_reclam_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->tri_pb_reclam->setText("Sort");
    ui->tri_pb_reclam->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->export_reclam->setText("Export");
    ui->export_reclam->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->ArduinoON->setText("ON");
    ui->ArduinoON->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->ArduinoOFF->setText("OFF");
    ui->ArduinoOFF->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->label_7->setText("Location");
    ui->label_8->setText("reason");
    ui->code_decaissement->setPlaceholderText("Code");
    ui->code_decaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->montant_decaissement->setPlaceholderText("Amount");
    ui->montant_decaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->remarque_decaissement->setPlaceholderText("Remark");
    ui->remarque_decaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->chercher_decaissement->setPlaceholderText("Research");
    ui->chercher_decaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->decaissement_pb_valider->setText("Validate");
    ui->decaissement_pb_valider->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->modifier_decaissement->setText("Modifiy");
    ui->modifier_decaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->supprimer_decaissement->setText("Delete");
    ui->supprimer_decaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trier_decaissement->setText("Sort");
    ui->trier_decaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trier_cit->setText("Sort");
    ui->trier_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->export_cit->setText("Export into PDF");
    ui->export_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->ajouter_cit->setText("Add");
    ui->ajouter_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->modifier_cit->setText("Modify");
    ui->modifier_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->supp_cit->setText("Delete");
    ui->supp_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->Bshow->setText("Display");
    ui->Bshow->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->groupBox_6->setTitle("Addition and Modification");
    ui->groupBox_6->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->groupBox_8->setTitle("Delete");
    ui->groupBox_8->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->nom_cit->setPlaceholderText("Name");
    ui->nom_cit->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->prenom_cit->setPlaceholderText("First Name");
    ui->prenom_cit->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->chercher_cit->setPlaceholderText("Search ID");
    ui->chercher_cit->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->pb_suprrr->setText("Delete");
    ui->pb_suprrr->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->Aj_mf_pb->setText("Add/Modify");
    ui->Aj_mf_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trinum_pb->setText("Sort by Number");
    ui->trinum_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trinom_pb->setText("Sort by Name");
    ui->trinom_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->triprenompb->setText("Sort by First Name");
    ui->triprenompb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->le_recherche01->setPlaceholderText("Research");
    ui->le_recherche01->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->le_supppr->setText("Delete");
    ui->le_supppr->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->label_2->setText("Add Employee");
    ui->label_3->setText("Delete Employee");
    ui->label->setText("Employee Table");
    ui->label_4->setText("Add Training");
    ui->label_5->setText("Delete Training");
    ui->label_6->setText("Training Table");
     ui->observation->setText("observation");
     ui->note->setText("note");
     ui->ajouter->setText("Add");
     ui->ajouter->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->modifier->setText("Modify");
     ui->modifier->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_3->setText("Delete");
     ui->pushButton_3->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_9->setText("Sort");
     ui->pushButton_9->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pb_ajouterformation->setText("Add");
     ui->pb_ajouterformation->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pb_modifierformation->setText("Modify");
     ui->pb_modifierformation->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pb_supprimerformation->setText("Delete");
     ui->pb_supprimerformation->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_12->setText("Sort");
     ui->pushButton_12->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->ajout1_pb->setText("Add");
     ui->ajout1_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->modif1_pb->setText("Modify");
     ui->modif1_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->supprimerdeces_pb->setText("Delete");
     ui->supprimerdeces_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->aj_mf_dec->setText("Add/Modify");
     ui->aj_mf_dec->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_14->setText("Sort by Name");
     ui->pushButton_14->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_16->setText("Sort by First Name");
     ui->pushButton_16->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->le_nom->setPlaceholderText("Name");
     ui->le_nom->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_prenom->setPlaceholderText("First Name");
     ui->le_prenom->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_salaire->setPlaceholderText("Salary");
     ui->le_salaire->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_duree->setPlaceholderText("Duration");
     ui->le_duree->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_searchformation->setPlaceholderText("research");
     ui->le_searchformation->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_idformation->setPlaceholderText("ID Training");
     ui->le_idformation->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_supprimerformation->setPlaceholderText("ID Training");
     ui->le_supprimerformation->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_nom1->setPlaceholderText("Name");
     ui->le_nom1->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_prenom1->setPlaceholderText("First Name");
     ui->le_prenom1->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_lieu->setPlaceholderText("Place");
     ui->le_lieu->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_nomdupere->setPlaceholderText("Fadher's Surname");
     ui->le_nomdupere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_prenomdupere->setPlaceholderText("Fadher's Name");
     ui->le_prenomdupere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_nommere->setPlaceholderText("Modher's Surname");
     ui->le_nommere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_prenommere->setPlaceholderText("Modher's Name");
     ui->le_prenommere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_nationalite->setPlaceholderText("Nationality");
     ui->le_nationalite->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_numeronaissance->setPlaceholderText("Birth Number");
     ui->le_numeronaissance->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_sexe->setPlaceholderText("Gender");
     ui->le_sexe->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->tribunal->setPlaceholderText("Court");
     ui->tribunal->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->recherche_deces->setPlaceholderText("Research");
     ui->recherche_deces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->supprimerdeces_pb->setText("Delete");
     ui->supprimerdeces_pb->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");

     ui->combo_mehode_encaissement->clear();
        QStringList list1;
        list1<<"Payment method"<<"choice"<<"transfer"<<"check"<<"credit card";
        ui->combo_mehode_encaissement->addItems(list1);

        ui->combo_mehode_decaissement->clear();
           QStringList list2;
           list1<<"Payment method"<<"choice"<<"transfer"<<"check"<<"credit card";
           ui->combo_mehode_decaissement->addItems(list2);

           ui->combobox_tri_decaissement->clear();
              QStringList list3;
              list3<<"code"<<"date"<<"amount"<<"payment method"<<"ID employe"<<"remark";
              ui->combobox_tri_decaissement->addItems(list3);

              ui->combobox_tri_encaissement->clear();
                 QStringList list4;
                 list4<<"code"<<"date"<<"amount"<<"payment method"<<"ID employe"<<"remark";
                 ui->combobox_tri_encaissement->addItems(list4);


                 ui->nomdeces->setPlaceholderText("Name");
                 ui->nomdeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_prenomdeces->setPlaceholderText("First Name");
                 ui->le_prenomdeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_lieudeces->setPlaceholderText("Place");
                 ui->le_lieudeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_nomperedeces->setPlaceholderText("Fadher's Surname");
                 ui->le_nomperedeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_prenomperedeces->setPlaceholderText("Fadher's Name");
                 ui->le_prenomperedeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_nommeredeces->setPlaceholderText("Modher's Surname");
                 ui->le_nommeredeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_prenommere->setPlaceholderText("Modher's Name");
                 ui->le_prenommere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_nationalite_2->setPlaceholderText("Nationality");
                 ui->le_nationalite_2->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_numdeces->setPlaceholderText("Death Number");
                 ui->le_numdeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_sexe_deces->setPlaceholderText("Gender");
                 ui->le_sexe_deces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_tribunaldeces->setPlaceholderText("Court");
                 ui->le_tribunaldeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_idcdeces->setPlaceholderText("registrar's identity");
                 ui->le_idcdeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_lieudeces_2->setPlaceholderText("place of death");
                 ui->le_lieudeces_2->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->notedeces->setText("observation");
                 ui->observationdeces->setText("note");
                 ui->Ajouterdeces_pb->setText("Add");
                 ui->Ajouterdeces_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->modifierdeces_pb->setText("Modify");
                 ui->modifierdeces_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");


                 ui->IdD->setPlaceholderText("ID request");
                 ui->IdD->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_etatD->setPlaceholderText("request state");
                 ui->le_etatD->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_prenomD->setPlaceholderText("First Name");
                 ui->le_prenomD->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_nomD->setPlaceholderText("Name");
                 ui->le_nomD->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->lineEdit_8->setPlaceholderText("ID request");
                 ui->lineEdit_8->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->pushButton_21->setText("Delete");
                 ui->pushButton_21->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->recherche_dem->setPlaceholderText("research");
                 ui->recherche_dem->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->numparcelleC->setPlaceholderText("plot number");
                 ui->numparcelleC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->surfaceC->setPlaceholderText("area");
                 ui->surfaceC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->nomC->setPlaceholderText("Name");
                 ui->nomC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->prenomC->setPlaceholderText("First Name");
                 ui->prenomC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->supp_numPC->setPlaceholderText("plote number");
                 ui->supp_numPC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->rechercheC->setPlaceholderText("research");
                 ui->rechercheC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");

                 ui->pushButton_17->setText("Modify");
                 ui->pushButton_17->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->Ajouter_demande_pb->setText("Add");
                 ui->Ajouter_demande_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->pushButton_27->setText("Sort ASC");
                 ui->pushButton_27->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->pushButton_26->setText("Sort DSC");
                 ui->pushButton_26->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->AjouterC->setText("Add");
                 ui->AjouterC->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->modifierC->setText("Modify");
                 ui->modifierC->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->pushButton_18->setText("Urbanism");
                 ui->pushButton_18->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");


                 ui->comboBox->clear();
                    QStringList list5;
                    list5<<"Salary"<<"date"<<"Name"<<"ID";
                    ui->comboBox->addItems(list5);

                    ui->combo_boxtri->clear();
                       QStringList list6;
                       list6<<"ID training"<<"ID trainer"<<"Date"<<"Duration";
                       ui->combo_boxtri->addItems(list6);

                       ui->combobox_tri_encaissement->clear();
                          QStringList list7;
                          list7<<"Code"<<"date"<<"Payment Method"<<"Amount"<<"remark<<";
                          ui->combobox_tri_encaissement->addItems(list7);

                          ui->combobox_tri_decaissement->clear();
                             QStringList list8;
                             list8<<"Code"<<"date"<<"Amount"<<"Payment Method"<<"remark<<";
                             ui->combobox_tri_decaissement->addItems(list8);

                             ui->combo_reclam_tri->clear();
                                QStringList list9;
                                list9<<"ID"<<"location<<";
                                ui->combo_reclam_tri->addItems(list9);

                                ui->combocit->clear();
                                   QStringList list10;
                                   list10<<"Name"<<"ID<<";
                                   ui->combocit->addItems(list10);

                                   ui->combo_mehode_decaissement->clear();
                                      QStringList list20;
                                      list20<<"Payment method"<<"choice"<<"virement"<<"check"<<"credit card";
                                      ui->combo_mehode_decaissement->addItems(list20);

                                      ui->modifierV->setText("Modify");
                                      ui->modifierV->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                                      ui->ajouterV->setText("Add");
                                      ui->ajouterV->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
 ui->ajouterequi->setText("Add");
ui->ajouterequi->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
ui->pushButton_25->setText("Delete");
ui->pushButton_25->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");

ui->IDVS->setPlaceholderText("ID vehicle");
ui->IDVS->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
ui->nomV->setPlaceholderText("vehicle Name");
ui->nomV->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
ui->refV->setPlaceholderText("reference");
ui->refV->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
ui->idV->setPlaceholderText("ID vehicle");
ui->idV->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
ui->NOMA->setPlaceholderText("Name");
ui->NOMA->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
ui->REFA->setPlaceholderText("reference");
ui->REFA->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
ui->comboV->clear();
   QStringList list22;
   list22<<"identifier"<<"Name"<<"reference";
   ui->comboV->addItems(list22);
}

void Ressources_Humaines::on_francais_clicked()
{
    lang="fr";
    ui->menu_rh->setText("Ressources Humaines");
    ui->menu_rh->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->menu_fn->setText("Finance");
    ui->menu_fn->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->pushButton_19->setText("Citoyens");
    ui->pushButton_19->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->test->setText("Municipalité");
    ui->test->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->code_encaissement->setPlaceholderText("Code");
    ui->code_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->montant_encaissement->setPlaceholderText("Montant");
    ui->montant_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->remarque_encaissement->setPlaceholderText("Remarque");
    ui->remarque_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");

    ui->combo_mehode_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->encaissement_pb->setText("Valider");
    ui->encaissement_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->modifier_encaissement->setText("Modifier");
    ui->modifier_encaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->supprimer_encaissement->setText("Supprimer");
    ui->supprimer_encaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trier_encaissement->setText("Trier");
    ui->trier_encaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->chercher_encaissement->setPlaceholderText("Rechercher");
    ui->chercher_encaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");


    ui->le_reclamation->setPlaceholderText("Réclamation");
    ui->le_reclamation->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->groupBox->setTitle("Ajouter/Modifier Réclamation");
    ui->groupBox->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->groupBox_2->setTitle("Supprimer");
    ui->groupBox_2->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->groupBox_3->setTitle("Affichage et Tri");
    ui->groupBox_3->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->groupBox_4->setTitle("Exporter en PDF");
    ui->groupBox_4->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->modifier_reclam_pb->setText("Modifier");
    ui->modifier_reclam_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->ajouter_reclam_pb->setText("Ajouter");
    ui->ajouter_reclam_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->supp_reclam_pb->setText("Supprimer");
    ui->supp_reclam_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->chercher_reclam_pb->setText("Chercher");
    ui->chercher_reclam_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->tri_pb_reclam->setText("Trier");
    ui->tri_pb_reclam->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->export_reclam->setText("Exporter");
    ui->export_reclam->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->ArduinoON->setText("Marche");
    ui->ArduinoON->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->ArduinoOFF->setText("Arrêt");
    ui->ArduinoOFF->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->label_7->setText("Emplacement");
    ui->label_8->setText("Raison");


    ui->code_decaissement->setPlaceholderText("Code");
    ui->code_decaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->montant_decaissement->setPlaceholderText("Montant");
    ui->montant_decaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->remarque_decaissement->setPlaceholderText("Remarque");
    ui->remarque_decaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->chercher_decaissement->setPlaceholderText("Rechercher");
    ui->chercher_decaissement->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->decaissement_pb_valider->setText("Valider");
    ui->decaissement_pb_valider->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->modifier_decaissement->setText("Modifier");
    ui->modifier_decaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->supprimer_decaissement->setText("Supprimer");
    ui->supprimer_decaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trier_decaissement->setText("Trier");
    ui->trier_decaissement->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");



    ui->trier_cit->setText("Trier");
    ui->trier_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->export_cit->setText("Exporter en PDF");
    ui->export_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->ajouter_cit->setText("Ajouter");
    ui->ajouter_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->modifier_cit->setText("Modifier");
    ui->modifier_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->supp_cit->setText("Supprimer");
    ui->supp_cit->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->Bshow->setText("Afficher");
    ui->Bshow->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->groupBox_6->setTitle("Ajout et Modification");
    ui->groupBox_6->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->groupBox_8->setTitle("Supprimer");
    ui->groupBox_8->setStyleSheet("background-color: rgb(41, 45, 56); border-radius: 5px;");
    ui->nom_cit->setPlaceholderText("Nom");
    ui->nom_cit->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->prenom_cit->setPlaceholderText("Prénom");
    ui->prenom_cit->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->chercher_cit->setPlaceholderText("Chercher ID");
    ui->chercher_cit->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");

    ui->pb_suprrr->setText("Supprimer");
    ui->pb_suprrr->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->Aj_mf_pb->setText("Ajouter/Modifier");
    ui->Aj_mf_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trinum_pb->setText("Trier par Numéro");
    ui->trinum_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->trinom_pb->setText("Trier par Nom");
    ui->trinom_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->triprenompb->setText("Trierpar Prénom");
    ui->triprenompb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
    ui->le_recherche01->setPlaceholderText("Recherche");
    ui->le_recherche01->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
    ui->le_supppr->setText("Supprimer");
    ui->le_supppr->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");


    ui->label_2->setText("Ajouter Employés");
    ui->label_3->setText("Supprimer employés");
    ui->label->setText("Tableau d'employés");
    ui->label_4->setText("Ajouter Formation");
    ui->label_5->setText("Supprimr Formation");
    ui->label_6->setText("Tableau de Formation");
     ui->observation->setText("observation");
     ui->note->setText("note");
     ui->ajouter->setText("Ajouter");
     ui->ajouter->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->modifier->setText("Modifier");
     ui->modifier->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_3->setText("Supprimer");
     ui->pushButton_3->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_9->setText("Trier");
     ui->pushButton_9->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pb_ajouterformation->setText("Ajouter");
     ui->pb_ajouterformation->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pb_modifierformation->setText("Modifier");
     ui->pb_modifierformation->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pb_supprimerformation->setText("Supprimer");
     ui->pb_supprimerformation->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_12->setText("Trier");
     ui->pushButton_12->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->ajout1_pb->setText("Ajouter");
     ui->ajout1_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->modif1_pb->setText("Modifier");
     ui->modif1_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->supprimerdeces_pb->setText("Supprimer");
     ui->supprimerdeces_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->aj_mf_dec->setText("Ajouter/Modifier");
     ui->aj_mf_dec->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_14->setText("Trier par le Nom");
     ui->pushButton_14->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->pushButton_16->setText("Trier par le prénom");
     ui->pushButton_16->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
     ui->le_nom->setPlaceholderText("Nom");
     ui->le_nom->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_prenom->setPlaceholderText("Prénom");
     ui->le_prenom->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_salaire->setPlaceholderText("Salaire");
     ui->le_salaire->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_duree->setPlaceholderText("Durée");
     ui->le_duree->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_searchformation->setPlaceholderText("rechercher");
     ui->le_searchformation->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_idformation->setPlaceholderText("ID FOrmation");
     ui->le_idformation->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_supprimerformation->setPlaceholderText("ID Formation");
     ui->le_supprimerformation->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_nom1->setPlaceholderText("Nom");
     ui->le_nom1->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_prenom1->setPlaceholderText("Prénom");
     ui->le_prenom1->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_lieu->setPlaceholderText("Lieu");
     ui->le_lieu->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_nomdupere->setPlaceholderText("Nom du Pére");
     ui->le_nomdupere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_prenomdupere->setPlaceholderText("Prénom du Pére");
     ui->le_prenomdupere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_nommere->setPlaceholderText("Nom de la mére");
     ui->le_nommere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_prenommere->setPlaceholderText("Prénom de la Mére");
     ui->le_prenommere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_nationalite->setPlaceholderText("Nationalité");
     ui->le_nationalite->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_numeronaissance->setPlaceholderText("Numéro de naissance");
     ui->le_numeronaissance->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->le_sexe->setPlaceholderText("Sexe");
     ui->le_sexe->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->tribunal->setPlaceholderText("Tribunal");
     ui->tribunal->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->recherche_deces->setPlaceholderText("Rechercher");
     ui->recherche_deces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
     ui->supprimerdeces_pb->setText("Supprimer");
     ui->supprimerdeces_pb->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");


     ui->combo_mehode_encaissement->clear();
        QStringList list1;
        list1<<"Méthode de payement"<<"virement"<<"chéque"<<"carte bancaire"<<"éspéce";
        ui->combo_mehode_encaissement->addItems(list1);

        ui->combo_mehode_decaissement->clear();
           QStringList list21;
           list21<<"Méthode de payement"<<"virement"<<"chéque"<<"carte bancaire"<<"éspéce";
           ui->combo_mehode_decaissement->addItems(list21);

           ui->combobox_tri_decaissement->clear();
              QStringList list3;
              list3<<"code"<<"date"<<"montant"<<"méthode de payement"<<"ID employé"<<"remarque";
              ui->combobox_tri_decaissement->addItems(list3);

              ui->combobox_tri_encaissement->clear();
                 QStringList list4;
                 list4<<"code"<<"date"<<"montant"<<"méthode de payement"<<"ID employé"<<"remarque";
                 ui->combobox_tri_encaissement->addItems(list4);


                 ui->nomdeces->setPlaceholderText("Nom");
                 ui->nomdeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_prenomdeces->setPlaceholderText("Prénom");
                 ui->le_prenomdeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_lieudeces->setPlaceholderText("lieu");
                 ui->le_lieudeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_nomperedeces->setPlaceholderText("Nom du pére");
                 ui->le_nomperedeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_prenomperedeces->setPlaceholderText("prénom du pére");
                 ui->le_prenomperedeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_nommeredeces->setPlaceholderText("Nom de la mére");
                 ui->le_nommeredeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_prenommere->setPlaceholderText("prénom de la mére");
                 ui->le_prenommere->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_nationalite_2->setPlaceholderText("Nationalité");
                 ui->le_nationalite_2->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_numdeces->setPlaceholderText("Numéro décès");
                 ui->le_numdeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_sexe_deces->setPlaceholderText("sexe");
                 ui->le_sexe_deces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_tribunaldeces->setPlaceholderText("Tribunal");
                 ui->le_tribunaldeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_idcdeces->setPlaceholderText("Identité de l'officier de l'état civile");
                 ui->le_idcdeces->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_lieudeces_2->setPlaceholderText("lieu décès");
                 ui->le_lieudeces_2->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->notedeces->setText("observation");
                 ui->observationdeces->setText("note");
                 ui->Ajouterdeces_pb->setText("Ajouter");
                 ui->Ajouterdeces_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->modifierdeces_pb->setText("Modifier");
                 ui->modifierdeces_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");




                 ui->IdD->setPlaceholderText("ID demande");
                 ui->IdD->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_etatD->setPlaceholderText("état demande");
                 ui->le_etatD->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_prenomD->setPlaceholderText("Prénom");
                 ui->le_prenomD->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->le_nomD->setPlaceholderText("Nom");
                 ui->le_nomD->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->lineEdit_8->setPlaceholderText("ID demande");
                 ui->lineEdit_8->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->pushButton_21->setText("Supprimer");
                 ui->pushButton_21->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->recherche_dem->setPlaceholderText("recherche");
                 ui->recherche_dem->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->numparcelleC->setPlaceholderText("numéro parcelle");
                 ui->numparcelleC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->surfaceC->setPlaceholderText("Surface");
                 ui->surfaceC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->nomC->setPlaceholderText("Nom");
                 ui->nomC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->prenomC->setPlaceholderText("Prénom");
                 ui->prenomC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->supp_numPC->setPlaceholderText("numéro parcelle");
                 ui->supp_numPC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                 ui->rechercheC->setPlaceholderText("recherche");
                 ui->rechercheC->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");

                 ui->pushButton_17->setText("Modifier");
                 ui->pushButton_17->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->Ajouter_demande_pb->setText("Ajouter");
                 ui->Ajouter_demande_pb->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->pushButton_27->setText("Tri ASC");
                 ui->pushButton_27->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->pushButton_26->setText("Tri DSC");
                 ui->pushButton_26->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->AjouterC->setText("Ajouter");
                 ui->AjouterC->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->modifierC->setText("Modifier");
                 ui->modifierC->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                 ui->pushButton_18->setText("Urbanisme");
                 ui->pushButton_18->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");

                 ui->comboBox->clear();
                    QStringList list16;
                    list16<<"Salaire"<<"date"<<"Nom"<<"ID";
                    ui->comboBox->addItems(list16);

                    ui->combo_boxtri->clear();
                       QStringList list15;
                       list15<<"ID Formation"<<"ID Formateur"<<"Date"<<"Durée";
                       ui->combo_boxtri->addItems(list15);

                       ui->combobox_tri_encaissement->clear();
                          QStringList list14;
                          list14<<"Code"<<"date"<<"Méthode payement"<<"Montant"<<"remarque";
                          ui->combobox_tri_encaissement->addItems(list14);

                          ui->combobox_tri_decaissement->clear();
                             QStringList list13;
                             list13<<"Code"<<"date"<<"Montant"<<"Méthode payement"<<"remarque";
                             ui->combobox_tri_decaissement->addItems(list13);

                             ui->combo_reclam_tri->clear();
                                QStringList list12;
                                list12<<"ID"<<"Emplacement";
                                ui->combo_reclam_tri->addItems(list12);

                                ui->combocit->clear();
                                   QStringList list11;
                                   list11<<"Nom"<<"ID";
                                   ui->combocit->addItems(list11);

                                   ui->ajouterequi->setText("Ajouter");
                                  ui->ajouterequi->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                                  ui->pushButton_25->setText("supprimer");
                                  ui->pushButton_25->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");

                                  ui->IDVS->setPlaceholderText("ID véhicvle");
                                  ui->IDVS->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                                  ui->nomV->setPlaceholderText("véhicule Name");
                                  ui->nomV->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                                  ui->refV->setPlaceholderText("réfèrence");
                                  ui->refV->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                                  ui->idV->setPlaceholderText("ID véhicule");
                                  ui->idV->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                                  ui->NOMA->setPlaceholderText("Name");
                                  ui->NOMA->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                                  ui->REFA->setPlaceholderText("réfèrence");
                                  ui->REFA->setStyleSheet("QLineEdit {background-color: rgb(27, 29, 35);borderradius:5px;border: 2px solid rgb(27, 29, 35);padding-left: 10px;} QLineEdit:hover {border: 2px solid rgb(64, 71, 88);} QLineEdit:focus {border: 2px solid rgb(91, 101, 124); }");
                                  ui->comboV->clear();
                                     QStringList list22;
                                     list22<<"identifiant"<<"Name"<<"réfèrence";
                                     ui->modifierV->setText("Modifier");
                                     ui->modifierV->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");
                                     ui->ajouterV->setText("Ajouter");
                                     ui->ajouterV->setStyleSheet("QPushButton {border: 2px solid rgb(52, 59, 72); border-radius: 5px;	 background-color: rgb(52, 59, 72); } QPushButton:hover {background-color: rgb(57, 65, 80); border: 2px solid rgb(61, 70, 86);} QPushButton:pressed { background-color: rgb(35, 40, 49); border: 2px solid rgb(43, 50, 61);}");                      ui->comboV->addItems(list22);


}

void Ressources_Humaines::on_temp_clicked()
{
    ui->main_stacked->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(14);

}

void Ressources_Humaines::on_ExcelEMP_clicked()
{
    QTableView *table;
               table = ui->tableView;

               QString filters("CSV files (.csv);;All files (.*)");
               QString defaultFilter("CSV files (*.csv)");
               QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);
               QFile file(fileName);

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                   QTextStream data(&file);
                   QStringList strList;
                   for (int i = 0; i < model->columnCount(); i++) {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") << "\n";
                   for (int i = 0; i < model->rowCount(); i++) {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++) {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") + "\n";
                   }
                   file.close();
                   QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
               }
}

void Ressources_Humaines::on_backA_clicked()
{
    ui->main_stacked->setCurrentIndex(0);
    ui->side_stacked->setCurrentIndex(0);

}

void Ressources_Humaines::on_statEMP_clicked()
{

    statem=new lestat(this);
    statem->show();
}

void Ressources_Humaines::on_STATA_clicked()
{
    stequi=new statequi(this);
    stequi->show();
}
