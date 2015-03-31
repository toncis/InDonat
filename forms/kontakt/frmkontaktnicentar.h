//
//  frmkontakticentar.h
//
//  Author:
//       Tonči Sviličić <tonci.svilicic@in2.hr>
//
//  Copyright (c) 2012 Tonči Sviličić
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef FRMKONTAKTNICENTAR_H
#define FRMKONTAKTNICENTAR_H

#include <QMainWindow>
#include <QDateTime>

#include "donat.h"

namespace Ui {
class FrmKontaktniCentar;
}

namespace Kontakt {

class FrmKontaktniCentar : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FrmKontaktniCentar(QWidget *parent = 0);
    explicit FrmKontaktniCentar(QWidget *parent = 0, string strTelefonskiBroj = "");
    ~FrmKontaktniCentar();
    
private slots:
    void on_btnChangeUserRole_clicked();

    void on_btnContactSearch_clicked();

    void on_btnOsf_clicked();

    void on_btnList_clicked();

    void on_btnAnonymous_clicked();

    void on_btnIdentification_clicked();

    void on_btnMjerenjeBrzine_clicked();

    void on_btnUgovorneObveze_clicked();

    void on_btnStrankaEdit_clicked();

    void on_btnEmailEdit_clicked();

    void on_btnTipKupcaEdit_clicked();

    void on_btnInstalacijaEdit_clicked();

    void on_btnRacunEdit_clicked();

    void on_btnLoyaltyEdit_clicked();

    void on_btnTreeImovinaExpand_clicked();

    void on_btnTreeImovinaColapse_clicked();

    void on_btnKontakOsobeExpand_clicked();

    void on_btnKontakOsobeColapse_clicked();

    void on_btnKontakiExpand_clicked();

    void on_btnKontakiColapse_clicked();

    void on_btnOdustani_clicked();

    void on_btnTipStranke_2_clicked();

    void on_btnRacunStranke_clicked();

    void on_btnStrankaBiljeska_clicked();

    void on_btnStrankaIzjave_clicked();

    void on_btnStrankaTipInfo_clicked();

    void on_btnStrankaRacunInfo_clicked();

    void on_btnStrankaBiljeskaInfo_clicked();

    void on_btnStrankaIzjaveInfo_clicked();

private:
    Ui::FrmKontaktniCentar *ui;

    struct gim_struktura_t {
      unsigned int KupacId;
      string KupacNaziv;
      int Status;
      unsigned int GrupaImovineId;
      string TelefonskiBroj;
      string Klasa;
    };

    list<gim_struktura_t> m_lstKupacTelefon1;
    list<gim_struktura_t> m_lstKupacTelefon2;

    struct kup_struktura_t {
//        Dim KUPAC_OK
//        Dim KUPAC_STRANKA_NO
//        Dim KUPAC_NO
//        Dim KUPAC_NAZ
//        Dim KUPAC_ADRESA
//        Dim KUPAC_AD1
//        Dim KUPAC_AD2
//        Dim KUPAC_ADRESA_NO
//        Dim KUPAC_MB
//        Dim KUPAC_OIB
//        Dim KUPAC_EMAIL
//        Dim KUPAC_TIP_NO
//        Dim KUPAC_TIP_NAZ
//        Dim KUPAC_ZASTUPNIK_NO
//        Dim KUPAC_SEGMENT_NO
//        Dim KUPAC_SEGMENT_NAZ
//        Dim KUPAC_KLJUCNI
//        Dim HEAD_NO
//        Dim HEAD_STRANKA_NO
//        Dim KUPAC_IMF_NO
//        Dim KUPAC_LOYALTY_NO
//        Dim NAPLATA_NO
//        Dim INSTALACIJA_NO

      unsigned int KupacId;
      unsigned int KUPAC_STRANKA_NO;
      string KUPAC_NAZ;
      string KUPAC_ADRESA;
      string KUPAC_AD1;
      string KUPAC_AD2;
      unsigned int KUPAC_ADRESA_NO;
      string KUPAC_MB;
      string KUPAC_OIB;
      string KUPAC_EMAIL;
      int KUPAC_TIP_NO;
      int TSTRANKE3_ID;
      int KUPAC_SEGMENT_NO;
      string KUPAC_SEGMENT_NAZ;
      string KUPAC_TIP_NAZ;
      unsigned int HEAD_NO;
      unsigned int HEAD_STRANKA_NO;
      unsigned int KUPAC_LOYALTY_NO;
    };


    unsigned int m_iKupacId;
    string m_strKUPAC_NAZ;
    unsigned int m_iBillingAccountId;
    string m_strBillingAccountNaziv;
    unsigned int m_iInstalacijaId;
    string m_strInstalacijaNaziv;
    unsigned int m_iGrupaImovineId;
    string m_strTelefonskiBroj;

    unsigned int m_iKUPAC_STRANKA_NO;
    string m_strKUPAC_MB;
    string m_strKUPAC_ADRESA;
    string m_strKUPAC_AD1;
    string m_strKUPAC_AD2;
    int m_iKUPAC_SEGMENT_NO;
    string m_strKUPAC_ZASTUPNIK_NO;

    int m_iKUPAC_TIP_NO;
    unsigned int m_iHEAD_NO;

    unsigned int m_iAKT_GIM_NO;
    int m_iAKT_TEL_NO;
    string m_strAKT_TEL_KLASA;

    int m_iGRP_TIP;

    int m_iAktivnostNo;
    int m_iAKT_CODE_LOG;
    int m_iAKT_CODE;
    int m_iAKT_STATUS;
    int m_iROLA_VEL_NO;
    int m_iAKT_CODE_ROLA;

    string m_strANONIM_VAL;
    string m_strCC_KON_VALUE;

    unsigned int m_iOSOBA_NO;
    unsigned int m_iOSOBA_ITEM_NO;
    string m_strOSOBA_ITEM_NAZ;

    void initForm();
    void popunaRole();
    void popunaAnonimniKupacVrijednost();
    void popunaAnonimac();
    void popunaAnonimacKontakt();
    void popunaUpit();
    void popunaKupacTelefon1();
    void popunaKupacTelefon2();
    void popunaKupac();
    bool popunaKupac_ProvjeriStanje();
    void popunaOsobe();
    void popunaKontakt_A();
    void popunaUlogaStranke();
    void popunaGrupaImovine();
    void popuniInfoPanel();
    void popuniKupceNaoDabir();

};

}
#endif // FRMKONTAKTNICENTAR_H
