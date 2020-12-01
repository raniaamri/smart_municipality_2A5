#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "connection.h"
#include <QtCharts/QChartView>
int main(int argc, char *argv[])
{
    connection c;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
