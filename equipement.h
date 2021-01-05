#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDebug>




class equipement
{

public:
    equipement();
    equipement(int,QString,QString);

    void setid_e(int);
    void setnom(QString);
    void setreference(QString);



    int getID_E();
    QString get_NOM();
    QString get_REFERENCE();
    bool ajouter();
    QSqlQueryModel * Afficher();
    QSqlQueryModel * afficher_equipement();
    bool modifier(int, QString, QString);
    bool supprimer(int);
    QSqlQueryModel * recherche (const QString &ress);
    QSqlQueryModel *  trier(const QString &critere, const QString &mode );

private:

    int ID_E;
    QString NOM,REFERENCE,TYPE;

};

#endif // EQUIPEMENT_H
