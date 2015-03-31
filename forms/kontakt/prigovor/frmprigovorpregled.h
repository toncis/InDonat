//
//  frmprigovorpregled.h
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

#ifndef FRMPRIGOVORPREGLED_H
#define FRMPRIGOVORPREGLED_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"


namespace Ui {
class FrmPrigovorPregled;
}

namespace Kontakt {
class FrmPrigovorPregled : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorPregled(QWidget *parent = 0);
    ~FrmPrigovorPregled();

private slots:
    void on_btnClanGrupe_clicked();

    void on_btnVoditeljGrupe_clicked();

    void on_cboClanGrupe_currentIndexChanged(const QString &arg1);

    void on_cboVoditeljGrupe_currentIndexChanged(const QString &arg1);

    void on_btnStatusSvi_clicked();

    void on_btnStatusUtijeku_clicked();

    void on_btnStatusZavrseno_clicked();

    void on_btnStatusStorno_clicked();

    void on_btnOdabirPrigovorTipova_clicked();

    void on_treePrigovori_itemPressed(QTreeWidgetItem *item, int column);

    void on_btnPrigovorsStatusi_clicked();

    void on_btnPrigovorEdit_clicked();

    void on_btnGo2_8_clicked();

    void on_btnGo2_18_clicked();

    void on_btnGo2_10_clicked();

    void on_btnGo2_11_clicked();

    void on_btnKontaktDokumenti_clicked();

private:
    Ui::FrmPrigovorPregled *ui;

    QIcon m_iconKupac;
    QIcon m_iconTelefon;
    QIcon m_iconMobitel;
    QIcon m_iconInternet;
    QIcon m_iconPrinter;
    QIcon m_iconEmail;
    QIcon m_iconBundle;
    QIcon m_iconZuti;
    QIcon m_iconZeleni;
    QIcon m_iconCrveni;
    QIcon m_iconTransparent;

    int m_iKontaktId;
    int m_iPrigovorId;
    int m_iStavkaId;
    int m_iStavkaStatusId;

    int m_iPrigovorFileter1;
    int m_iPrigovorFileter2;
    int m_iTipKorisnika;
    int m_iAktivnaKorisnikGrupa;
    string m_strSveKorisnikGrupe;
    string m_strAktivnaKorisnikGrupa;
    string m_strAktivniKorisnikId;

    int m_iKorisnickiKanalId;
    unsigned int m_iKupacId;
    string m_strKupacNaziv;
    int m_iKupacTipId;
    string m_strTelefonskiBroj;
    unsigned int m_iGrupaImovineId;
    int m_iZaGrupaId;
    string m_strZaGrupaNaziv;
    unsigned int m_iUslugaNaplataId;
    int m_iZahtjevTipId;
    unsigned int m_iZahtjevId;
    string m_strST_Opis;
    int m_iRjesenjeStatusId;
    int m_iRjesenjeTipId;
    int m_iOdobrenjeStatusId;
    int m_iOdobrenjeNivoId;
    int m_iNaplataStatusId;
    int m_iDokumentStatusId;
    int m_iTehnikaStatusId;
    int m_iTehnikaRegijaId;

    // Tip prigovora prikaz
    enum TipPrigovoraMode
    {
        PrikaziPrigovoreSve   = 1,
        PrikaziPrigovoreUtijeku = 2,
        PrikaziPrigovoreZavrsene = 3,
        PrikaziPrigovoreStornirane = 4
    };

    TipPrigovoraMode m_TipPrigovora;


    void initForm();
    void clearPrigovor();
    void popuniKorisnikGrupe();
    void popuniKorisnikAgent();
    void popuniPrigovore();
    void popuniPrigovor();
    void popuniPrilogDatoteke();
    int getKontaktId(int iStavkaId);
};

}
#endif // FRMPRIGOVORPREGLED_H
