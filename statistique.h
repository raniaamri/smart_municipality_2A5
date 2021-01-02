#ifndef STATISTIQUE_H
#define STATISTIQUE_H
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
class statistique;
}

class statistique : public QDialog
{
    Q_OBJECT




public:
    explicit statistique(QWidget *parent = nullptr);
    ~statistique();
    int Stat_partie2() ;
        int Stat_partie3() ;
        int Stat_partie4() ;

        void paintEvent(QPaintEvent *) ;

private:
    Ui::statistique *ui;
};

#endif // STATISTIQUE_H
