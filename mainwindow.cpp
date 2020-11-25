#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qmessagebox.h>
#include <QSqlQuery>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->tableView->setModel(naissance_temporaire.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Ajouter_clicked()
{
    int cin=ui->lineEdit->text().toInt();
    QString nome=ui->lineEdit_Nom->text();
    QString prenome=ui->lineEdit_Prenom->text();
    QString lieu_de_naissance=ui->lineEdit_lieu_de_naissance->text();
    QString nomPere=ui->lineEdit_nom_du_pere->text();
    QString prenompere=ui->lineEdit_prenom_du_pere->text();
    QString nommere=ui->lineEdit_nom_de_mere->text();
    QString prenommere=ui->lineEdit_prenom_de_mere->text();
    QString nationalite=ui->lineEdit_nationalite->text();
    QString sexe=ui->lineEdit_3->text();
    QString tribunal=ui->lineEdit_TRIBUNAL->text();
    QString officier=ui->lineEdit_OFFICIER->text();
    QString note=ui->textEdit_2->accessibleDescription();
    QString observations=ui->textEdit->accessibleDescription();
    QDate date_de_naissance=ui->dateEdit_2->date();
    QDate date_de_declaration=ui->dateEdit->date();

    naissance n(cin,nome,prenome,lieu_de_naissance,nomPere,prenompere,nommere,prenommere,nationalite,sexe,tribunal,officier,note,observations,date_de_naissance,date_de_declaration);
    bool test=n.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout naissance"),
                                 QObject::tr("ajout avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(naissance_temporaire.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout naissance"),
                              QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_Modifier_clicked()
{
    naissance_temporaire.setCIN(ui->lineEdit->text().toInt());
    naissance_temporaire.setNom(ui->lineEdit_Nom->text());
    naissance_temporaire.setlieu_de_naissance(ui->lineEdit_lieu_de_naissance->text());
    naissance_temporaire.setnom_pere(ui->lineEdit_nom_du_pere->text());
    naissance_temporaire.setprenom_pere(ui->lineEdit_prenom_du_pere->text());
    naissance_temporaire.setnom_dela_mere(ui->lineEdit_nom_de_mere->text());
    naissance_temporaire.setprenom_dela_mere(ui->lineEdit_prenom_de_mere->text());
    naissance_temporaire.setnationalite(ui->lineEdit_nationalite->text());
    naissance_temporaire.setsexe(ui->lineEdit_3->text());
    naissance_temporaire.setidentite_de_declarant(ui->lineEdit_TRIBUNAL->text());
    naissance_temporaire.setidentite_de_officier(ui->lineEdit_OFFICIER->text());
    naissance_temporaire.setnote(ui->textEdit_2->accessibleDescription());
    naissance_temporaire.setobservations(ui->textEdit->accessibleDescription());
    naissance_temporaire.setdate_de_naissance(ui->dateEdit_2->date());
    naissance_temporaire.setdate_de_declaration(ui->dateEdit->date());

    if(naissance_temporaire.modifier())
    {
        QMessageBox::information(nullptr, QObject::tr("modifier une naissance"),
                                 QObject::tr("modification avec succès !!.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(naissance_temporaire.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier une naissance"),
                              QObject::tr("modification échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_Supprimer_clicked()
{
    int cin=ui->lineEdit_Suppression->text().toInt();
    bool test=naissance_temporaire.supprimer(cin);
    if(test){
        QMessageBox::information(nullptr, QObject::tr("suppression naissannce"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(naissance_temporaire.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("suppression naissance"),
                              QObject::tr("suppression échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);


}

//deces
void MainWindow::on_Ajouter_d_clicked()
{
    int cind=ui->lineEdit->text().toInt();
    QString nomed=ui->lineEdit_Nom_2->text();
    QString prenomed=ui->lineEdit_Prenomd->text();
    QString lieu_de_naissanced=ui->lineEdit_lieu_de_naissanced->text();
    QString lieu_de_deces=ui->lineEdit_6->text();
    QString nomPered=ui->lineEdit_nompered->text();
    QString prenompered=ui->lineEdit_prenom_du_pere_2->text();
    QString nommered=ui->lineEdit_nom_de_mere_2->text();
    QString prenommered=ui->lineEdit_prenom_de_mere_2->text();
    QString nationalited=ui->lineEdit_nationalite_2->text();
    QString sexed=ui->lineEdit_5->text();
    QString tribunald=ui->lineEdit_TRIBUNAL_2->text();
    QString officierd=ui->lineEdit_OFFICIER_2->text();
    QString noted=ui->textEdit_4->accessibleDescription();
    QString observationsd=ui->textEdit_3->accessibleDescription();
    QDate date_de_naissanced=ui->dateEdit_3->date();
    QDate date_de_declarationd=ui->dateEdit_4->date();
    QDate date_de_deces=ui->dateEdit_5->date();


    deces d(cind,nomed,prenomed,lieu_de_naissanced,nomPered,prenompered,nommered,prenommered,nationalited,sexed,tribunald,officierd,noted,observationsd,lieu_de_deces,date_de_naissanced,date_de_declarationd,date_de_deces);
    bool test=d.ajouter_deces();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout deces"),
                                 QObject::tr("ajout avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(deces_temporaire.afficher_deces());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout deces"),
                              QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_modifier_d_clicked()
{

}

void MainWindow::on_supprimer_d_clicked()
{

}
