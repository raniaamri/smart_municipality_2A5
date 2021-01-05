#include "ressources_humaines.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QIcon>
#include <QAction>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "connection.h"
#include <QtCharts/QChartView>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.ouvrirConnection();
    Ressources_Humaines rh;






         if(test)
         {

             rh.show();
             QMessageBox::information(nullptr, QObject::tr("database is open"),
                         QObject::tr("connection successful.\n""Click Cancel to exit."), QMessageBox::Cancel);

             // qDebug()<<"Connection successful";
         }
         else

             QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                         QObject::tr("connection failed.\n""Click Cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}


