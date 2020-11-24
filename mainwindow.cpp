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
        QMessageBox::critical(nullptr, QObject::tr("Ajout etudiant"),
                              QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_Modifier_clicked()
{

}

void MainWindow::on_pushButton_Supprimer_clicked()
{

}
