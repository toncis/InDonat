//
//  frmdonatmenu_old.h
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


#ifndef FRMDONATMENU_OLD_H
#define FRMDONATMENU_OLD_H

#include <QMainWindow>
#include "donat.h"

namespace Ui {
    class FrmDonatMenu_Old;
}

class FrmDonatMenu_Old : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmDonatMenu_Old(QWidget *parent = 0);
    ~FrmDonatMenu_Old();

private slots:
    void on_cboFltSearchMode_currentIndexChanged(int index);

    void on_btnTrazi_clicked();

    void on_actionClose_triggered();

    void on_actionO_programu_triggered();

    void on_actionMojeRole_triggered();

    void on_actionZaporka_triggered();

private:
    // Qt designer is used for this form
    Ui::FrmDonatMenu_Old *ui;

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

    // Donat main search mode
    DonatSearchMode m_SearchMode;
    // Donat main customer info
    long m_iStrankaId;
    long m_iKupacId;
    long m_iGrupaImovineId;
    int m_iGrupaImovineIsStatus;
    int m_iGrupaImovineIsTip;
    std::string *m_strTelefonskiBroj;

};



#endif // FRMDONATMENU_OLD_H
