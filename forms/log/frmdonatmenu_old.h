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
* 	1.0		Created by Tonci Svilicic
\******************************************************************************************/

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
