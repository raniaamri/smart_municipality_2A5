#ifndef CADASTRE_H
#define CADASTRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class cadastre
{
public:
    cadastre();
    cadastre(int,QString,QString,float);
    QString get_nom(){return nom;}
    bool ajouter();
    bool Modifier(int id_cadastre,QString nom,QString prenom,float surface);
    QSqlQueryModel *sortid_up();
    QSqlQueryModel *sortid_down();
    bool supprimer(int);
    QSqlQueryModel *afficher();
    QSqlQueryModel * rechercher (const QString &aux);

private:
    int id_cadastre;
    QString prenom;
    QString nom;
    float surface;
};

#endif // CADASTRE_H
