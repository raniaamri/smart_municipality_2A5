#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"naissance.h"
#include"deces.h"
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


    void on_pushButton_Ajouter_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButton_Supprimer_clicked();

private:
    Ui::MainWindow *ui;
    naissance naissance_temporaire;
    deces deces_temporaire;
};
#endif // MAINWINDOW_H
