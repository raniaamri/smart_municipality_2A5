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


Ressources_Humaines::Ressources_Humaines(QWidget *parent) :
    QDialog(parent),
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

/*setting up the widget page + les icones*/
ui->main_stacked->setCurrentIndex(0);
ui->side_stacked->setCurrentIndex(0);
ui->stackedWidget_2->setCurrentIndex(0);
ui->pushButton_7->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-change-userclicked-64.png"));
ui->pushButton_8->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-file-64.png"));
ui->pushButton_11->setIcon(QIcon("C:/Users/user/Documents/smartM/icons/16x16/cil-arrow-left.png"));
ui->retour_menu->setIcon(QIcon("C:/Users/user/Documents/smartM/icons/16x16/cil-arrow-left.png"));
ui->encaissement_pb_2->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/encaissementOUI.png"));
ui->decaissement_pb->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/decaissementNON.png"));
ui->stat_encaissement->setIcon(QIcon("C:/Users/user/Documents/smartMunicipality/iconet/statistiques.png"));

auto movie = new QMovie(this);
movie->setFileName("C:/Users/user/Documents/smartMunicipality/iconet/Mfinnances.gif");
connect(movie, &QMovie::frameChanged, [=]{
 ui->menu_fn->setIcon(movie->currentPixmap());
});
movie->start();

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
                        if (!ui->tableView->isColumnHidden(column))
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
    QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("C://Users//user//document//smartMunicipality//decaissement.pdf");//badel i chemin win t7eb t7ot il fichier ya2melek creation
            QPainter painter;

            if (! painter.begin(&printer)) { // failed to open file
                qWarning("failed to open file, is it writable?");
            }

            QSqlQuery   query ;
            qDebug() << query.prepare("select sysdate from dual  "); //date systeme
            if ( query.exec() )
            {

                QString S= QDate::currentDate().toString();
                painter.drawText(850,50,S);
                QPen penred(Qt::black);

                painter.setFont(QFont("Arial", 30));
                penred.setWidth(1);
                painter.setPen(penred);

                painter.drawText(250,100," Decaissement ");
                painter.setFont(QFont("Arial",30));
                painter.setPen(Qt::black);

            }

            QString code_decaissement,date_decaissement,methode_decaissement ,id_employe,montant_decaissement, remarque_decaissement;
            QSqlQuery   qry ;
            int i =50;
            int k=0;
            qDebug() << qry.prepare("select * from DECAISSEMENT ");
            painter.drawPixmap(600,10,100,100,QPixmap::fromImage(QImage("C:/Users/asus/Desktop/smartMunicipality/logo")));//chemin mta3 il logo

            if ( qry.exec() )
            {

                while(qry.next())
                {

                    if ( k % 13 ==0)
                    {   i=250;
                        painter.setFont(QFont("Arial",10));
                        QPen penblack(Qt::black);

                        painter.setPen(penblack);
        painter.drawText (0,150,"code");
        painter.drawText (130,150,"date");
        painter.drawText (290,150,"methode");
        painter.drawText (400,150,"id_employe");
        painter.drawText (500,150,"montant");
        painter.drawText(620,150,"remarque ");
                    }

                    painter.setFont(QFont("Arial",10));
                    QPen penblack(Qt::black);

                    painter.setPen(penblack);
                    int j=0;
                    code_decaissement= qry.value(0).toString();
                    painter.drawText(j*20,i, code_decaissement);
                    j++;
                    date_decaissement=qry.value(1).toString();
                    painter.drawText(j*120,i, date_decaissement);
                    j++;
                   methode_decaissement=qry.value(2).toString();
                    painter.drawText(j*150,i, methode_decaissement);
                    j++;
                    id_employe=qry.value(3).toString();
                    painter.drawText(j*133,i, id_employe);
                    j++;
                   montant_decaissement=qry.value(4).toString();
                    painter.drawText(j*125,i, montant_decaissement);
                    j++;
                   remarque_decaissement=qry.value(5).toString();
                     painter.drawText(j*124,i, remarque_decaissement);
                    i+=80;
                    k++;

                }
            }

            painter.end();
}

void Ressources_Humaines::on_pdf_encaisssement_clicked()
{
    QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("C://Users//user//document//smartMunicipality//encaissement.pdf");//badel i chemin win t7eb t7ot il fichier ya2melek creation
            QPainter painter;

            if (! painter.begin(&printer)) { // failed to open file
                qWarning("failed to open file, is it writable?");
            }

            QSqlQuery   query ;
            qDebug() << query.prepare("select sysdate from dual  "); //date systeme
            if ( query.exec() )
            {

                QString S= QDate::currentDate().toString();
                painter.drawText(850,50,S);
                QPen penred(Qt::black);

                painter.setFont(QFont("Arial", 30));
                penred.setWidth(1);
                painter.setPen(penred);

                painter.drawText(250,100," Encaissement ");
                painter.setFont(QFont("Arial",30));
                painter.setPen(Qt::black);

            }

            QString code_encaissement,date_encaissement,methode_encaissement ,id_employe,montant_encaissement, remarque_encaissement;
            QSqlQuery   qry ;
            int i =50;
            int k=0;
            qDebug() << qry.prepare("select * from encaissement ");
            painter.drawPixmap(600,10,100,100,QPixmap::fromImage(QImage("C:/Users/asus/Desktop/smart-muni/logo")));//chemin mta3 il logo

            if ( qry.exec() )
            {

                while(qry.next())
                {

                    if ( k % 13 ==0)
                    {   i=250;
                        painter.setFont(QFont("Arial",10));
                        QPen penblack(Qt::black);

                        painter.setPen(penblack);
        painter.drawText (0,150,"code");
        painter.drawText (130,150,"date");
        painter.drawText (290,150,"methode");
        painter.drawText (400,150,"id_employe");
        painter.drawText (500,150,"montant");
        painter.drawText(620,150,"remarque ");
                    }

                    painter.setFont(QFont("Arial",10));
                    QPen penblack(Qt::black);

                    painter.setPen(penblack);
                    int j=0;
                    code_encaissement= qry.value(0).toString();
                    painter.drawText(j*20,i, code_encaissement);
                    j++;
                    date_encaissement=qry.value(1).toString();
                    painter.drawText(j*120,i, date_encaissement);
                    j++;
                   methode_encaissement=qry.value(2).toString();
                    painter.drawText(j*150,i, methode_encaissement);
                    j++;
                    id_employe=qry.value(3).toString();
                    painter.drawText(j*133,i, id_employe);
                    j++;
                   montant_encaissement=qry.value(4).toString();
                    painter.drawText(j*125,i, montant_encaissement);
                    j++;
                   remarque_encaissement=qry.value(5).toString();
                     painter.drawText(j*124,i, remarque_encaissement);
                    i+=80;
                    k++;

                }
            }

            painter.end();
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

}

void Ressources_Humaines::on_cit_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
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
    ui->stackedWidget_2->setCurrentIndex(6);
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
                QString data = ui->tableView->model()->data(ui->tabbaladia->model()->index(row, column)).toString().simplified();
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
}

void Ressources_Humaines::on_retourmenu_clicked()
{
    ui->main_stacked->setCurrentIndex(0);
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
        ui->tab_deces->setModel(de.afficher_deces());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout deces"),
                              QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}
