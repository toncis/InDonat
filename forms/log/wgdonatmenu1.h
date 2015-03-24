/************************************* Module Header **************************************\
* Module Name:  wgdonatmenu.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of widget wgDonatMenu for the DONAT menu form
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

#ifndef WGDONATMENU1_H
#define WGDONATMENU1_H

#include <QWidget>
#include <QtWidgets>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QScrollArea;
class QLabel;
class QFrame;
class QToolBox;
class QWidget;
class QPushButton;
QT_END_NAMESPACE

namespace Log {

class WgDonatMenu1 : public QWidget
{
    Q_OBJECT

public:

    explicit WgDonatMenu1(QWidget *parent = 0);
    ~WgDonatMenu1();

    // [Dokumenti]
    QPushButton *m_btnCpeOprema;
    QPushButton *m_btnZahtjevMax23;
    QPushButton *m_btnPregled;

    // [Stranka]
    QPushButton *m_btnOcv;
    QPushButton *m_btnFizickaOsoba;
    QPushButton *m_btnPravnaOsoba;


signals:

public slots:

private:

    // [0]
    QVBoxLayout *m_vboxDonatMenu;
    QScrollArea *m_scrMainMenu;
    QToolBox *m_tboxDonatMenu;

    // [1]
    QWidget *m_pageDokumenti;
    // [Stranka]
    QWidget *m_pageStranka;
    QWidget *m_pageUlogeStranke;
    QWidget *m_pageAdreseStranke;
    QWidget *m_pagePregledIzItb;
    QWidget *m_pageCcar;
    QWidget *m_pageSmetnje;
    QWidget *m_pageWwms;
    QWidget *m_pageIspravak;
    QWidget *m_pageNpCps;
    QWidget *m_pageVeleprodaja;
    QWidget *m_pageTrajniNalog;
    QWidget *m_pageListeInteresa;
    QWidget *m_pageOtpustDuga;
    QWidget *m_pageCuba;
    QWidget *m_pageTpartneri;
    QWidget *m_pagePrigovori;
    QWidget *m_pageDataUsluge;
    QWidget *m_pageUgovoriPopusta;
    QWidget *m_pageSla;
    QWidget *m_pageTehnickiProcesi;
    QWidget *m_pageTaskManagement;
    QWidget *m_pageZlonamjerniPozivi;

    // [10]
    QFrame *m_fraMainMenuImage;
    QLabel *m_imgMainMenuImage;

    // Create Donat Menu
    void createMainMenu();
    // Create Donat Menu toolbars
    void createDokumenti();
    void createStranka();
    void createUlogeStranke();
    void createAdreseStranke();
    void createPregledIzItb();
    void createCcar();
    void createSmetnje();
    void createWwms();
    void createIspravak();
    void createNpCps();
    void createVeleprodaja();
    void createTrajniNalog();
    void createListeInteresa();
    void createOtpustDuga();
    void createCuba();
    void createTpartneri();
    void createPrigovori();
    void createDataUsluge();
    void createUgovoriPopusta();
    void createSla();
    void createTehnickiProcesi();
    void createTaskManagement();
    void createZlonamjerniPozivi();

    // Create Donat Menu image
    void createMainImage();
    void createMainActions();

};

}   // namespace log

#endif // WGDONATMENU1_H
