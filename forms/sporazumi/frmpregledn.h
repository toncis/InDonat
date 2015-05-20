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

private:
    Ui::FrmPregledN *ui;

    unsigned int m_iSporazumId;
    int m_iListaGrupa;
    int m_iTipKorisnika;
    int m_iTipKanala;
    int m_iTipKupca;
    int m_iTipFiltra;
    int m_iFltLinijaProdukataId;

    void initForm();
    void initSporazum();
    void initSlog();
    void setKorisnik();
    void popunaKlasa();
    void popunaListaGrupa();
    void addNewGrupaToListGrupe(QList<QTreeWidgetItem *> listListaGrupa, QTreeWidgetItem *itemGrupa);

};

} // namespace sporazumi

#endif // FRMPREGLEDN_H
