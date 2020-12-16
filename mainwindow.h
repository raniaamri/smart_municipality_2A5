#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "encaissement.h"
#include <QMainWindow>
#include "decaissement.h"
#include "statistique.h"
#include <QMediaPlayer>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
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
    void on_valider_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_confirmer_la_modification_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_14_clicked();

    void on_pdf_clicked();

    void on_supprimer_clicked();

    void on_pdf_dec_clicked();

    void on_supprimer_2_clicked();

    void on_recherche_textChanged(const QString &arg1);

    void on_recherche_2_textChanged(const QString &arg1);

    void on_tab_de_doubleClicked(const QModelIndex &index);

    void on_tableau_en_doubleClicked(const QModelIndex &index);



    void on_pushButton_16_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_16_clicked();

    void on_radioButton_12_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_15_clicked();

    void on_radioButton_11_clicked();

    void on_radioButton_14_clicked();

    void on_radioButton_10_clicked();



    void on_on_anglais_en_clicked();

    void on_pushButton_7_clicked();

    void on_on_anglais_dec_clicked();

    void on_pushButton_9_clicked();



private:
    Ui::MainWindow *ui;
    encaissement tab_encaissement;
    decaissement tab_decaissement;
    statistique *stat;
    QMediaPlayer *click;
    QString lang="fr";
};
#endif // MAINWINDOW_H
