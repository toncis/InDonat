/************************************* Module Header **************************************\
* Module Name:  frmdonatmenu.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of DONAT main form
*
* For more information see the Books Online and documentation.
* *****************************************************************************************
* All rights reserved.
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
* OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
* FITNESS FOR A PARTICULAR PURPOSE.
* * *****************************************************************************************
* Release History :
*
* VERSION	DESCRIPTION
* 	3.0		Created by Tonci Svilicic
\******************************************************************************************/

#ifndef FRMDONATMENU_H
#define FRMDONATMENU_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>

#include "donat.h"

namespace Ui {
class FrmDonatMenu;
}

namespace Log {

class FrmDonatMenu : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FrmDonatMenu(QWidget *parent = 0);
    ~FrmDonatMenu();
    
private slots:
    void on_btnPromjenaZaporke_clicked();
    void on_btnSifarnik_clicked();
    void on_btnOdrzavanje_clicked();
    void on_btnAbout_clicked();

    void on_btnTcom_clicked();
    void on_btnTmobile_clicked();

    void on_btnTrazi_clicked();
    void on_btnDonatKon_clicked();
    void on_btnDonatFiz_clicked();
    void on_btnDonatFir_clicked();


    void on_btnInfo_clicked();
    void on_btnZahtjevi_clicked();
    void on_btnSmetnje_clicked();
    void on_btnKontakti_clicked();
    void on_btnOsobe_clicked();

    void on_btnDonatStatus_clicked();
    void on_btnWwmsStatus_clicked();
    void on_btnDonatProcesi_clicked();

    void on_btnAdslStatus_clicked();
    void on_btnMaxTvStatus_clicked();

    void on_btnStatusBarDonatUser_clicked();

    void on_btnFltNaziv_clicked();
    void on_btnFltTelefon_clicked();
    void on_btnFltMbJmbg_clicked();
    void on_btnFltOib_clicked();
    void on_btnFltUlogaStrankeId_clicked();
    void on_btnFltTicketId_clicked();
    void on_btnFltAssetId_clicked();
    void on_btnFltGrupa_clicked();
    void on_btnFltHijerahija_clicked();
    void on_btnFltUlica_clicked();
    void on_btnFltKolokacija_clicked();
    void on_btnExpandImovina_clicked();
    void on_btnGrupeImovineView_clicked();
    void on_btnAssetView_clicked();

    void on_btnAktivnaGrupaImovine_clicked();
    void on_btnNeaktivnaGrupaImovine_clicked();
    void on_btnAktivnaImovina_clicked();
    void on_btnNeaktivnaImovina_clicked();

    void toUpper(const QString &text);
    void on_txtFltNaziv_textEdited(const QString &arg1);

    void on_treeAsset_itemPressed(QTreeWidgetItem *item, int column);
    void on_treeGrupeImovine_itemPressed(QTreeWidgetItem *item, int column);
    void on_treeImovina_itemPressed(QTreeWidgetItem *item, int column);
    void on_treeImovina_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btnUgovorneObveze_clicked();

    void on_btnMnuZahtjevPregled_clicked();

    void on_btnMnuZahtjevNemogucnost_clicked();

    void on_btnMnuUgovorPregled_clicked();

    void on_btnMnuUgovorSklapanje_clicked();

    void on_btnMnuObavijestSlanje_clicked();

    void on_btnMnuObavijestPoslane_clicked();

    void on_btnMnuZahtjevMax23_clicked();

    void on_btnMnuZahtjevNovi_clicked();

    void on_btnMnuPregled_clicked();

    void on_btnMnuCpeOprema_clicked();

    void on_btnMnuFizickaStranka_clicked();

    void on_btnMnuPravnaOsoba_clicked();

    void on_btnMnuTipStranke_clicked();

    void on_btnMnuNovaUloga_clicked();

    void on_btnMnuNovaUlogaStranka_clicked();

    void on_btnMnuPorez_clicked();

    void on_btnMnuPripadnostPodjeli_clicked();

    void on_btnMnuAtributi_clicked();

    void on_btnMnuFilterListaN_clicked();


    void on_btnSviKupci_toggled(bool checked);

    void on_btnAktivniKupci_toggled(bool checked);


    void on_btnIzmjenaAtributa_clicked();

    void on_treeStranke_itemPressed(QTreeWidgetItem *item, int column);

    void on_btnStrankaZurnal_clicked();

    void on_btnImovinaEdit_clicked();

    void on_btnMnuOsf_clicked();

    void on_btnMnuMdmPodaci_clicked();

    void on_btnMnuKanalProdaje_clicked();

    void on_btnF2x_clicked();

    void on_btnBundleInfo_clicked();

    void on_btnMnuPrigovorAdd_clicked();

    void on_btnMnuPrigovorPregled_clicked();

    void on_btnMnuPrigovorOdobrenje_clicked();

    void on_btnMnuPrigovorPismo_clicked();

    void on_btnStatusBarDonatDabase_clicked();

    void on_btnPromjenaKanalaProdaje_clicked();

    void on_btnLogiraniKorisnik_clicked();

    void on_btnMnuSuspenzija_clicked();

    void on_btnMnuZlonamjerniPregled_clicked();

    void on_btnMnuZlonamjerniUnosMob_clicked();

private:
    Ui::FrmDonatMenu *ui;

    // Donat main search mode
    enum DonatSearchMode
    {
        TraziPoNazivKorisnika = 1,
        TraziPoBrojTelefona = 2,
        TraziPoJmbg = 3,
        TraziPoOib = 4,
        TraziPoUlogaStrankeId = 5,
        TraziPoTicketId = 6,
        TraziPoAssetId = 7,
        TraziPoGrupna = 8,
        TraziPoHijerahija = 9
    };
    DonatSearchMode m_SearchMode;
    enum DonatInfoMode
    {
        PrikaziInfo = 1,
        PrikaziInfoZahtjevi = 2,
        PrikaziInfoSmetnje = 3,
        PrikaziInfoKontakti = 4,
        PrikaziInfoOsobe = 5
    };
    DonatInfoMode m_InfoMode;
    bool m_bSearchAktivneKupce;
    // Donat main customer info
    unsigned int m_iStrankaId;
    long long m_iKupacId;
    unsigned int m_iGrupaImovineId;
    unsigned int m_iGrupaImovineIsStatus;
    unsigned int m_iGrupaImovineIsTip;
    unsigned int m_iImovinaId;
    int m_iImovinaIdStatus;
    string m_strTelefonskiBroj;
    string m_strTelefonskiBrojKlasa;
    string m_strOib;
    unsigned int m_iMdmId;
    bool m_bPunoGrupaImovine;
    bool m_bAktivnaGrupaImovine;
    bool m_bAktivnaImovina;
    bool m_bImovinaExpand;

    QIcon m_iconAdressValid;
    QIcon m_iconZuti;
    QIcon m_iconZeleni;
    QIcon m_iconCrveni;
    QIcon m_iconTransparent;

    struct gim_struktura_sve_t {
      string Tip;
      unsigned int Asset;
      unsigned int GrupaImovineId;
      string TelefonskiBroj;
      string Klasa;
    };

    void clearDonatSearchResults();
    void clearDonatStranka();
    void clearDonatStrankaAsset();

    // Customer search
    void traziDonatKorisnikaPoNazivu();
    void traziDonatKorisnikaPoBrojuTelefona();
    void traziDonatKorisnikaPoJmbg();
    void traziDonatKorisnikaPoOib();
    void traziDonatKorisnikaPoUlogaStrankeId();
    void traziDonatKorisnikaPoTicketId();
    void traziDonatKorisnikaPoAssetId();
    // Customer data
    void popuniStrankaUlogeStranaka();
    void popuniStrankaZastupnika();
    void provjeriOib();
    void popuniStrankaSveKlase();
    void popuniStrankaGrupeImovine();
    void popuniZaGrupuImovine();
    void popuniStrankaMdm(QTreeWidgetItem *itemDonatStranka);
    // [ Imovina ]
    void popuniSveImovine();
    void popuniImovinaAtribute(QTreeWidgetItem *itemImovina);
    void popuniImovinaStatus();

    void popuniStrankaAdslStatus();
    void popuniStrankaIptvStatus();

    void popuniStrankaPoruke();
    void popuniStrankaPoruku(string strSqlStatement);
    void popuniInfoZahtjevi();

    int vratiIndikatorZaprikazUgovorneObveze(const unsigned int iGrupaImovineId, string strTip = string());
    string vratiChurnPhoneRizik(const string strPhoneNumber);


};

}

#endif // FRMDONATMENU_H
