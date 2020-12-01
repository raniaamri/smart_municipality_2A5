#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"demandes.h"
#include "cadastre.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Bdemande_clicked();

    void on_Bcadastre_clicked();

    void on_Bquitter_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_Bconfirmer_clicked();

    void on_Bajout_clicked();

    void on_pushButton_15_clicked();

    void on_Bsupprimer_clicked();

    void on_Bsuppression_clicked();

    void on_Bmodifier_clicked();

    void on_pushButton_2_clicked();

    void on_Bmodification_clicked();

    void on_pushButton_135_clicked();

    void on_Bajout_16_clicked();

    void on_Bconfirmer2_clicked();

    void on_pushButton_125_clicked();

    void on_Bsuppression_16_clicked();

    void on_Bsupprimer2_clicked();

    void on_pushButton_126_clicked();

    void on_Bmodification_16_clicked();

    void on_Bmodifier2_clicked();

    void on_pushButton_127_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_136_clicked();

    void on_pushButton_123_clicked();

    void on_pushButton_124_clicked();

    void on_pushButton_134_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_133_clicked();

    void on_pushButton_132_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    demandes tmpdemandes;
    cadastre tmpcadastre;
};
#endif // MAINWINDOW_H
