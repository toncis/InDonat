/************************************* Module Header **************************************\
* Module Name:  frmdonatmenu.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT main form
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


#include "frmdonatmenu_old.h"
#include "ui_frmdonatmenu_old.h"
#include "frmdonatabout.h"
#include "frmdonatuserrole.h"
#include "frmdonatpasswordchange.h"

FrmDonatMenu_Old::FrmDonatMenu_Old(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmDonatMenu_Old)
{
    ui->setupUi(this);

    this->ui->fraKlasa->setVisible(false);

    this->m_SearchMode = TraziPoNazivKorisnika;
    this->m_strTelefonskiBroj = new std::string();

    this->ui->actionClose->setIcon(QIcon::fromTheme("application-exit"));
    this->ui->actionO_programu->setIcon(QIcon::fromTheme("help-about"));
    this->ui->actionZaporka->setIcon(QIcon::fromTheme("security-high"));
    this->ui->actionA_uriraj_reporte->setIcon(QIcon::fromTheme("software-update-available"));
    this->ui->actionMojeRole->setIcon(QIcon::fromTheme("security-low"));

}

FrmDonatMenu_Old::~FrmDonatMenu_Old()
{
    m_strTelefonskiBroj->empty();
    CloseDonatConnection();
    delete ui;
}

void FrmDonatMenu_Old::on_cboFltSearchMode_currentIndexChanged(int index)
{
    switch (index)
    {
      case 0:
        m_SearchMode = TraziPoNazivKorisnika;
        break;
      case 1:
        m_SearchMode = TraziPoBrojTelefona;
        break;
      case 2:
        m_SearchMode = TraziPoJmbg;
        break;
      case 3:
        m_SearchMode = TraziPoOib;
        break;
      case 4:
        m_SearchMode = TraziPoUlogaStrankeId;
        break;
      case 5:
        m_SearchMode = TraziPoTicketId;
        break;
      case 6:
        m_SearchMode = TraziPoAssetId;
        break;
      case 7:
        m_SearchMode = TraziPoGrupna;
        break;
      case 8:
        m_SearchMode = TraziPoHijerahija;
        break;
      default:
        m_SearchMode = TraziPoNazivKorisnika;
      }
}

void FrmDonatMenu_Old::on_btnTrazi_clicked()
{

}

void FrmDonatMenu_Old::on_actionClose_triggered()
{
    this->close();
}

void FrmDonatMenu_Old::on_actionO_programu_triggered()
{
    // Show Donat about form
    Log::FrmDonatAbout *frmAbout = new Log::FrmDonatAbout();
    frmAbout->exec();
    delete frmAbout;
}

void FrmDonatMenu_Old::on_actionMojeRole_triggered()
{
    // Show Donat user roles
    Log::FrmDonatUserRole *frmDonatUserRoles = new Log::FrmDonatUserRole();
    frmDonatUserRoles->exec();
    delete frmDonatUserRoles;
}

void FrmDonatMenu_Old::on_actionZaporka_triggered()
{
    // Show Donat user password change
    Log::FrmDonatPasswordChange *frmDonatPasswordChange = new Log::FrmDonatPasswordChange();
    frmDonatPasswordChange->exec();
    delete frmDonatPasswordChange;
}
