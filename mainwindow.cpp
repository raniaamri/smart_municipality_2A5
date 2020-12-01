#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qmessagebox.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTextDocument>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QPrinter>
#include <QTextDocument>
#include<QTextStream>
#include<QtDebug>
#include<QDir>
#include<QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_cin->setValidator(new QIntValidator(0,99999999,this));
    ui->tableView->setModel(naissance_temporaire.afficher());
    ui->tableView_3->setModel(deces_temporaire.afficher_deces());

}

MainWindow::~MainWindow()
{
    delete ui;
}

//CRUD de NAISSANCE
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
    QString observations=ui->textEdit->toPlainText();
    QString note=ui->textEdit_2->toPlainText();

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
    naissance_temporaire.setPrenom(ui->lineEdit_Prenom->text());

    naissance_temporaire.setlieu_de_naissance(ui->lineEdit_lieu_de_naissance->text());
    naissance_temporaire.setnom_pere(ui->lineEdit_nom_du_pere->text());
    naissance_temporaire.setprenom_pere(ui->lineEdit_prenom_du_pere->text());
    naissance_temporaire.setnom_dela_mere(ui->lineEdit_nom_de_mere->text());
    naissance_temporaire.setprenom_dela_mere(ui->lineEdit_prenom_de_mere->text());
    naissance_temporaire.setnationalite(ui->lineEdit_nationalite->text());
    naissance_temporaire.setsexe(ui->lineEdit_3->text());
    naissance_temporaire.setidentite_de_declarant(ui->lineEdit_TRIBUNAL->text());
    naissance_temporaire.setidentite_de_officier(ui->lineEdit_OFFICIER->text());
    naissance_temporaire.setnote(ui->textEdit_2->toPlainText());
    naissance_temporaire.setobservations(ui->textEdit->toPlainText());
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

//CRUD de DECES!!!!!!!!!!!!!!!!!!!!


void MainWindow::on_Ajouter_d_clicked()
{
    int cind=ui->lineEdit_cin->text().toInt();
    QString nomed=ui->lineEdit_Nom_2->text();
    QString prenomed=ui->lineEdit_Prenomd->text();
    QString lieu_de_naissanced=ui->lineEdit_lieu_de_naissanced->text();

    QString nomPered=ui->lineEdit_nompered->text();
    QString prenompered=ui->lineEdit_prenom_du_pere_2->text();
    QString nommered=ui->lineEdit_nom_de_mere_2->text();
    QString prenommered=ui->lineEdit_prenom_de_mere_2->text();
    QString nationalited=ui->lineEdit_nationalite_2->text();
    QString sexed=ui->lineEdit_5->text();
    QString tribunald=ui->lineEdit_TRIBUNAL_2->text();
    QString officierd=ui->lineEdit_OFFICIER_2->text();
    QString noted=ui->textEdit_4->toPlainText();
    QString observationsd=ui->textEdit_3->toPlainText();
    QString lieu_de_deces=ui->lineEdit_6->text();
    QDate date_de_naissanced=ui->dateEdit_3->date();
    QDate date_de_declarations_dedeces=ui->dateEdit_4->date();
    QDate date_de_deces=ui->dateEdit_5->date();


    deces d(cind,nomed,prenomed,lieu_de_naissanced,nomPered,prenompered,nommered,prenommered,nationalited,sexed,tribunald,officierd,noted,observationsd,lieu_de_deces,date_de_naissanced,date_de_declarations_dedeces,date_de_deces);
    bool test=d.ajouter_deces();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout deces"),
                                 QObject::tr("ajout avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_3->setModel(deces_temporaire.afficher_deces());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout deces"),
                              QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_modifier_d_clicked()
{
    deces_temporaire.setCINd(ui->lineEdit_cin->text().toInt());
    deces_temporaire.setNomd(ui->lineEdit_Nom_2->text());
    deces_temporaire.setPrenomd(ui->lineEdit_Prenomd->text());

    deces_temporaire.setlieu_de_naissanced(ui->lineEdit_lieu_de_naissanced->text());
    deces_temporaire.setnom_pered(ui->lineEdit_nompered->text());
    deces_temporaire.setprenom_pered(ui->lineEdit_prenom_du_pere_2->text());
    deces_temporaire.setnom_dela_mered(ui->lineEdit_nom_de_mere_2->text());
    deces_temporaire.setprenom_dela_mered(ui->lineEdit_prenom_de_mere_2->text());
    deces_temporaire.setnationalited(ui->lineEdit_nationalite_2->text());
    deces_temporaire.setsexed(ui->lineEdit_5->text());
    deces_temporaire.setidentite_de_declarantd(ui->lineEdit_TRIBUNAL_2->text());
    deces_temporaire.setidentite_de_officierd(ui->lineEdit_OFFICIER_2->text());
    deces_temporaire.setnoted(ui->textEdit_4->toPlainText());
    deces_temporaire.setobservationsd(ui->textEdit_3->toPlainText());
    deces_temporaire.setlieu_de_deces(ui->lineEdit_6->text());
    deces_temporaire.setdate_de_naissanced(ui->dateEdit_3->date());
    deces_temporaire.setdate_de_declarations_dedeces(ui->dateEdit_4->date());
    deces_temporaire.setdate_de_deces(ui->dateEdit_5->date());

    if(deces_temporaire.modifier_deces())
    {
        QMessageBox::information(nullptr, QObject::tr("modifier une deces"),
                                 QObject::tr("modification avec succès !!.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_3->setModel(deces_temporaire.afficher_deces());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier une deces"),
                              QObject::tr("modification échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_supprimer_d_clicked()
{
    int cin=ui->lineEdit_4->text().toInt();
    bool test=deces_temporaire.supprimer_deces(cin);
    if(test){
        QMessageBox::information(nullptr, QObject::tr("suppression deces"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_3->setModel(deces_temporaire.afficher_deces());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("suppression deces"),
                              QObject::tr("suppression échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);


}

// LES métiers de la classe NAISSANCE
void MainWindow::on_pushButton_tri_parNom_clicked()
{
    ui->tableView->setModel(naissance_temporaire.afficher_tri_nom());
}

void MainWindow::on_pushButton_tri_parPrenom_clicked()
{
    ui->tableView->setModel(naissance_temporaire.afficher_tri_prenom());
}

void MainWindow::on_lineEdit_recherche_dynamique_textChanged(const QString &arg1)
{
    QString nom = ui->lineEdit_recherche_dynamique->text();
    ui->tableView->setModel(naissance_temporaire.recherche_dynamique(nom));
}



void MainWindow::on_pushButton_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount =ui->tableView->model()->columnCount();
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


    //  QTextDocument document;
    // document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName("naissance.pdf");
    document->print(&printer);
    QDesktopServices::openUrl(QUrl::fromLocalFile("naissance.pdf"));
}



void MainWindow::on_pushButton_tri_clicked()
{
    ui->tableView->setModel(naissance_temporaire.tri_tri());
}


// LES métiers de la classe DECES
void MainWindow::on_pushButton_13_clicked()
{
    ui->tableView_3->setModel(deces_temporaire.afficher_tri_nom());
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->tableView_3->setModel(deces_temporaire.afficher_tri_prenom());
}

void MainWindow::on_lineEdit_recherche_dynamique_deces_textChanged(const QString &arg1)
{
    QString nom = ui->lineEdit_recherche_dynamique_deces->text();
    ui->tableView_3->setModel(deces_temporaire.recherche_dynamique(nom));
}
