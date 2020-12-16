#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include"encaissement.h"
#include <QMessageBox>
#include <QFile>
#include <QPrinter>
#include <QDebug>
#include <QPainter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QTextDocument>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQueryModel *model=new QSqlQueryModel();
           QSqlQuery qry;
           qry.prepare("select ID from EMPLOYE");
           qry.exec();
           model->setQuery(qry);
           ui->id_em_en->setModel(model);
           ui->id_em_en->setCurrentIndex(-1);
           ui->id_em_dec->setModel(model);
           ui->id_em_dec->setCurrentIndex(-1);
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->tableau_en->setModel(tab_encaissement.afficher());

    ui->tab_de->setModel(tab_decaissement.afficher());
    ui->stackedWidget->setCurrentIndex(1);
     ui->stackedWidget_3->setCurrentIndex(1);
    ui->stackedWidget_4->setCurrentIndex(1);
    click = new QMediaPlayer();
            click->setMedia(QUrl::fromLocalFile("C:/Users/asus/Desktop/smart-muni/click.mp3"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_valider_clicked()
{
    click->play();
    int id_employe=ui->id_em_en->currentText().toInt();
    QString methode_encaissement=ui->methode_encaissement->currentText();
    QString remarque_encaissement=ui->remarque_encaissement->text();
    QString montant_encaissement=ui->montant_encaissement->text();
    encaissement en(methode_encaissement, montant_encaissement ,id_employe , remarque_encaissement);
    bool test=en.ajouter();
    if(ui->id_em_en->currentIndex()==-1||ui->montant_encaissement->text().isEmpty()||ui->methode_encaissement->currentText()=="choix")
    {QMessageBox::warning(nullptr, QObject::tr("erreur"),
                              QObject::tr("verifier les champs.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);}
    else{
    if(test)
    {
        if(lang=="fr")
        {

       ui->tableau_en->setModel(tab_encaissement.afficher());
       QMessageBox::information(nullptr, QObject::tr("Ajouter encaissement"),
       QObject::tr("encaissement ajoutée.\n"
       "Click Cancel to exit."), QMessageBox::Cancel);
       ui->id_em_en->setCurrentIndex(-1);
       ui->montant_encaissement->clear();
       ui->methode_encaissement->setCurrentIndex(0);
       ui->remarque_encaissement->clear();
       }
else
            if(lang=="ang")
            {
                ui->tableau_en->setModel(tab_encaissement.afficher_ang());
                QMessageBox::information(nullptr, QObject::tr("add collection"),
                QObject::tr("collection added.\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
                ui->id_em_en->setCurrentIndex(-1);
                ui->montant_encaissement->clear();
                ui->methode_encaissement->setCurrentIndex(0);
                ui->remarque_encaissement->clear();
            }

    }
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    click->play();
   int id_em_dec=ui->id_em_dec->currentText().toInt();
   QString methode_decaissement=ui->methode_decaissement->currentText();
    QString remarque_decaissement=ui->remarque_decaissement->text();
    QString montant_decaissement=ui->montant_decaissement->text();
    decaissement de(methode_decaissement, montant_decaissement ,id_em_dec , remarque_decaissement);
    bool test=de.ajouter();
    if(ui->id_em_dec->currentIndex()==-1||ui->montant_decaissement->text().isEmpty()||ui->methode_decaissement->currentText()=="choix")
    {QMessageBox::warning(nullptr, QObject::tr("erreur"),
                              QObject::tr("verifier les champs.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);}
    else{
    if(test)
    {
       ui->tab_de->setModel(tab_decaissement.afficher());
       QMessageBox::information(nullptr, QObject::tr("Ajouter decaissement"),
       QObject::tr("decaissement ajoutée.\n"
       "Click Cancel to exit."), QMessageBox::Cancel);
       ui->id_em_dec->setCurrentIndex(-1);
       ui->montant_decaissement->clear();
       ui->methode_decaissement->setCurrentIndex(0);
       ui->remarque_decaissement->clear();

    }
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    click->play();
stat=new statistique(this);
stat->show();



}

void MainWindow::on_pushButton_2_clicked()
{
    click->play();
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_confirmer_la_modification_clicked()
{
    click->play();
    int id_employe=ui->id_em_en_3->text().toInt() ;
    QString methode_encaissement=ui->methode_encaissement_4->currentText();
    QString remarque_encaissement=ui->remarque_encaissement_3->text();
    QString montant_encaissement=ui->montant_encaissement_3->text();
    encaissement en(methode_encaissement, montant_encaissement ,id_employe , remarque_encaissement);
    bool test=en.modifier();
    if(test)
    {
       ui->tableau_en->setModel(tab_encaissement.afficher());
       QMessageBox::information(nullptr, QObject::tr("modifier encaissement"),
       QObject::tr("encaissement modifiée.\n"
       "Click Cancel to exit."), QMessageBox::Cancel);

    }
}


void MainWindow::on_pushButton_5_clicked()
{
    click->play();
   ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_pushButton_15_clicked()
{
    click->play();
    ui->stackedWidget_3->setCurrentIndex(2);
}

void MainWindow::on_pushButton_10_clicked()
{
    click->play();
     ui->stackedWidget_4->setCurrentIndex(0);
}


void MainWindow::on_pushButton_14_clicked()
{
    click->play();
    ui->stackedWidget_4->setCurrentIndex(2);
}

void MainWindow::on_pdf_clicked()
{
    click->play();
    QString strStream;
                               QTextStream out(&strStream);
                               const int rowCount = ui->tableau_en->model()->rowCount();
                               const int columnCount =ui->tableau_en->model()->columnCount();

                               out <<  "<html>\n"
                                       "<head>\n"
                                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                       <<  QString("<title>%1</title>\n").arg("Encaissement")
                                       <<  "</head>\n"
                                       "<body bgcolor=#ffffff link=#5000A0>\n"
                                           "<img src='C:/Users/asus/Desktop/smart-muni/logo' width='100' height='100'>\n"
                                           "<h1>Encaissement </h1>"



                                           "<table border=1 cellspacing=0 cellpadding=2>\n";


                               // headers
                                   out << "<thead><tr bgcolor=#f0f0f0>";
                                   for (int column = 0; column < columnCount; column++)
                                       if (!ui->tableau_en->isColumnHidden(column))
                                           out << QString("<th>%1</th>").arg(ui->tableau_en->model()->headerData(column, Qt::Horizontal).toString());
                                   out << "</tr></thead>\n";
                                   // data table
                                      for (int row = 0; row < rowCount; row++) {
                                          out << "<tr>";
                                          for (int column = 0; column < columnCount; column++) {
                                              if (!ui->tableau_en->isColumnHidden(column)) {
                                                  QString data = ui->tableau_en->model()->data(ui->tableau_en->model()->index(row, column)).toString().simplified();
                                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                              }
                                          }
                                          out << "</tr>\n";
                                      }
                                      out <<  "</table>\n"
                                          "</body>\n"
                                          "</html>\n";
                                      QTextDocument * document = new  QTextDocument ();

                           document->setHtml(strStream);



                           QPrinter printer(QPrinter::PrinterResolution);

                                                       document-> setHtml (strStream);

                                                       QPrinter QPrinter;

                                                       QPrintDialog * dialog = new  QPrintDialog (& QPrinter, NULL );
                                                       if (dialog-> exec () == QDialog::Accepted) {
                                                           document-> print (& QPrinter);}
}

void MainWindow::on_supprimer_clicked()
{
    click->play();
int row=ui->tableau_en->selectionModel()->currentIndex().row();
QString code_supprimer=ui->tableau_en->model()->index(row,0).data().toString();
bool test=tab_encaissement.supprimer(code_supprimer);
if(row==-1)
{ QMessageBox::critical(nullptr, QObject::tr("Supprimer"),
                        QObject::tr("Erreur selectionnez visite que vous voulez le supprimer!.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}
else
{
if(test)
{
    ui->tableau_en->setModel(tab_encaissement.afficher());
    QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                QObject::tr("encaissement supprimé.\n"
                            "Click Cancel" ),QMessageBox::Cancel);
}
}
}



void MainWindow::on_pdf_dec_clicked()
{
    {
        click->play();

        QString strStream;
                                  QTextStream out(&strStream);
                                  const int rowCount = ui->tab_de->model()->rowCount();
                                  const int columnCount =ui->tab_de->model()->columnCount();

                                  out <<  "<html>\n"
                                          "<head>\n"
                                          "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                          <<  QString("<title>%1</title>\n").arg("Decaissement")
                                          <<  "</head>\n"
                                          "<body bgcolor=#ffffff link=#5000A0>\n"
                                              "<img src='C:/Users/asus/Desktop/smart-muni/logo' width='100' height='100'>\n"
                                              "<h1>Decaissement </h1>"



                                              "<table border=1 cellspacing=0 cellpadding=2>\n";


                                  // headers
                                      out << "<thead><tr bgcolor=#f0f0f0>";
                                      for (int column = 0; column < columnCount; column++)
                                          if (!ui->tab_de->isColumnHidden(column))
                                              out << QString("<th>%1</th>").arg(ui->tab_de->model()->headerData(column, Qt::Horizontal).toString());
                                      out << "</tr></thead>\n";
                                      // data table
                                         for (int row = 0; row < rowCount; row++) {
                                             out << "<tr>";
                                             for (int column = 0; column < columnCount; column++) {
                                                 if (!ui->tab_de->isColumnHidden(column)) {
                                                     QString data = ui->tab_de->model()->data(ui->tab_de->model()->index(row, column)).toString().simplified();
                                                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                 }
                                             }
                                             out << "</tr>\n";
                                         }
                                         out <<  "</table>\n"
                                             "</body>\n"
                                             "</html>\n";
                                         QTextDocument * document = new  QTextDocument ();

                              document->setHtml(strStream);



                              QPrinter printer(QPrinter::PrinterResolution);

                                                          document-> setHtml (strStream);

                                                          QPrinter QPrinter;

                                                          QPrintDialog * dialog = new  QPrintDialog (& QPrinter, NULL );
                                                          if (dialog-> exec () == QDialog::Accepted) {
                                                              document-> print (& QPrinter);}
    }
}

void MainWindow::on_supprimer_2_clicked()

    {
    click->play();
    int row=ui->tab_de->selectionModel()->currentIndex().row();
    QString code_supprimer=ui->tab_de->model()->index(row,0).data().toString();
    bool test=tab_decaissement.supprimer(code_supprimer);
    if(row==-1)
    { QMessageBox::critical(nullptr, QObject::tr("Supprimer"),
                            QObject::tr("Erreur selectionnez visite que vous voulez le supprimer!.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {
    if(test)
    {
        ui->tab_de->setModel(tab_decaissement.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                    QObject::tr("decaissement supprimé.\n"
                                "Click Cancel" ),QMessageBox::Cancel);

    }
    }
    }




void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    QString q=arg1;
    if(q=="")
    {
        ui->tableau_en->setModel(tab_encaissement.afficher());
    }
    else {ui->tableau_en->setModel(tab_encaissement.rechercher(q));}
}

void MainWindow::on_recherche_2_textChanged(const QString &arg1)
{
    QString q=arg1;
    if(q=="")
    {
        ui->tab_de->setModel(tab_decaissement.afficher());
    }
    else {ui->tab_de->setModel(tab_decaissement.rechercher(q));}
}

void MainWindow::on_tab_de_doubleClicked(const QModelIndex &index)
{
    ui->stackedWidget->setCurrentIndex(2);

       QString val=ui->tab_de->model()->data(index).toString();
       QSqlQuery query;
       query.prepare("select * from decaissement where code_decaissement='"+val+"'");

       if(query.exec())
       {
           while(query.next())
           {
               ui->code_decaissement_2->setText(query.value(0).toString());
                ui->id_em_dec_2->setText(query.value(4).toString());

           }
      }
}

void MainWindow::on_tableau_en_doubleClicked(const QModelIndex &index)
{
    ui->stackedWidget_2->setCurrentIndex(3);

       QString val=ui->tableau_en->model()->data(index).toString();
       QSqlQuery query;
       query.prepare("select * from encaissement where code_encaissement='"+val+"'");

       if(query.exec())
       {
           while(query.next())
           {ui->code_encaissement_3->setText(query.value(0).toString());
            ui->id_em_en_3->setText(query.value(3).toString());

           }
      }

}

void MainWindow::on_pushButton_16_clicked()
{
    click->play();
    ui->stackedWidget->setCurrentIndex(2);
    int id_em_dec=ui->id_em_dec_2->text().toInt() ;
    QString methode_decaissement=ui->methode_decaissement_3->currentText();
    QString remarque_decaissement=ui->remarque_decaissement_2->text();
    QString montant_decaissement=ui->montant_decaissement_2->text();
    decaissement de(methode_decaissement, montant_decaissement ,id_em_dec , remarque_decaissement);
    bool test=de.modifier();
    if (id_em_dec||methode_decaissement.isEmpty()||remarque_decaissement.isEmpty()||montant_decaissement.isEmpty())
    {
        QMessageBox::information(nullptr, QObject::tr("modifier decaissement"),
        QObject::tr("remplir les champs.\n"
        "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
    if(test)
    {
       ui->tab_de->setModel(tab_decaissement.afficher());
       QMessageBox::information(nullptr, QObject::tr("modifier decaissement"),
       QObject::tr("decaissement modifiée.\n"
       "Click Cancel to exit."), QMessageBox::Cancel);

    }
    }
}

void MainWindow::on_radioButton_8_clicked()
{
    ui->tableau_en->setModel(tab_encaissement.afficher_asc());
}

void MainWindow::on_radioButton_clicked()
{
     ui->tableau_en->setModel(tab_encaissement.afficher_dec());
}

void MainWindow::on_radioButton_5_clicked()
{
     ui->tableau_en->setModel(tab_encaissement.afficher_asc_id());
}

void MainWindow::on_radioButton_4_clicked()
{
     ui->tableau_en->setModel(tab_encaissement.afficher_dec_id());
}

void MainWindow::on_radioButton_7_clicked()
{
    ui->tableau_en->setModel(tab_encaissement.afficher_asc_methode());
}

void MainWindow::on_radioButton_2_clicked()
{
     ui->tableau_en->setModel(tab_encaissement.afficher_dec_methode());
}

void MainWindow::on_radioButton_6_clicked()
{
  ui->tableau_en->setModel(tab_encaissement.afficher_asc_date());
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->tableau_en->setModel(tab_encaissement.afficher_dec_date());
}

void MainWindow::on_radioButton_16_clicked()
{
      ui->tab_de->setModel(tab_decaissement.afficher_asc());
}

void MainWindow::on_radioButton_12_clicked()
{
      ui->tab_de->setModel(tab_decaissement.afficher_dec());
}

void MainWindow::on_radioButton_13_clicked()
{
     ui->tab_de->setModel(tab_decaissement.afficher_asc_id());
}

void MainWindow::on_radioButton_9_clicked()
{
     ui->tab_de->setModel(tab_decaissement.afficher_dec_id());
}

void MainWindow::on_radioButton_15_clicked()
{
      ui->tab_de->setModel(tab_decaissement.afficher_asc_methode());
}

void MainWindow::on_radioButton_11_clicked()
{
    ui->tab_de->setModel(tab_decaissement.afficher_dec_methode());
}

void MainWindow::on_radioButton_14_clicked()
{
     ui->tab_de->setModel(tab_decaissement.afficher_asc_date());
}

void MainWindow::on_radioButton_10_clicked()
{
     ui->tab_de->setModel(tab_decaissement.afficher_dec_date());
}







void MainWindow::on_on_anglais_en_clicked()
{
    lang="ang";
    ui->tableau_en->setModel(tab_encaissement.afficher_ang());
    ui->id_en->setText("employe");
    ui->id_en->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");
    ui->montant->setText("amount");
    ui->montant->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);}");
    ui->remarque->setText("remark");
    ui->remarque->setStyleSheet("QLabel{ background-color:#25283b;font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180); }");
    ui->valider->setText("validate");
    ui->valider->setStyleSheet("QPushButton{font: 75 12pt MS Shell Dlg 2;font-weight:600;background-color:rgb(255,250,250);} QPushButton:hover:!pressed{ border: 1px solid yellow; background-color: rgb(255, 255, 127);} QPushButton:hover::pressed{ border: 1px solid green; background-color: rgb(0, 255,0);} font-weight:600; color:#ffffff;");
    ui->methode_encaissement->setCurrentText("choice");
    ui->methode_encaissement->setStyleSheet("QComboBox{background-color:#25283b; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px;border-top-right-radius:10px; border-down-right-radius:10px;padding: 1px 0px 1px 3px; }QComboBox:focus{ border: 1px solid rgb(180, 180, 180);color:rgb(255, 255, 255); }QListView { color: white;font-weight:900; color:#ffffff; }");
    ui->methode->setText("payment method");
    ui->methode->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");

    //modifier
    ui->employe->setText("employe");
    ui->employe->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");
    ui->montant_mod->setText("amount");
    ui->montant_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);}");
    ui->remarque_mod->setText("remark");
    ui->remarque_mod->setStyleSheet("QLabel{ background-color:#25283b;font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180); }");
    ui->confirmer_la_modification->setText("confirme change");
    ui->confirmer_la_modification->setStyleSheet("QPushButton{font: 75 12pt MS Shell Dlg 2;font-weight:600;background-color:rgb(255,250,250);} QPushButton:hover:!pressed{ border: 1px solid yellow; background-color: rgb(255, 255, 127);} QPushButton:hover::pressed{ border: 1px solid green; background-color: rgb(0, 255,0);} font-weight:600; color:#ffffff;");
    ui->methode_encaissement_4->setCurrentText("choice");
    ui->methode_encaissement_4->setStyleSheet("QComboBox{background-color:#25283b; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px;border-top-right-radius:10px; border-down-right-radius:10px;padding: 1px 0px 1px 3px; }QComboBox:focus{ border: 1px solid rgb(180, 180, 180);color:rgb(255, 255, 255); }QListView { color: white;font-weight:900; color:#ffffff; }");
    ui->methode_mod->setText("payment method");
    ui->methode_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");

    ui->radioButton->setText("code");
    ui->radioButton->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2;  border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_2->setText("method");
    ui->radioButton_2->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2;  border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_3->setText("date");
    ui->radioButton_3->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_4->setText("employe");
    ui->radioButton_4->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_5->setText("employe");
    ui->radioButton_5->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_6->setText("date");
    ui->radioButton_6->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_7->setText("method");
    ui->radioButton_7->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_8->setText("code");
    ui->radioButton_8->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");


}

void MainWindow::on_pushButton_7_clicked()
{
    lang="fr";
    ui->tableau_en->setModel(tab_encaissement.afficher());
    ui->id_en->setText("employé");
    ui->id_en->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");
    ui->montant->setText("montant");
    ui->montant->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);}");
    ui->remarque->setText("remarque");
    ui->remarque->setStyleSheet("QLabel{ background-color:#25283b;font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180); }");
    ui->valider->setText("valider");
    ui->valider->setStyleSheet("QPushButton{font: 75 12pt MS Shell Dlg 2;font-weight:600;background-color:rgb(255,250,250);} QPushButton:hover:!pressed{ border: 1px solid yellow; background-color: rgb(255, 255, 127);} QPushButton:hover::pressed{ border: 1px solid green; background-color: rgb(0, 255,0);} font-weight:600; color:#ffffff;");
    ui->methode_encaissement->setCurrentText("choix");
    ui->methode_encaissement->setStyleSheet("QComboBox{background-color:#25283b; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px;border-top-right-radius:10px; border-down-right-radius:10px;padding: 1px 0px 1px 3px; }QComboBox:focus{ border: 1px solid rgb(180, 180, 180);color:rgb(255, 255, 255); }QListView { color: white;font-weight:900; color:#ffffff; }");
    ui->methode->setText("méthode de payement");
    ui->methode->setStyleSheet("QLabel{ background-color:#25283b; font: 75 11pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");

    //modifier
    ui->employe->setText("employé");
    ui->employe->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");
    ui->montant_mod->setText("montant");
    ui->montant_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);}");
    ui->remarque_mod->setText("remarque");
    ui->remarque_mod->setStyleSheet("QLabel{ background-color:#25283b;font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180); }");
    ui->confirmer_la_modification->setText("confirmer modification");
    ui->confirmer_la_modification->setStyleSheet("QPushButton{font: 75 10pt MS Shell Dlg 2;font-weight:600;background-color:rgb(255,250,250);} QPushButton:hover:!pressed{ border: 1px solid yellow; background-color: rgb(255, 255, 127);} QPushButton:hover::pressed{ border: 1px solid green; background-color: rgb(0, 255,0);} font-weight:600; color:#ffffff;");
    ui->methode_encaissement_4->setCurrentText("choix");
    ui->methode_encaissement_4->setStyleSheet("QComboBox{background-color:#25283b; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px;border-top-right-radius:10px; border-down-right-radius:10px;padding: 1px 0px 1px 3px; }QComboBox:focus{ border: 1px solid rgb(180, 180, 180);color:rgb(255, 255, 255); }QListView { color: white;font-weight:900; color:#ffffff; }");
    ui->methode_mod->setText("méthode de payement");
    ui->methode_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 11pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");

    ui->radioButton->setText("code");
    ui->radioButton->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_2->setText("méthode");
    ui->radioButton_2->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_3->setText("date");
    ui->radioButton_3->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_4->setText("employé");
    ui->radioButton_4->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_5->setText("employé");
    ui->radioButton_5->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_6->setText("date");
    ui->radioButton_6->setStyleSheet("QRadioButton{background-color:#25283b;font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_7->setText("méthode");
    ui->radioButton_7->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_8->setText("code");
    ui->radioButton_8->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
}

void MainWindow::on_on_anglais_dec_clicked()
{
    ui->employe_dec->setText("employe");
    ui->employe_dec->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");
    ui->montant_dec->setText("amount");
    ui->montant_dec->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);}");
    ui->remarque_dec->setText("remark");
    ui->remarque_dec->setStyleSheet("QLabel{ background-color:#25283b;font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180); }");
    ui->ajouter->setText("validate");
    ui->ajouter->setStyleSheet("QPushButton{font: 75 12pt MS Shell Dlg 2;font-weight:600;background-color:rgb(255,250,250);} QPushButton:hover:!pressed{ border: 1px solid yellow; background-color: rgb(255, 255, 127);} QPushButton:hover::pressed{ border: 1px solid green; background-color: rgb(0, 255,0);} font-weight:600; color:#ffffff;");
    ui->methode_decaissement->setCurrentText("choice");
    ui->methode_decaissement->setStyleSheet("QComboBox{background-color:#25283b; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px;border-top-right-radius:10px; border-down-right-radius:10px;padding: 1px 0px 1px 3px; }QComboBox:focus{ border: 1px solid rgb(180, 180, 180);color:rgb(255, 255, 255); }QListView { color: white;font-weight:900; color:#ffffff; }");
    ui->methode_dec->setText("payment method");
    ui->methode_dec->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");

    //modifier
    ui->employe_dec_mod->setText("employe");
    ui->employe_dec_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");
    ui->montant_dec_mod->setText("amount");
    ui->montant_dec_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);}");
    ui->remarque_dec_mod->setText("remark");
    ui->remarque_dec_mod->setStyleSheet("QLabel{ background-color:#25283b;font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180); }");
    ui->confirmer_dec->setText("confirme change");
    ui->confirmer_dec->setStyleSheet("QPushButton{font: 75 12pt MS Shell Dlg 2;font-weight:600;background-color:rgb(255,250,250);} QPushButton:hover:!pressed{ border: 1px solid yellow; background-color: rgb(255, 255, 127);} QPushButton:hover::pressed{ border: 1px solid green; background-color: rgb(0, 255,0);} font-weight:600; color:#ffffff;");
    ui->methode_decaissement_3->setCurrentText("choice");
    ui->methode_decaissement_3->setStyleSheet("QComboBox{background-color:#25283b; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px;border-top-right-radius:10px; border-down-right-radius:10px;padding: 1px 0px 1px 3px; }QComboBox:focus{ border: 1px solid rgb(180, 180, 180);color:rgb(255, 255, 255); }QListView { color: white;font-weight:900; color:#ffffff; }");
    ui->methode_dec_mod->setText("payment method");
    ui->methode_dec_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");

    ui->radioButton_12->setText("code");
    ui->radioButton_12->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2;  border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_11->setText("method");
    ui->radioButton_11->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2;  border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_10->setText("date");
    ui->radioButton_10->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_9->setText("employe");
    ui->radioButton_9->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_13->setText("employe");
    ui->radioButton_13->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_14->setText("date");
    ui->radioButton_14->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_15->setText("method");
    ui->radioButton_15->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_16->setText("code");
    ui->radioButton_16->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->employe_dec->setText("employé");
    ui->employe_dec->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");
    ui->montant_dec->setText("montant");
    ui->montant_dec->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);}");
    ui->remarque_dec->setText("remarque");
    ui->remarque_dec->setStyleSheet("QLabel{ background-color:#25283b;font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180); }");
    ui->ajouter->setText("valider");
    ui->ajouter->setStyleSheet("QPushButton{font: 75 12pt MS Shell Dlg 2;font-weight:600;background-color:rgb(255,250,250);} QPushButton:hover:!pressed{ border: 1px solid yellow; background-color: rgb(255, 255, 127);} QPushButton:hover::pressed{ border: 1px solid green; background-color: rgb(0, 255,0);} font-weight:600; color:#ffffff;");
    ui->methode_decaissement->setCurrentText("choix");
    ui->methode_decaissement->setStyleSheet("QComboBox{background-color:#25283b; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px;border-top-right-radius:10px; border-down-right-radius:10px;padding: 1px 0px 1px 3px; }QComboBox:focus{ border: 1px solid rgb(180, 180, 180);color:rgb(255, 255, 255); }QListView { color: white;font-weight:900; color:#ffffff; }");
    ui->methode_dec->setText("méthode de payement");
    ui->methode_dec->setStyleSheet("QLabel{ background-color:#25283b; font: 75 11pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");

    //modifier
    ui->employe_dec_mod->setText("employé");
    ui->employe_dec_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");
    ui->montant_dec_mod->setText("montant");
    ui->montant_dec_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 12pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);}");
    ui->remarque_dec_mod->setText("remarque");
    ui->remarque_dec_mod->setStyleSheet("QLabel{ background-color:#25283b;font: 75 12pt MS Shell Dlg 2; font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180); }");
    ui->confirmer_dec->setText("confirmer modification");
    ui->confirmer_dec->setStyleSheet("QPushButton{font: 75 10pt MS Shell Dlg 2;font-weight:600;background-color:rgb(255,250,250);} QPushButton:hover:!pressed{ border: 1px solid yellow; background-color: rgb(255, 255, 127);} QPushButton:hover::pressed{ border: 1px solid green; background-color: rgb(0, 255,0);} font-weight:600; color:#ffffff;");
    ui->methode_decaissement_3->setCurrentText("choix");
    ui->methode_decaissement_3->setStyleSheet("QComboBox{background-color:#25283b; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px;border-top-right-radius:10px; border-down-right-radius:10px;padding: 1px 0px 1px 3px; }QComboBox:focus{ border: 1px solid rgb(180, 180, 180);color:rgb(255, 255, 255); }QListView { color: white;font-weight:900; color:#ffffff; }");
    ui->methode_dec_mod->setText("méthode de payement");
    ui->methode_dec_mod->setStyleSheet("QLabel{ background-color:#25283b; font: 75 11pt MS Shell Dlg 2;font-weight:600; color:#ffffff; border:1px solid rgb(255, 250, 250); color:rgb(255, 255, 255); padding-left:16px; border:1px solid rgb(255, 250, 250); border-top-right-radius:10px; border-down-right-radius:10px; } QLabel:focus{ border: 1px solid rgb(180, 180, 180);  }");

    ui->radioButton_12->setText("code");
    ui->radioButton_12->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2;  border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_11->setText("méthode");
    ui->radioButton_11->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2;  border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_10->setText("date");
    ui->radioButton_10->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_9->setText("employé");
    ui->radioButton_9->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_13->setText("employé");
    ui->radioButton_13->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_14->setText("date");
    ui->radioButton_14->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_15->setText("méthode");
    ui->radioButton_15->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
    ui->radioButton_16->setText("code");
    ui->radioButton_16->setStyleSheet("QRadioButton{background-color:#25283b; font: 60 10pt MS Shell Dlg 2; border:2px solid rgb(255,255,255); color:rgb(255, 255, 255); padding-left:16px; border-top-right-radius:10px; border-down-right-radius:10px; } QRadioButton:focus{ border: 1px solid rgb(255, 255, 255); } QRadioButton:pressed {border:2px solid rgb(179, 34, 58);}");
}

