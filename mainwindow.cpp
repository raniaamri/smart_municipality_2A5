#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include"demandes.h"
#include"cadastre.h"
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
#include <QFile>
#include <QFileDialog>
#include<QTextStream>
#include <QPrintDialog>
#include<QPdfWriter>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QSqlRecord>
#include <QTextDocument>
QT_CHARTS_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPixmap bkngd("C:/Users/Home/Desktop/municipalitye.webp");//background
    bkngd=bkngd.scaled(this->size()*1.23,Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background,bkngd);
    this->setPalette(palette);
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabdemandes->setModel(tmpdemandes.afficher());
    ui->tabcadastre->setModel(tmpcadastre.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Bdemande_clicked()
{
ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Bcadastre_clicked()
{
 ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_Bquitter_clicked()
{
    close();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Bconfirmer_clicked()
{
    int id=0;
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString etat = ui->etat->text();

           if((nom !=  "")&&(prenom!="")&&(etat !="")) {
               QMessageBox::information(this, "Ajout", "Ajout reussi");
}
           else {
               QMessageBox::warning(this,"Ajout", "Ajouter svp ");
           }

demandes p(id,nom,prenom,etat);
bool test=p.ajouter();
//notif->showMessage(tr("Profil ajouté "),tr(nom.toUtf8().constData()));
ui->stackedWidget->setCurrentIndex(2);
ui->tabdemandes->setModel(tmpdemandes.afficher());
}

void MainWindow::on_Bajout_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_15_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Bsupprimer_clicked()
{
    int id_demande=ui->id_demande->currentText().toInt();
        //qDebug()<<id_demande;
        QString nom;
        QString prenom;
        QString etat;
      demandes o(id_demande,nom,prenom,etat);
        bool test=o.supprimer(id_demande);
         // notif->showMessage(tr("ouvrier Supprimé "),tr(prenom.toUtf8().constData()));
        QMessageBox::information(this, "Supprimée", "Supression reussi");
        ui->stackedWidget->setCurrentIndex(2);
        ui->tabdemandes->setModel(tmpdemandes.afficher());
}



void MainWindow::on_Bsuppression_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
            QSqlQuery q;
            q.prepare("select ID_demande from demandes ");
            q.exec();
            modal->setQuery(q);
            ui->id_demande->setModel(modal);
            ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_Bmodifier_clicked()
{
    int id_demande=0;
        QString nom = ui->nom_2->text();
        QString prenom = ui->prenom_2->text();
        QString etat = ui->etat_2->currentText();


               if((nom !=  "")&&(prenom!=""))
               {
                   QMessageBox::information(this, "Modification", "Modifié");
               }
               else
               {
                   QMessageBox::warning(this,"Modification", "Verifié(e) svp ");
               }

               demandes o(id_demande,nom,prenom,etat);
               bool test=o.Modifier();
              // notif->showMessage(tr("Ouvrier Modifié "),tr(nom.toUtf8().constData()));
               ui->stackedWidget->setCurrentIndex(2);
               ui->tabdemandes->setModel(tmpdemandes.afficher());
     QMessageBox::information(this, "Demande", "Modifié(e)");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Bmodification_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
            QSqlQuery q;
            q.prepare("select etat from demandes ");
            q.exec();
            modal->setQuery(q);
            ui->etat_2->setModel(modal);
     ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_135_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Bajout_16_clicked()
{
   ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_Bconfirmer2_clicked()
{
    int id=0;
    QString nom = ui->nom_3->text();
    QString prenom = ui->prenom_3->text();
    float surface = ui->surface_1->text().toFloat();

           if((nom !=  "")&&(prenom != "")) {
               QMessageBox::information(this, "Ajout", "Ajout reussi");
}
           else {
               QMessageBox::warning(this,"Ajout", "Ajouter svp ");
           }

cadastre a(id,nom,prenom,surface);
bool test=a.ajouter();
//notif->showMessage(tr("Profil ajouté "),tr(nom.toUtf8().constData()));
ui->stackedWidget->setCurrentIndex(5);
ui->tabcadastre->setModel(tmpcadastre.afficher());
}


void MainWindow::on_pushButton_125_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_Bsuppression_16_clicked()
{
     QSqlQueryModel * modal = new QSqlQueryModel ();
             QSqlQuery q;
             q.prepare("select ID_cadastre from cadastre ");
             q.exec();
             modal->setQuery(q);
             ui->id_cadastre->setModel(modal);
             ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_Bsupprimer2_clicked()
{
    int id_cadastre=ui->id_cadastre->currentText().toInt();
        //qDebug()<<id_cadastre;
        QString nom;
        QString prenom;
        float surface;
      cadastre o(id_cadastre,nom,prenom,surface);
        bool test=o.supprimer(id_cadastre);
         // notif->showMessage(tr("ouvrier Supprimé "),tr(prenom.toUtf8().constData()));
        QMessageBox::information(this, "Supprimée", "Supression reussi");
        ui->stackedWidget->setCurrentIndex(5);
        ui->tabcadastre->setModel(tmpcadastre.afficher());
}

void MainWindow::on_pushButton_126_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_Bmodification_16_clicked()
{

      ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_Bmodifier2_clicked()
{
    int id_cadastre=0;
        QString nom = ui->nom_4->text();
        QString prenom = ui->prenom_4->text();
        float surface = ui->surface->text().toFloat();


               if((nom !=  "")&&(prenom!=""))
               {
                   QMessageBox::information(this, "Modification", "Modifié");
               }
               else
               {
                   QMessageBox::warning(this,"Modification", "Verifié(e) svp ");
               }

               cadastre o(id_cadastre,nom,prenom,surface);
               bool test=o.Modifier();
              // notif->showMessage(tr("cadastre Modifié "),tr(nom.toUtf8().constData()));
               ui->stackedWidget->setCurrentIndex(5);
               ui->tabcadastre->setModel(tmpcadastre.afficher());

}

void MainWindow::on_pushButton_127_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->tabdemandes->setModel(tmpdemandes.sortid_up());
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->tabdemandes->setModel(tmpdemandes.sortid_down());
}

void MainWindow::on_pushButton_8_clicked()
{
    QString chercher= ui->recherche->text();
    QString nom;

        QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        if(chercher != "")
        {q.prepare("select * from demandes where nom like '%"+chercher+"%'");
            q.bindValue(":nom",chercher);
            q.exec();
            modal->setQuery(q);
            ui->tabdemandes->setModel(modal);
            ui->tabdemandes->setModel(modal);
    }
        else
        {QMessageBox::warning(this,"Probléme","recherche invalide");

}
}

void MainWindow::on_pushButton_7_clicked()
{

    // Assign names to the set of bars used
                QBarSet *set0 = new QBarSet("demandes");

                QSqlQuery q;
                              q.prepare("select id_demande from demandes order by id_demande asc ");
                              if(q.exec())
                              {
                                             while (q.next())
                                             {
                                                 float a=q.value(0).toFloat();
                                               *set0 << a ;
                                             }
    }
                QBarSeries *series = new QBarSeries();

                // 2. Stacked bar chart
                // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
                series->append(set0);


                // Used to define the bar chart to display, title
                // legend,
                QChart *chart = new QChart();
                // Add the chart
                chart->addSeries(series);

                // Set title
                chart->setTitle(" % etat selon l'id des demandes ");

                // Define starting animation
                // NoAnimation, GridAxisAnimations, SeriesAnimations
                chart->setAnimationOptions(QChart::AllAnimations);

                // Holds the category titles
                QStringList categories;
                //QSqlQuery q;
                              q.prepare("select etat from demandes order by id_demande  ");
                              if(q.exec())
                            {
                                while (q.next())
                                {
                                QString a=q.value(0).toString() ;
                                 categories << a ;
                                }
                            }
                // Adds categories to the axes
                QBarCategoryAxis *axis = new QBarCategoryAxis();
                axis->append(categories);
                chart->createDefaultAxes();

                // 1. Bar chart
                chart->setAxisX(axis, series);

                // 2. Stacked Bar chart
                // chart->setAxisY(axis, series);

                // Define where the legend is displayed
                chart->legend()->setVisible(true);
                chart->legend()->setAlignment(Qt::AlignBottom);

                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);

                // Used to change the palette
                QPalette pal = qApp->palette();

                // Change the color around the chart widget and text
                pal.setColor(QPalette::Window, QRgb(0xffffff));
                pal.setColor(QPalette::WindowText, QRgb(0x404044));

                // Apply palette changes to the application
                qApp->setPalette(pal);

    chartView->setParent(ui->horizontalFrame);
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_136_clicked()
{
    QString chercher= ui->recherche_2->text();
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

void MainWindow::on_pushButton_123_clicked()
{
     ui->tabcadastre->setModel(tmpcadastre.sortid_up());
}

void MainWindow::on_pushButton_124_clicked()
{
     ui->tabcadastre->setModel(tmpcadastre.sortid_down());
}

void MainWindow::on_pushButton_134_clicked()
{
    // Assign names to the set of bars used
                QBarSet *set0 = new QBarSet("cadastre");

                QSqlQuery q;
                              q.prepare("select id_cadastre from cadastre order by id_cadastre asc ");
                              if(q.exec())
                              {
                                             while (q.next())
                                             {
                                                 float a=q.value(0).toFloat();
                                               *set0 << a ;
                                             }
    }
                QBarSeries *series = new QBarSeries();

                // 2. Stacked bar chart
                // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
                series->append(set0);


                // Used to define the bar chart to display, title
                // legend,
                QChart *chart = new QChart();
                // Add the chart
                chart->addSeries(series);

                // Set title
                chart->setTitle("nombre de surface selon l'id des cadastres ");

                // Define starting animation
                // NoAnimation, GridAxisAnimations, SeriesAnimations
                chart->setAnimationOptions(QChart::AllAnimations);

                // Holds the category titles
                QStringList categories;
                //QSqlQuery q;
                              q.prepare("select surface from cadastre order by id_cadastre  ");
                              if(q.exec())
                            {
                                while (q.next())
                                {
                                QString a=q.value(0).toString() ;
                                 categories << a ;
                                }
                            }
                // Adds categories to the axes
                QBarCategoryAxis *axis = new QBarCategoryAxis();
                axis->append(categories);
                chart->createDefaultAxes();

                // 1. Bar chart
                chart->setAxisX(axis, series);

                // 2. Stacked Bar chart
                // chart->setAxisY(axis, series);

                // Define where the legend is displayed
                chart->legend()->setVisible(true);
                chart->legend()->setAlignment(Qt::AlignBottom);

                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);

                // Used to change the palette
                QPalette pal = qApp->palette();

                // Change the color around the chart widget and text
                pal.setColor(QPalette::Window, QRgb(0xffffff));
                pal.setColor(QPalette::WindowText, QRgb(0x404044));

                // Apply palette changes to the application
                qApp->setPalette(pal);

    chartView->setParent(ui->horizontalFrame_2);
    ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_pushButton_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_6_clicked()
{
    QTableView *table;
        table = ui->tabdemandes;

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

void MainWindow::on_pushButton_133_clicked()
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

void MainWindow::on_pushButton_132_clicked()
{
    QString strStream;
          QTextStream out(&strStream);
    QSqlQuery Query;
    Query.prepare("select * from cadastre");
    Query.exec();
          const int rowCount = Query.size();
          const int columnCount = Query.record().count();

          out <<  "<html>\n"
              "<head>\n"
             // "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<   QString ( " <title>% liste des propritaires </title> \ n " ). arg ( " cadastre " )
              <<  "</head>\n"
              "<body bgcolor=#ffffff link=#5000A0>\n"
              "<center><table border=1 cellspacing=0 cellpadding=2>\n"
        // " <center><img src = 'C:/Users/soulayma/Desktop/test.png' width = '100' height = '100'></center>  "
                                      " <h1><center> Liste des propritaires</center> </h1> ";

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
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString strStream;
          QTextStream out(&strStream);
    QSqlQuery Query;
    Query.prepare("select * from demandes");
    Query.exec();
          const int rowCount = Query.size();
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
    }
}
