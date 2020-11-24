#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "encaissement.h"
#include <QMainWindow>
#include "decaissement.h"
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
    void on_pushButton_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

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

private:
    Ui::MainWindow *ui;
    encaissement tab_encaissement;
    decaissement tab_decaissement;
};
#endif // MAINWINDOW_H