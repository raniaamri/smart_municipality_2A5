#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include "formation.h"
#include <QMainWindow>
#include<QLabel>
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

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_ajouter_clicked();

    void on_pushButton_3_clicked();

    void on_le_id_search_textChanged(const QString &arg1);

    void on_modifier_clicked();


    void on_pushButton_9_clicked();




    void on_pushButton_10_clicked();

    void on_pb_ajouterformation_clicked();

    void on_pushButton_2_clicked();

    void on_pb_modifierformation_clicked();

    void on_le_searchformation_textChanged(const QString &arg1);

    void on_pb_supprimerformation_clicked();





    void on_export_2_clicked();

private:

    Ui::MainWindow *ui;
    Employe E;
    formation F;
};


#endif // MAINWINDOW_H
