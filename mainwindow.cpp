#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include"encaissement.h"
#include <QMessageBox>
#include <QFile>
#include <QPrinter>
#include <QDebug>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->tableau_en->setModel(tab_encaissement.afficher());
    ui->tab_de->setModel(tab_decaissement.afficher());
    ui->stackedWidget->setCurrentIndex(1);
     ui->stackedWidget_3->setCurrentIndex(1);
    ui->stackedWidget_4->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int code_encaissement=ui->code_encaissement->text().toInt() ;
    int id_employe=ui->comboBox->currentText().toInt();
    QString methode_encaissement=ui->methode_encaissement->currentText();
    QString remarque_encaissement=ui->remarque_encaissement->text();
    QString montant_encaissement=ui->montant_encaissement->text();
    encaissement en(code_encaissement,methode_encaissement, montant_encaissement ,id_employe , remarque_encaissement);
    bool test=en.ajouter();
    if(ui->code_encaissement->text().isEmpty()||ui->comboBox->currentText()=="choix id"||ui->code_encaissement->text().contains(QRegExp("^[1-9]"))==0||ui->montant_encaissement->text().isEmpty()||ui->methode_encaissement->currentText()=="choix")
    {QMessageBox::warning(nullptr, QObject::tr("erreur"),
                              QObject::tr("verifier les champs.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);}
    else{
    if(test)
    {
       ui->tableau_en->setModel(tab_encaissement.afficher());
       QMessageBox::information(nullptr, QObject::tr("Ajouter encaissement"),
       QObject::tr("encaissement ajoutée.\n"
       "Click Cancel to exit."), QMessageBox::Cancel);

    }
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    int code_decaissement=ui->code_decaissement->text().toInt() ;
   int id_em_dec=ui->comboBox_4->currentText().toInt();
   QString methode_decaissement=ui->methode_decaissement->currentText();
    QString remarque_decaissement=ui->remarque_decaissement->text();
    QString montant_decaissement=ui->montant_decaissement->text();
    decaissement de(code_decaissement,methode_decaissement, montant_decaissement ,id_em_dec , remarque_decaissement);
    bool test=de.ajouter();
    if(ui->code_decaissement->text().isEmpty()||ui->code_decaissement->text().contains(QRegExp("^[1-9]"))==0||ui->comboBox_4->currentText()=="choix id"||ui->montant_decaissement->text().isEmpty()||ui->methode_decaissement->currentText()=="choix")
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

    }
    }
}

void MainWindow::on_pushButton_6_clicked()
{
stat=new statistique(this);
stat->show();



}

void MainWindow::on_pushButton_2_clicked()
{
ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_pushButton_13_clicked()
{
    int code_encaissement=ui->code_encaissement_3->text().toInt() ;
    int id_employe=ui->id_em_en_3->text().toInt() ;
    QString methode_encaissement=ui->methode_encaissement_4->currentText();
    QString remarque_encaissement=ui->remarque_encaissement_3->text();
    QString montant_encaissement=ui->montant_encaissement_3->text();
    encaissement en(code_encaissement,methode_encaissement, montant_encaissement ,id_employe , remarque_encaissement);
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
   ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
}

void MainWindow::on_pushButton_10_clicked()
{
     ui->stackedWidget_4->setCurrentIndex(0);
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
}

void MainWindow::on_pdf_clicked()
{
    QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("C://Users//asus//Desktop//smart-muni//encaissement.pdf");//badel i chemin win t7eb t7ot il fichier ya2melek creation
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

void MainWindow::on_supprimer_clicked()
{
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

        QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("C://Users//asus//Desktop//smart-muni//decaissement.pdf");//badel i chemin win t7eb t7ot il fichier ya2melek creation
                QPainter painter;

                if (! painter.begin(&printer)) { // failed to open file
                    qWarning("failed to open file, is it writable?");
                }

                QSqlQuery   query ;
                qDebug() << query.prepare("select sysdate from dual  ");
                if ( query.exec() )
                {

                    QString S= QDate::currentDate().toString();
                    painter.drawText(850,50,S);
                    QPen penred(Qt::black);

                    painter.setFont(QFont("Arial", 30));
                    penred.setWidth(1);
                    painter.setPen(penred);

                    painter.drawText(250,100," decaissement ");
                    painter.setFont(QFont("Arial",30));
                    painter.setPen(Qt::black);

                }

                QString code_decaissement,date_decaissement,methode_decaissement ,id_employe,montant_decaissement, remarque_decaissement;
                QSqlQuery   qry ;
                int i =50;
                int k=0;
                qDebug() << qry.prepare("select * from decaissement ");
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
            painter.drawText (290,150,"montant");
            painter.drawText (400,150,"methode");
            painter.drawText (500,150,"id_employe");
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
                       montant_decaissement=qry.value(2).toString();
                        painter.drawText(j*150,i, montant_decaissement);
                        j++;
                       methode_decaissement=qry.value(3).toString();
                        painter.drawText(j*133,i, methode_decaissement);
                        j++;
                        id_employe=qry.value(4).toString();
                        painter.drawText(j*125,i,  id_employe);
                        j++;
                       remarque_decaissement=qry.value(5).toString();
                         painter.drawText(j*124,i, remarque_decaissement);
                        i+=80;
                        k++;

                    }
                }

                painter.end();
    }
}

void MainWindow::on_supprimer_2_clicked()

    {
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
        ui->tableau_en->setModel(tab_encaissement.afficher());
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

           }
      }

}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    int code_decaissement=ui->code_decaissement_2->text().toInt() ;
    int id_em_dec=ui->id_em_dec_2->text().toInt() ;
    QString methode_decaissement=ui->methode_decaissement_3->currentText();
    QString remarque_decaissement=ui->remarque_decaissement_2->text();
    QString montant_decaissement=ui->montant_decaissement_2->text();
    decaissement de(code_decaissement,methode_decaissement, montant_decaissement ,id_em_dec , remarque_decaissement);
    bool test=de.modifier();
    if (code_decaissement==0||id_em_dec||methode_decaissement.isEmpty()||remarque_decaissement.isEmpty()||montant_decaissement.isEmpty())
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




