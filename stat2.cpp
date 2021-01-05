
#include "stat2.h"
#include "ui_stat2.h"

stat2::stat2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat2)
{
    ui->setupUi(this);
}

stat2::~stat2()
{
    delete ui;
}

int stat2::Stat_partie2()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select etat from demandes order by id_demande") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;

}
int stat2::Stat_partie3()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select id_demande from demandes order by id_demande asc") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;

}




void stat2::paintEvent(QPaintEvent *)
{

    int b=Stat_partie2();
    //cout<<b<<endl ;
    int c=Stat_partie3();
   // cout<<c<<endl ;

        float s2= b*100 ;
        float s3=c*100;
        float nb = b+c ;
        float q2 ;
        q2 = s2/nb ;
        float q3;
        q3=s3/nb;
        float y  ;
        y = (q2*360)/100 ;
        float m;
        m= (q3*360)/100;
        float z  ;
        z=360-(y+m) ;
    QPainter painter(this);
    QRectF size=QRectF(50,50,this->width()-500,this->width()-500);

    painter.setBrush(Qt::blue);
    painter.drawPie(size,0,16*y);
    ui->label->setText("blue:1-100") ;
    painter.setBrush(Qt::green);
    painter.drawPie(size,16*y,16*m);
    ui->label_2->setText("green:101-500") ;
    painter.setBrush(Qt::red);
    painter.drawPie(size,16*(m+y),16*z);
    ui->label_3->setText("red:501-10000") ;

}
