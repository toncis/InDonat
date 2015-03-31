//
//  frmsuspenzija.h
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

#ifndef FRMSUSPENZIJA_H
#define FRMSUSPENZIJA_H

#include <QDialog>
#include <QTreeWidget>
#include <QTime>

#include "donat.h"

namespace Ui {
class FrmSuspenzija;
}

namespace Sporazumi {

class FrmSuspenzija : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSuspenzija(QWidget *parent = 0);
    ~FrmSuspenzija();

private slots:
    void on_btnTrazi_clicked();

    void on_btnTelefon_clicked();

    void on_btnAsset_clicked();

    void on_btnKupac_clicked();

    void on_btnBillingAccount_clicked();

    void on_btnSuspenzija_clicked();

    void on_btnResuspenzija_clicked();

    void on_btnPotvrda_clicked();

    void on_btnZatvori_clicked();

    void on_btnIspisliste_clicked();

    void on_btnUkloniListu_clicked();

    void on_btnUkloniStavku_clicked();

    void on_btnUkloniPlacanje_clicked();

    void on_pushButton_clicked();

    void on_treeWidget_itemPressed(QTreeWidgetItem *item, int column);

    void on_treeWidget_2_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmSuspenzija *ui;

    // Search mode
    enum DonatSearchMode
    {
        TraziPoTelefonu = 1,
        TraziPoAssetId = 2,
        TraziPoKupacId = 3,
        TraziPoRacunId = 4
    };
    DonatSearchMode m_SearchMode;




    void initForm();

};

}   // namespace sporazumi

#endif // FRMSUSPENZIJA_H
