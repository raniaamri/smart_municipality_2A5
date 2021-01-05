#ifndef RESSOURCES_HUMAINES_H
#define RESSOURCES_HUMAINES_H
#include <QDialog>
#include <QWidget>
#include "employe.h"
#include "formation.h"
#include "encaissement.h"
#include "statistique.h"
#include"stat2.h"
#include"decaissement.h"
#include"citoyens.h"
#include"rec.h"
#include"naissance.h"
#include"deces.h"
#include"cadastre.h"
#include"demandes.h"
#include <QMainWindow>
#include<QLabel>
#include "arduino.h"
#include"equipement.h"
#include"vehicule.h"
namespace Ui {
class Ressources_Humaines;
}

class Ressources_Humaines : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ressources_Humaines(QWidget *parent = nullptr);
    ~Ressources_Humaines();

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

    void on_pushButton_12_clicked();

    void on_pushButton_6_clicked();
    void on_pushButton_11_clicked();

    void on_pushButton_clicked();





    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_menu_rh_clicked();

    void on_encaissement_pb_clicked();

    void on_supprimer_encaissement_clicked();

    void on_menu_fn_clicked();

    void on_chercher_encaissement_textChanged(const QString &arg1);

    void on_trier_encaissement_clicked();

    void on_stat_encaissement_clicked();

    void on_decaissement_pb_valider_clicked();

    void on_supprimer_decaissement_clicked();

    void on_chercher_decaissement_textChanged(const QString &arg1);

    void on_trier_decaissement_clicked();

    void on_pdf_decaissement_clicked();

    void on_pdf_encaisssement_clicked();

    void on_modifier_encaissement_clicked();

    void on_modifier_decaissement_clicked();

    void on_encaissement_pb_2_clicked();

    void on_decaissement_pb_clicked();

    void on_retour_menu_clicked();

    void on_ajouter_reclam_pb_clicked();

    void on_modifier_reclam_pb_clicked();

    void on_supp_reclam_pb_clicked();

    void on_chercher_reclam_pb_clicked();

    void on_tri_pb_reclam_clicked();

    void on_export_reclam_clicked();

    void on_pushButton_19_clicked();

    void on_ajouter_cit_clicked();

    void on_modifier_cit_clicked();

    void on_supp_cit_clicked();

    void on_Bshow_clicked();

    void on_B_ASC_clicked();

    void on_trier_cit_clicked();

    void on_export_cit_clicked();

    void on_recla_pb_clicked();

    void on_cit_pb_clicked();

    void on_Aj_mf_pb_clicked();

    void on_ajout1_pb_clicked();


    void on_pushButton_20_clicked();


    void on_test_clicked();

    void on_modif1_pb_clicked();

    void on_pb_suprrr_clicked();

    void on_le_recherche01_textChanged(const QString &arg1);

    void on_trinum_pb_clicked();

    void on_trinom_pb_clicked();

    void on_triprenompb_clicked();

    void on_pdf_pb01_clicked();

    void on_naissanceside_clicked();

    void on_retourmenu_clicked();

    void on_pushButton_13_clicked();

    void on_Ajouterdeces_pb_clicked();

    void on_decesside_clicked();

    void on_aj_mf_dec_clicked();

    void on_modifierdeces_pb_clicked();

    void on_recherche_deces_textChanged(const QString &arg1);

    void on_supprimerdeces_pb_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_Ajouter_demande_pb_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_22_clicked();

    void on_AjouterC_clicked();

    void on_supprimerC_clicked();

    void on_modifierC_clicked();

    void on_pdfC_pb_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_18_clicked();

    void on_demande_clicked();

    void on_cadastre_clicked();

    void on_RRETOUR_clicked();

    void on_login_pb_clicked();

    void on_disconnect_clicked();

    void on_searching_clicked();

    void on_searchingAgain_clicked();

    void on_recherche_dem_textChanged(const QString &arg1);

    void on_rechercheC_textChanged(const QString &arg1);



    void on_xxx_clicked();
private slots :
    void update_label();


    void on_ArduinoON_2_clicked();

    void on_ArduinoOFF_2_clicked();

    void on_ajouterequi_clicked();

    void on_pushButton_25_clicked();

    void on_modifierequi_clicked();

    void on_PDFA_clicked();

    void on_MAILINGA_clicked();

    void on_comboV_activated(const QString &arg1);

    void on_ajouterV_clicked();

    void on_supprimerV_clicked();

    void on_modifierV_clicked();

    void on_toV_clicked();

    void on_toE_clicked();

private:
    Ui::Ressources_Humaines *ui;
    Employe E;
    formation F;
    encaissement en;
    decaissement dc;
    statistique *stat;
    stat2 *stat02;
    Rec R;
    Cit C;
    naissance na;
    deces de;
    cadastre ca ;
    demandes dem;
    arduino A;
    QByteArray data;
    equipement e;
    vehicule v;

};

#endif // RESSOURCES_HUMAINES_H




