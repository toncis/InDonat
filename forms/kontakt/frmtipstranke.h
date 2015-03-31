//
//  frmtipstranke.h
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

#ifndef FRMTIPSTRANKE_H
#define FRMTIPSTRANKE_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
    class FrmTipStranke;
}

namespace Kontakt {

class FrmTipStranke : public QDialog
{
    Q_OBJECT

public:
    explicit FrmTipStranke(QWidget *parent = 0);
    explicit FrmTipStranke(unsigned int iStrankaId, QWidget *parent = 0);
    explicit FrmTipStranke(unsigned int iStrankaId, unsigned int iKupacId, QWidget *parent = 0);
    ~FrmTipStranke();

private slots:

    void on_btnPotvrda_clicked();

    void on_txtTip1_textEdited(const QString &arg1);

    void on_txtTip2_textEdited(const QString &arg1);

    void on_txtTip3_textEdited(const QString &arg1);

    void on_txtSegment_textEdited(const QString &arg1);

    void on_txtOpomena_textEdited(const QString &arg1);

    void on_txtProfil_textEdited(const QString &arg1);

    void on_treeSifre_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmTipStranke *ui;

    // Tip Stranke sifarnik
    enum TipStrankeSifarnikMode
    {
        SifarnikModeTipStrankeNone   = 0,
        SifarnikModeTipStranke1 = 1,
        SifarnikModeTipStranke2 = 2,
        SifarnikModeTipStranke3 = 3,
        SifarnikModeMarketinskiSegment = 4,
        SifarnikModeTipoviOpominjanja = 5,
        SifarnikModeKreditniProfili = 6
    };

    TipStrankeSifarnikMode m_SifranikMode;

    unsigned int m_iStrankaId;
    unsigned int m_iKupacId;
    int m_iTipStranke1Id;
    int m_iTipStranke2Id;
    int m_iTipStranke3Id;
    int m_iMarketinskiSegmentId;
    int m_iTipOpominjanjaId;
    int m_iKreditniProfilId;

    bool provjeriSmijeLiMatPromjena(const unsigned int iKupacId);
    void popuniStranku(const unsigned int iStrankaId);

    void popuniTipStranke1();
    void popuniTipStranke2();
    void popuniTipStranke3();
    void popuniMarketSegmente();
    void popuniTipoveOpomena();
    void popuniKreditneProfile();

    void promjeniTipStranke();
};

}  // Kontakt

#endif // FRMTIPSTRANKE_H
