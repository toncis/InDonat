//
//  wgdonatmenu1.h
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
