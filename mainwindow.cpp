#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "formation.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

/*controle de saisie*/
    ui->setupUi(this);
ui->le_id->setValidator(new QIntValidator(100, 999, this));
ui->le_id_supp->setValidator(new QIntValidator(100, 999, this));
ui->le_supprimerformation->setValidator(new QIntValidator(100, 999, this));
ui->le_salaire->setValidator(new QIntValidator(100,99999, this));
ui->le_nom->setMaxLength(10);
ui->le_prenom->setMaxLength(10);
ui->le_idformation->setValidator(new QIntValidator(100,999, this));

/*setting up the widget page + les icones*/
ui->stackedWidget_2->setCurrentIndex(0);
ui->pushButton_7->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-change-userclicked-64.png"));
ui->pushButton_8->setIcon(QIcon("c:/Users/user/Documents/Ressources_Humaines/icons/16x16/icons8-file-64.png"));

}


MainWindow::~MainWindow()
{

    delete ui;
}






void MainWindow::on_ajouter_clicked()
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
            /* Animation mainwindow*/
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

void MainWindow::on_pushButton_3_clicked()
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


void MainWindow::on_pushButton_7_clicked()
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

        /*fade in effect lel stacked widget*/
        QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
        ui->stackedWidget_2->setGraphicsEffect(eff);
        QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
        a->setDuration(350);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        a->start(QPropertyAnimation::DeleteWhenStopped);


}

void MainWindow::on_pushButton_8_clicked()
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




void MainWindow::on_modifier_clicked()
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



void MainWindow::on_le_id_search_textChanged(const QString &arg1)
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


void MainWindow::on_pushButton_9_clicked()
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











void MainWindow::on_pushButton_10_clicked()
{
    /* faragh lineEdits kol*/
    ui->le_id->setText("");
    ui->le_prenom->setText("");
    ui->le_nom->setText("");
    ui->le_salaire->setText("");
    ui->le_id_supp->setText("");


}


void MainWindow::on_pb_ajouterformation_clicked()
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



void MainWindow::on_pb_modifierformation_clicked()
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

void MainWindow::on_le_searchformation_textChanged(const QString &arg1)
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

void MainWindow::on_pb_supprimerformation_clicked()
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




void MainWindow::on_pushButton_2_clicked()
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

void MainWindow::on_export_2_clicked()
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

void MainWindow::on_pushButton_12_clicked()
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

void MainWindow::on_pushButton_6_clicked()
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
