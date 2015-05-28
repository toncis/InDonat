//
//  frmpregledimovine.h
//
//  Author:
//       Tonči Sviličić <tonci.svilicic@in2.hr>
//
//  Copyright (c) 2015 Tonči Sviličić
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

#ifndef FRMPREGLEDN_H
#define FRMPREGLEDN_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QDateTime>
#include "donat.h"

namespace Ui {
class FrmPregledN;
}

namespace Sporazumi {

class FrmPregledN : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPregledN(QWidget *parent = 0);
    ~FrmPregledN();

private slots:
    void on_btnPregledAktivnosti_clicked();

    void on_btnPromjenaKanalaProdaje_clicked();

    void on_cboPretragaKlase_currentIndexChanged(int index);

    void on_btnZahtjevUnio_clicked();

    void on_btnZahtjevProdao_clicked();

    void on_btnKanalProdaje_clicked();

    void on_btnRegija_clicked();

    void on_btnDonatUser_clicked();

    void on_btnZahtjev_clicked();

    void on_btnUgovor_clicked();

    void on_btnObavijest_clicked();

    void on_btnSme_clicked();

    void on_btnPretragaPrivatni_clicked();

    void on_btnPretragaKljucni_clicked();

    void on_btnPretragatSme_clicked();

    void on_btnPretragaVeleprodaja_clicked();

    void on_treeListeGrupa_itemPressed(QTreeWidgetItem *item, int column);

    void on_btnFilterFormatiraniNaziv_clicked();

    void on_btnFilterAdresa_clicked();

    void on_btnTrazi_clicked();

    void on_btnFiletrBrojDokumenta_clicked();

    void on_btnFilterBrojTelefona_clicked();

    void on_btnFilterAsset_clicked();

    void on_btnFilterBrojSporazuma_clicked();

    void on_btnFilterTicket_clicked();

    void on_btnFilterKupacId_clicked();

    void on_treeSporazumi_itemPressed(QTreeWidgetItem *item, int column);

    void on_treeSporazumLista_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmPregledN *ui;

    int m_iNoDef;

    unsigned int m_iSporazumId;
    unsigned int m_iStrankaId;
    unsigned int m_iKupacId;
    unsigned int m_iSporazumSlogId;
    unsigned int m_iPoslovniProcesId;
    unsigned int m_iGrupaImovineId;
    string m_strBrojDokumenta;
    QDateTime m_dateDatumzahtjeva;

    int m_iListaGrupa;
    int m_iTipKorisnika;
    int m_iTipKanala;
    int m_iTipKupca;
    int m_iTipFiltra;
    int m_iTipDodatnogFiltra;
    int m_iFltLinijaProdukataId;

    int m_iListaTipId;
    string m_strListaValue;
    int m_iListaSub;
    int m_iListaSel;

    QIcon m_iconUkljucenje;
    QIcon m_iconPromjena;
    QIcon m_iconIskljucenje;
    QIcon m_iconZuti;
    QIcon m_iconZeleni;
    QIcon m_iconCrveni;
    QIcon m_iconTransparent;

    void initForm();
    void initSporazum();
    void initSlog();
    void setKorisnik();
    void popunaKlasa();
    void popunaListaGrupa();
    void pokreniPretrazivanje();
    void popunaZahtjevaL1();
    void popunaZahtjevaL2();
    void popunaUgovoraL1();
    void popunaUgovoraL2();
    void popunaObavijestL1();
    void popunaPregledaZahtjevaNew();
    void popunaKupca();
    void popuniSporazumListu();
    void popunaSporazumSlog();
    void popunaWwmsGreska();
    void popunaWwmsRazlog();
    void popunaWwmsStorno();
    void popunaSporazumAktivnosti();
    void popunaOstalo();

    void addNewGrupaToListGrupe(QList<QTreeWidgetItem *> listListaGrupa, QTreeWidgetItem *itemGrupa);

};

} // namespace sporazumi

#endif // FRMPREGLEDN_H
