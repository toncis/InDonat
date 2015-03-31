//
//  frmkontaktnicentaruser.h
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

#ifndef FRMKONTAKTNICENTARUSER_H
#define FRMKONTAKTNICENTARUSER_H

#include <QDialog>
#include <QTableWidget>
#include "donat.h"

namespace Ui {
class FrmKontaktniCentarUser;
}

namespace Kontakt {

class FrmKontaktniCentarUser : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmKontaktniCentarUser(QWidget *parent = 0, int iTipRole = 0);
    ~FrmKontaktniCentarUser();
    
private slots:
    void on_btnPotvrda_clicked();

    void on_grdKorisnickeGrupe_itemClicked(QTableWidgetItem *item);

private:
    Ui::FrmKontaktniCentarUser *ui;

    int m_iTipRole;
    int m_iRolaTip;
    int m_iGrupaId;
    string m_strGrupaNaziv;

    void popuniGrupe();
};

} // Kontakt

#endif // FRMKONTAKTNICENTARUSER_H
