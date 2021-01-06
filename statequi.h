#ifndef STATEQUI_H
#define STATEQUI_H

#include <QDialog>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
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
#include <QPainter>
#include <QSqlQuery>

#include <QDialog>
namespace Ui {
class statequi;
}

class statequi : public QDialog
{
    Q_OBJECT

public:
    explicit statequi(QWidget *parent = nullptr);
    ~statequi();
    int Stat_partie2() ;
        int Stat_partie3() ;
        int Stat_partie4() ;

        void paintEvent(QPaintEvent *) ;

private:
    Ui::statequi *ui;
};

#endif // STATEQUI_H







