#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"ressources_humaines.h"
#include"ui_ressources_humaines.h"
#include <QMessageBox>
#include<QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint );


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{
    QString username;
    QString password;
    username=ui->lineEdit_user->text();
    password=ui->lineEdit_password->text();
    QSqlQuery qry;
    if(qry.exec( "select * from compte where username='"+username +"' and password='"+password +"'"))
      {
        int count=0;
    while(qry.next())
       {
        count++;
        }
    if(count==1)
    {
        hide();
        Ressources_Humaines RH;
        RH.exec();
    }
    if(count<1)
    {
        QMessageBox::critical(nullptr, QObject::tr("password incorrect"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        /*  ui->label-setText("false")*/
    }
    }
}
