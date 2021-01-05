#ifndef stat2_H
#define stat2_H
#include <QDialog>
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
class stat2;
}



class stat2 : public QDialog
{
    Q_OBJECT




public:
    explicit stat2(QWidget *parent = nullptr);
    ~stat2();
    int Stat_partie2() ;
        int Stat_partie3() ;

        void paintEvent(QPaintEvent *) ;

private:
    Ui::stat2 *ui;
};

#endif // STAT2_H
