//
//  frmzahtjevipregled.h
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

#ifndef FRMZAHTJEVIPREGLED_H
#define FRMZAHTJEVIPREGLED_H

#include <QDialog>
#include <QTableWidgetItem>

#include "donat.h"

namespace Ui {
class FrmZahtjeviPregled;
}

namespace Sporazumi {

class FrmZahtjeviPregled : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmZahtjeviPregled(QWidget *parent = 0);
    explicit FrmZahtjeviPregled(unsigned int iKupacId, QWidget *parent = 0);
    ~FrmZahtjeviPregled();
    
private slots:
    void on_btnPrivatniKupci_clicked();
    void on_btnKlucniKupci_clicked();
    void on_btnPoslovniKupci_clicked();
    void on_btnDanas_clicked();
    void on_btnOvajTjedan_clicked();
    void on_btnOvajMjesec_clicked();
    void on_btnStatusSvi_clicked();
    void on_btnStatusUtijeku_clicked();
    void on_btnStatusRezerviran_clicked();
    void on_btnStatusStorniran_clicked();
    void on_btnStorno_clicked();
    void on_btnStornoDonat_clicked();
    void on_btnNastavakRealizacije_clicked();
    void on_btnPretvoriU1Kunu_clicked();
    void on_btnKlasa_clicked();
    void on_btnKanalProdaje_clicked();
    void on_btnMojiDokumenti_clicked();
    void on_btnOznaciSve_clicked();
    void on_btnOznaciNista_clicked();
    void on_btnPregledSporazuma_clicked();
    void on_btnPregledStanjaDonat_clicked();
    void on_btnPregledStanjaWwms_clicked();
    void on_btnPregledDetaljno_clicked();
    void on_btnPregledProcesi_clicked();
    void on_btnPregledDisKarta_clicked();
    void on_btn_Napomena_clicked();
    void on_btnDatoteka_clicked();
    void on_btnSpis_clicked();
    void on_btnJop_clicked();
    void on_btnDodijeliJop_clicked();
    void on_btnOpisZaduzenja_clicked();
    void on_btnUlaznePoruke_clicked();
    void on_btnPromjenaKPro_clicked();
    void on_btnDatumZahtjeva_clicked();
    void on_btnIsipisDokumenta_clicked();

    void on_lstvZahtjevi_itemPressed(QTableWidgetItem *item);

    void on_cboKlase_currentIndexChanged(const QString &arg1);

private:
    Ui::FrmZahtjeviPregled *ui;

    // [Private Class Members]
    unsigned int m_iStrankaId;
    unsigned int m_iKupacId;
    long long m_iUlogaStrankeId;
    int m_iTipUlogaStrankeId;

    int m_iTipKanalaProdaje;
    string m_strKanalProdaje;
    int m_iFltLinijaProduktaId;

    int m_iTipDokumenta;

    unsigned int m_iSporazumId;


    // Zahtjev search mode
    enum TipKupcaSearchMode
    {
        SearchModePrivatni = 1,
        SearchModePoslovni = 2,
        SearchModeKljucni = 3
    };
    TipKupcaSearchMode m_TipKupcaSearchMode;
    enum PeriodSearchMode
    {
        SearchModeTipNone = 0,
        SearchModeDanas = 1,
        SearchModeOvajTjedan = 2,
        SearchModeOvajMjesec = 3
    };
    PeriodSearchMode m_PeriodSearchMode;
    enum StatusSearchMode
    {
        SearchModeSvi = -1,
        SearchModeUTijeku = 1,
        SearchModeRezerviran = 8,
        SearchModeRealiziran = 4,
        SearchModeStorniran = 5,
        SearchModeValidacija = 9
    };
    StatusSearchMode m_StatusSearchMode;

    QIcon m_iconCickled;

    // [Private Member Functions]
    void initFormView();
    void popuniSveKlase();
    void popuniKanalProdaje();
    void popuniZahtjeve();

};

}

#endif // FRMZAHTJEVIPREGLED_H
