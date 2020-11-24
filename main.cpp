#include "mainwindow.h"
#include<QMessageBox>
#include <QApplication>
#include <QDebug>
#include"connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    MainWindow w;

    bool test=c.createConnection();
    if(test)
        qDebug()<<"connexion reussite";
    else
        qDebug()<<"pas de connexion";

    w.show();
    return a.exec();
}
