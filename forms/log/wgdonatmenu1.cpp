/************************************* Module Header **************************************\
* Module Name:  wgdonatmenu.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of wgDonatMenu DONAT menu form.
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

#include "wgdonatmenu1.h"

namespace Log {

WgDonatMenu1::WgDonatMenu1(QWidget *parent) :
    QWidget(parent)
{
    m_vboxDonatMenu = new QVBoxLayout();
    m_vboxDonatMenu->setContentsMargins(2, 2, 2, 2);
    m_vboxDonatMenu->setSpacing(1);
    m_scrMainMenu = new QScrollArea();
    m_scrMainMenu->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // [0]
    createMainMenu();
    m_vboxDonatMenu->addWidget(m_scrMainMenu);
    // [10]
    createMainImage();

    QSizePolicy fraDonatMenu1SizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    fraDonatMenu1SizePolicy.setHorizontalStretch(0);
    fraDonatMenu1SizePolicy.setVerticalStretch(0);
    this->setSizePolicy(fraDonatMenu1SizePolicy);

    setLayout(m_vboxDonatMenu);
}

void WgDonatMenu1::createMainMenu()
{
    m_tboxDonatMenu = new QToolBox();
    m_tboxDonatMenu->setFrameShape(QFrame::StyledPanel);

    QSizePolicy tboxPageSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tboxPageSizePolicy.setHorizontalStretch(0);
    tboxPageSizePolicy.setVerticalStretch(0);
    m_tboxDonatMenu->setSizePolicy(tboxPageSizePolicy);

    createDokumenti();
    createStranka();
    createUlogeStranke();
    createAdreseStranke();
    createPregledIzItb();
    createCcar();
    createSmetnje();
    createWwms();
    createIspravak();
    createNpCps();
    createVeleprodaja();
    createTrajniNalog();
    createListeInteresa();
    createOtpustDuga();
    createCuba();
    createTpartneri();
    createPrigovori();
    createDataUsluge();
    createUgovoriPopusta();
    createSla();
    createTehnickiProcesi();
    createTaskManagement();
    createZlonamjerniPozivi();

    QSizePolicy scrPageSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrPageSizePolicy.setHorizontalStretch(0);
    scrPageSizePolicy.setVerticalStretch(0);
    m_scrMainMenu->setSizePolicy(scrPageSizePolicy);

    m_scrMainMenu->setWidget(m_tboxDonatMenu);
}
void WgDonatMenu1::createDokumenti()
{
    m_pageDokumenti = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageDokumenti->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxDokumenti = new QVBoxLayout();
    vboxDokumenti->setContentsMargins(1, 1, 1, 1);
    vboxDokumenti->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageDokumenti->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnZahtjev = new QPushButton(tr("Zahtjev"));
    btnZahtjev->setFlat(TRUE);
    btnZahtjev->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnZahtjev);
    m_btnZahtjevMax23 = new QPushButton(tr("Zahtjev Max 2-3"));
    m_btnZahtjevMax23->setFlat(TRUE);
    m_btnZahtjevMax23->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(m_btnZahtjevMax23);
    QPushButton *btnZahtjevGrupni = new QPushButton(tr("Zahtjev grupni"));
    btnZahtjevGrupni->setFlat(TRUE);
    btnZahtjevGrupni->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnZahtjevGrupni);
    QPushButton *btnKanalProdaje = new QPushButton(tr("Kanal prodaje"));
    btnKanalProdaje->setFlat(TRUE);
    btnKanalProdaje->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnKanalProdaje);
    m_btnPregled = new QPushButton(tr("Pregled"));
    m_btnPregled->setFlat(TRUE);
    m_btnPregled->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(m_btnPregled);
    QPushButton *btnPreseljenje = new QPushButton(tr("Preseljenje"));
    btnPreseljenje->setFlat(TRUE);
    btnPreseljenje->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnPreseljenje);
    QPushButton *btnNoviVlasnik = new QPushButton(tr("Novi vlasnik"));
    btnNoviVlasnik->setFlat(TRUE);
    btnNoviVlasnik->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnNoviVlasnik);
    QPushButton *btnProspekt = new QPushButton(tr("Prospekt"));
    btnProspekt->setFlat(TRUE);
    btnProspekt->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnProspekt);
    QPushButton *btnNetPhone = new QPushButton(tr("Net Phone"));
    btnNetPhone->setFlat(TRUE);
    btnNetPhone->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnNetPhone);
    QPushButton *btnNetPhoneOff = new QPushButton(tr("Net Phone OFF"));
    btnNetPhoneOff->setFlat(TRUE);
    btnNetPhoneOff->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnNetPhoneOff);
    QPushButton *btnImfPodaci = new QPushButton(tr("IMF podaci"));
    btnImfPodaci->setFlat(TRUE);
    btnImfPodaci->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(btnImfPodaci);
    QPushButton *btnJednokratnoZaduzenje = new QPushButton(tr("Jednokratno zad."));
    btnJednokratnoZaduzenje->setCursor(Qt::PointingHandCursor);
    btnJednokratnoZaduzenje->setFlat(TRUE);
    vboxDokumenti->addWidget(btnJednokratnoZaduzenje);
    m_btnCpeOprema = new QPushButton(tr("CP oprema"));
    m_btnCpeOprema->setFlat(TRUE);
    m_btnCpeOprema->setCursor(Qt::PointingHandCursor);
    vboxDokumenti->addWidget(m_btnCpeOprema);

    m_pageDokumenti->setLayout(vboxDokumenti);
    m_tboxDonatMenu->addItem(m_pageDokumenti, tr("Dokumenti"));
}
void WgDonatMenu1::createStranka()
{
    m_pageStranka = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageStranka->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxStranka = new QVBoxLayout();
    vboxStranka->setContentsMargins(1, 1, 1, 1);
    vboxStranka->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageStranka->setSizePolicy(pagePageSizePolicy);

    m_btnFizickaOsoba = new QPushButton(tr("Fizička osoba"));
    m_btnFizickaOsoba->setFlat(TRUE);
    m_btnFizickaOsoba->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(m_btnFizickaOsoba);
    m_btnPravnaOsoba = new QPushButton(tr("Pravna osoba"));
    m_btnPravnaOsoba->setFlat(TRUE);
    m_btnPravnaOsoba->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(m_btnPravnaOsoba);
    QPushButton *btnTip = new QPushButton(tr("Tip"));
    btnTip->setFlat(TRUE);
    btnTip->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnTip);
    QPushButton *btnNovaUloga = new QPushButton(tr("Nova uloga"));
    btnNovaUloga->setFlat(TRUE);
    btnNovaUloga->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnNovaUloga);
    QPushButton *btnNovaUlogaStranaka = new QPushButton(tr("Nova uloga-stranaka"));
    btnNovaUlogaStranaka->setFlat(TRUE);
    btnNovaUlogaStranaka->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnNovaUlogaStranaka);
    QPushButton *btnPorez = new QPushButton(tr("Porez"));
    btnPorez->setFlat(TRUE);
    btnPorez->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnPorez);
    QPushButton *btnPripadnostPodjeli = new QPushButton(tr("Pripadnost podjeli"));
    btnPripadnostPodjeli->setFlat(TRUE);
    btnPripadnostPodjeli->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnPripadnostPodjeli);
    QPushButton *btnAtributi = new QPushButton(tr("Atributi"));
    btnAtributi->setFlat(TRUE);
    btnAtributi->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnAtributi);
    QPushButton *btnKontaktSaStrankom = new QPushButton(tr("Kontakt sa strankom"));
    btnKontaktSaStrankom->setFlat(TRUE);
    btnKontaktSaStrankom->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnKontaktSaStrankom);
    QPushButton *btnUkloniStranku = new QPushButton(tr("Ukloni stranku"));
    btnUkloniStranku->setFlat(TRUE);
    btnUkloniStranku->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnUkloniStranku);
    QPushButton *btnTajnostPodataka = new QPushButton(tr("Tajnost podataka"));
    btnTajnostPodataka->setFlat(TRUE);
    btnTajnostPodataka->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnTajnostPodataka);
    QFrame *hLine1 = new QFrame();
    hLine1->setFrameShape(QFrame::HLine);
    hLine1->setFrameShadow(QFrame::Sunken);
    vboxStranka->addWidget(hLine1);
    QPushButton *btnVasStranka = new QPushButton(tr("VAS - stranka"));
    btnVasStranka->setFlat(TRUE);
    btnVasStranka->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnVasStranka);
    QPushButton *btnVasPromijena = new QPushButton(tr("VAS - promijena"));
    btnVasPromijena->setFlat(TRUE);
    btnVasPromijena->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(btnVasPromijena);
    m_btnOcv = new QPushButton(tr("OCV"));
    m_btnOcv->setFlat(TRUE);
    m_btnOcv->setCursor(Qt::PointingHandCursor);
    vboxStranka->addWidget(m_btnOcv);

    m_pageStranka->setLayout(vboxStranka);
    m_tboxDonatMenu->addItem(m_pageStranka, tr("Stranka"));
}
void WgDonatMenu1::createUlogeStranke()
{
    m_pageUlogeStranke = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageUlogeStranke->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxUlogeStranke = new QVBoxLayout();
    vboxUlogeStranke->setContentsMargins(1, 1, 1, 1);
    vboxUlogeStranke->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageUlogeStranke->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnVrstaRacuna = new QPushButton(tr("Vrsta računa"));
    btnVrstaRacuna->setFlat(TRUE);
    btnVrstaRacuna->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnVrstaRacuna);
    QPushButton *btnTipKontakta = new QPushButton(tr("Tip kontakta"));
    btnTipKontakta->setFlat(TRUE);
    btnTipKontakta->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnTipKontakta);
    QPushButton *btnSviKontakti = new QPushButton(tr("Svi kontakti"));
    btnSviKontakti->setFlat(TRUE);
    btnSviKontakti->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnSviKontakti);
    QPushButton *btnAtributi = new QPushButton(tr("Atributi"));
    btnAtributi->setFlat(TRUE);
    btnAtributi->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnAtributi);
    QFrame *hLine2 = new QFrame();
    hLine2->setFrameShape(QFrame::HLine);
    hLine2->setFrameShadow(QFrame::Sunken);
    vboxUlogeStranke->addWidget(hLine2);
    QPushButton *btnGrupniRacun = new QPushButton(tr("Grupni račun"));
    btnGrupniRacun->setFlat(TRUE);
    btnGrupniRacun->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnGrupniRacun);
    QPushButton *btnPovezivanjeKupaca = new QPushButton(tr("Povezivanje kupaca"));
    btnPovezivanjeKupaca->setFlat(TRUE);
    btnPovezivanjeKupaca->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnPovezivanjeKupaca);
    QPushButton *btnPovezivanjeRacuna = new QPushButton(tr("Povezivanje računa"));
    btnPovezivanjeRacuna->setFlat(TRUE);
    btnPovezivanjeRacuna->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnPovezivanjeRacuna);
    QPushButton *btnMassmerge = new QPushButton(tr("MASmerge"));
    btnMassmerge->setFlat(TRUE);
    btnMassmerge->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnMassmerge);
    QPushButton *btnDostavaCd = new QPushButton(tr("Dostava CD_a"));
    btnDostavaCd->setFlat(TRUE);
    btnDostavaCd->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnDostavaCd);
    QFrame *hLine3 = new QFrame();
    hLine3->setFrameShape(QFrame::HLine);
    hLine3->setFrameShadow(QFrame::Sunken);
    vboxUlogeStranke->addWidget(hLine3);
    QPushButton *btnLoyalty = new QPushButton(tr("Loyalty"));
    btnLoyalty->setFlat(TRUE);
    btnLoyalty->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnLoyalty);
    QPushButton *btnLoyaltyOff = new QPushButton(tr("Loyalty OFF"));
    btnLoyaltyOff->setFlat(TRUE);
    btnLoyaltyOff->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnLoyaltyOff);
    QPushButton *btnDodjelaImf = new QPushButton(tr("Dodjela IMF_a"));
    btnDodjelaImf->setFlat(TRUE);
    btnDodjelaImf->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnDodjelaImf);
    QPushButton *btnLoyaltyIspravak = new QPushButton(tr("Loyalty ispravak"));
    btnLoyaltyIspravak->setFlat(TRUE);
    btnLoyaltyIspravak->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnLoyaltyIspravak);
    QPushButton *btnStanjeNagrada = new QPushButton(tr("Stanje nagrada"));
    btnStanjeNagrada->setFlat(TRUE);
    btnStanjeNagrada->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnStanjeNagrada);
    QPushButton *btnTclub = new QPushButton(tr("T Club"));
    btnTclub->setFlat(TRUE);
    btnTclub->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnTclub);
    QPushButton *btnTclubObavijesti = new QPushButton(tr("T Club obavjesti"));
    btnTclubObavijesti->setFlat(TRUE);
    btnTclubObavijesti->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnTclubObavijesti);
    QPushButton *btnTClubBonovi = new QPushButton(tr("T CLub bonovi"));
    btnTClubBonovi->setFlat(TRUE);
    btnTClubBonovi->setCursor(Qt::PointingHandCursor);
    vboxUlogeStranke->addWidget(btnTClubBonovi);

    m_pageUlogeStranke->setLayout(vboxUlogeStranke);
    m_tboxDonatMenu->addItem(m_pageUlogeStranke, tr("Uloge stranke"));
}
void WgDonatMenu1::createAdreseStranke()
{
    m_pageAdreseStranke = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageAdreseStranke->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxAdreseStranke = new QVBoxLayout();
    vboxAdreseStranke->setContentsMargins(1, 1, 1, 1);
    vboxAdreseStranke->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageAdreseStranke->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnAdreseStranke = new QPushButton(tr("Adrese stranke"));
    btnAdreseStranke->setFlat(TRUE);
    btnAdreseStranke->setCursor(Qt::PointingHandCursor);
    vboxAdreseStranke->addWidget(btnAdreseStranke);
    QPushButton *btnAdresaUloge = new QPushButton(tr("Adresa uloge"));
    btnAdresaUloge->setFlat(TRUE);
    btnAdresaUloge->setCursor(Qt::PointingHandCursor);
    vboxAdreseStranke->addWidget(btnAdresaUloge);
    QPushButton *btnPromjenaAdrese = new QPushButton(tr("Promjena adrese"));
    btnPromjenaAdrese->setFlat(TRUE);
    btnPromjenaAdrese->setCursor(Qt::PointingHandCursor);
    vboxAdreseStranke->addWidget(btnPromjenaAdrese);

    m_pageAdreseStranke->setLayout(vboxAdreseStranke);
    m_tboxDonatMenu->addItem(m_pageAdreseStranke, tr("Adrese stranke"));
}
void WgDonatMenu1::createPregledIzItb()
{
    m_pagePregledIzItb = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pagePregledIzItb->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxPregledIzItb = new QVBoxLayout();
    vboxPregledIzItb->setContentsMargins(1, 1, 1, 1);
    vboxPregledIzItb->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pagePregledIzItb->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnITBnovi = new QPushButton(tr("ITBnovi"));
    btnITBnovi->setFlat(TRUE);
    btnITBnovi->setCursor(Qt::PointingHandCursor);
    vboxPregledIzItb->addWidget(btnITBnovi);
    QPushButton *btnITBstari = new QPushButton(tr("ITBstari"));
    btnITBstari->setFlat(TRUE);
    btnITBstari->setCursor(Qt::PointingHandCursor);
    vboxPregledIzItb->addWidget(btnITBstari);
    QPushButton *btnITBdata = new QPushButton(tr("ITBdata"));
    btnITBdata->setFlat(TRUE);
    btnITBdata->setCursor(Qt::PointingHandCursor);
    vboxPregledIzItb->addWidget(btnITBdata);
    QFrame *hLine4 = new QFrame();
    hLine4->setFrameShape(QFrame::HLine);
    hLine4->setFrameShadow(QFrame::Sunken);
    vboxPregledIzItb->addWidget(hLine4);
    QPushButton *btnGeneva= new QPushButton(tr("Geneva"));
    btnGeneva->setFlat(TRUE);
    btnGeneva->setCursor(Qt::PointingHandCursor);
    vboxPregledIzItb->addWidget(btnGeneva);

    m_pagePregledIzItb->setLayout(vboxPregledIzItb);
    m_tboxDonatMenu->addItem(m_pagePregledIzItb, tr("Pregled iz ITB"));
}
void WgDonatMenu1::createCcar()
{
    m_pageCcar = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageCcar->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxCcar = new QVBoxLayout();
    vboxCcar->setContentsMargins(1, 1, 1, 1);
    vboxCcar->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageCcar->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnSlanjeuBilling = new QPushButton(tr("Slanje u Billing"));
    btnSlanjeuBilling->setFlat(TRUE);
    btnSlanjeuBilling->setCursor(Qt::PointingHandCursor);
    vboxCcar->addWidget(btnSlanjeuBilling);
    QPushButton *btnPoslanouBilling = new QPushButton(tr("Poslano u Billing"));
    btnPoslanouBilling->setFlat(TRUE);
    btnPoslanouBilling->setCursor(Qt::PointingHandCursor);
    vboxCcar->addWidget(btnPoslanouBilling);
    QPushButton *btnSuspenzija = new QPushButton(tr("Suspenzija"));
    btnSuspenzija->setFlat(TRUE);
    btnSuspenzija->setCursor(Qt::PointingHandCursor);
    vboxCcar->addWidget(btnSuspenzija);
    QPushButton *btnSuspenzijaNovi = new QPushButton(tr("Suspenzija novi"));
    btnSuspenzijaNovi->setFlat(TRUE);
    btnSuspenzijaNovi->setCursor(Qt::PointingHandCursor);
    vboxCcar->addWidget(btnSuspenzijaNovi);
    QFrame *hLine5 = new QFrame();
    hLine5->setFrameShape(QFrame::HLine);
    hLine5->setFrameShadow(QFrame::Sunken);
    vboxCcar->addWidget(hLine5);
    QPushButton *btnTipSuspenzije = new QPushButton(tr("Tip suspenzije"));
    btnTipSuspenzije->setFlat(TRUE);
    btnTipSuspenzije->setCursor(Qt::PointingHandCursor);
    vboxCcar->addWidget(btnTipSuspenzije);

    m_pageCcar->setLayout(vboxCcar);
    m_tboxDonatMenu->addItem(m_pageCcar, tr("Ccar"));
}
void WgDonatMenu1::createSmetnje()
{
    m_pageSmetnje = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageSmetnje->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxSmetnje = new QVBoxLayout();
    vboxSmetnje->setContentsMargins(1, 1, 1, 1);
    vboxSmetnje->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageSmetnje->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnPrijavaSmetnje = new QPushButton(tr("Prijava smetnje"));
    btnPrijavaSmetnje->setFlat(TRUE);
    btnPrijavaSmetnje->setCursor(Qt::PointingHandCursor);
    vboxSmetnje->addWidget(btnPrijavaSmetnje);
    QPushButton *btnPregledSmetnji = new QPushButton(tr("Pregled smetnji"));
    btnPregledSmetnji->setFlat(TRUE);
    btnPregledSmetnji->setCursor(Qt::PointingHandCursor);
    vboxSmetnje->addWidget(btnPregledSmetnji);
    QFrame *hLine6 = new QFrame();
    hLine6->setFrameShape(QFrame::HLine);
    hLine6->setFrameShadow(QFrame::Sunken);
    vboxSmetnje->addWidget(hLine6);
    QPushButton *btnPrijavaRada = new QPushButton(tr("Prijava rada"));
    btnPrijavaRada->setFlat(TRUE);
    btnPrijavaRada->setCursor(Qt::PointingHandCursor);
    vboxSmetnje->addWidget(btnPrijavaRada);
    QPushButton *btnServer = new QPushButton(tr("Server"));
    btnServer->setFlat(TRUE);
    btnServer->setCursor(Qt::PointingHandCursor);
    vboxSmetnje->addWidget(btnServer);
    QPushButton *btnAgenti = new QPushButton(tr("Agenti"));
    btnAgenti->setFlat(TRUE);
    btnAgenti->setCursor(Qt::PointingHandCursor);
    vboxSmetnje->addWidget(btnAgenti);
    QPushButton *btnStatistika = new QPushButton(tr("Statistika"));
    btnStatistika->setFlat(TRUE);
    btnStatistika->setCursor(Qt::PointingHandCursor);
    vboxSmetnje->addWidget(btnStatistika);
    QPushButton *btnSmetnjaTest = new QPushButton(tr("Smetnja test"));
    btnSmetnjaTest->setFlat(TRUE);
    btnSmetnjaTest->setCursor(Qt::PointingHandCursor);
    vboxSmetnje->addWidget(btnSmetnjaTest);

    m_pageSmetnje->setLayout(vboxSmetnje);
    m_tboxDonatMenu->addItem(m_pageSmetnje, tr("Smetnje"));
}
void WgDonatMenu1::createWwms()
{
    m_pageWwms = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageWwms->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxWwms = new QVBoxLayout();
    vboxWwms->setContentsMargins(1, 1, 1, 1);
    vboxWwms->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageWwms->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnListaSporazuma = new QPushButton(tr("Lista sporazuma"));
    btnListaSporazuma->setFlat(TRUE);
    btnListaSporazuma->setCursor(Qt::PointingHandCursor);
    vboxWwms->addWidget(btnListaSporazuma);
    QPushButton *btnPopunaAtributa = new QPushButton(tr("Popuna atributa"));
    btnPopunaAtributa->setFlat(TRUE);
    btnPopunaAtributa->setCursor(Qt::PointingHandCursor);
    vboxWwms->addWidget(btnPopunaAtributa);

    m_pageWwms->setLayout(vboxWwms);
    m_tboxDonatMenu->addItem(m_pageWwms, tr("Wwms"));
}
void WgDonatMenu1::createIspravak()
{
    m_pageIspravak = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageIspravak->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxIspravaka = new QVBoxLayout();
    vboxIspravaka->setContentsMargins(1, 1, 1, 1);
    vboxIspravaka->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageIspravak->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnStatus = new QPushButton(tr("Status"));
    btnStatus->setFlat(TRUE);
    btnStatus->setCursor(Qt::PointingHandCursor);
    vboxIspravaka->addWidget(btnStatus);
    QPushButton *btnImovina = new QPushButton(tr("Imovina"));
    btnImovina->setFlat(TRUE);
    btnImovina->setCursor(Qt::PointingHandCursor);
    vboxIspravaka->addWidget(btnImovina);
    QPushButton *btnBrojTelefona = new QPushButton(tr("Broj telefona"));
    btnBrojTelefona->setFlat(TRUE);
    btnBrojTelefona->setCursor(Qt::PointingHandCursor);
    vboxIspravaka->addWidget(btnBrojTelefona);
    QPushButton *btnNovaImovina = new QPushButton(tr("Nova imovina"));
    btnNovaImovina->setFlat(TRUE);
    btnNovaImovina->setCursor(Qt::PointingHandCursor);
    vboxIspravaka->addWidget(btnNovaImovina);
    QPushButton *btnImfVeza = new QPushButton(tr("IMF veza"));
    btnImfVeza->setFlat(TRUE);
    btnImfVeza->setCursor(Qt::PointingHandCursor);
    vboxIspravaka->addWidget(btnImfVeza);

    m_pageIspravak->setLayout(vboxIspravaka);
    m_tboxDonatMenu->addItem(m_pageIspravak, tr("Ispravak"));
}
void WgDonatMenu1::createNpCps()
{
    m_pageNpCps = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageNpCps->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxNpCps = new QVBoxLayout();
    vboxNpCps->setContentsMargins(1, 1, 1, 1);
    vboxNpCps->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageNpCps->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnZahtjevNp = new QPushButton(tr("Zahtjev - NP"));
    btnZahtjevNp->setFlat(TRUE);
    btnZahtjevNp->setCursor(Qt::PointingHandCursor);
    vboxNpCps->addWidget(btnZahtjevNp);
    QPushButton *btnZahtjevCps = new QPushButton(tr("Zahtjev - CPS"));
    btnZahtjevCps->setFlat(TRUE);
    btnZahtjevCps->setCursor(Qt::PointingHandCursor);
    vboxNpCps->addWidget(btnZahtjevCps);
    QPushButton *btnZahtjevSa = new QPushButton(tr("Zahtjev - SA"));
    btnZahtjevSa->setFlat(TRUE);
    btnZahtjevSa->setCursor(Qt::PointingHandCursor);
    vboxNpCps->addWidget(btnZahtjevSa);
    QPushButton *btnZahtjevVa = new QPushButton(tr("Zahtjev - VA"));
    btnZahtjevVa->setFlat(TRUE);
    btnZahtjevVa->setCursor(Qt::PointingHandCursor);
    vboxNpCps->addWidget(btnZahtjevVa);
    QFrame *hLine = new QFrame();
    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    vboxNpCps->addWidget(hLine);
    QPushButton *btnObavjesti = new QPushButton(tr("Obavjesti"));
    btnObavjesti->setFlat(TRUE);
    btnObavjesti->setCursor(Qt::PointingHandCursor);
    vboxNpCps->addWidget(btnObavjesti);

    m_pageNpCps->setLayout(vboxNpCps);
    m_tboxDonatMenu->addItem(m_pageNpCps, tr("NP - CPS"));
}
void WgDonatMenu1::createVeleprodaja()
{
    m_pageVeleprodaja= new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageVeleprodaja->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxVeleprodaja= new QVBoxLayout();
    vboxVeleprodaja->setContentsMargins(1, 1, 1, 1);
    vboxVeleprodaja->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageVeleprodaja->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnZahtjev = new QPushButton(tr("Zahtjev"));
    btnZahtjev->setFlat(TRUE);
    btnZahtjev->setCursor(Qt::PointingHandCursor);
    vboxVeleprodaja->addWidget(btnZahtjev);

    m_pageVeleprodaja->setLayout(vboxVeleprodaja);
    m_tboxDonatMenu->addItem(m_pageVeleprodaja, tr("VELEPRODAJA"));
}
void WgDonatMenu1::createTrajniNalog()
{
    m_pageTrajniNalog = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageTrajniNalog->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxTrajniNalog = new QVBoxLayout();
    vboxTrajniNalog->setContentsMargins(1, 1, 1, 1);
    vboxTrajniNalog->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageTrajniNalog->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnUgovor = new QPushButton(tr("Ugovor"));
    btnUgovor->setFlat(TRUE);
    btnUgovor->setCursor(Qt::PointingHandCursor);
    vboxTrajniNalog->addWidget(btnUgovor);
    QPushButton *btnUgovorNovi = new QPushButton(tr("Ugovor novi"));
    btnUgovorNovi->setFlat(TRUE);
    btnUgovorNovi->setCursor(Qt::PointingHandCursor);
    vboxTrajniNalog->addWidget(btnUgovorNovi);
    QPushButton *btnPregled = new QPushButton(tr("Pregled"));
    btnPregled->setFlat(TRUE);
    btnPregled->setCursor(Qt::PointingHandCursor);
    btnPregled->setEnabled(FALSE);
    vboxTrajniNalog->addWidget(btnPregled);
    QFrame *hLine = new QFrame();
    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    vboxTrajniNalog->addWidget(hLine);
    QPushButton *btnPlacanje = new QPushButton(tr("Plaćanje"));
    btnPlacanje->setFlat(TRUE);
    btnPlacanje->setCursor(Qt::PointingHandCursor);
    vboxTrajniNalog->addWidget(btnPlacanje);

    m_pageTrajniNalog->setLayout(vboxTrajniNalog);
    m_tboxDonatMenu->addItem(m_pageTrajniNalog, tr("Trajni nalog"));
}
void WgDonatMenu1::createListeInteresa()
{
    m_pageListeInteresa = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageListeInteresa->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxListeInteresa = new QVBoxLayout();
    vboxListeInteresa->setContentsMargins(1, 1, 1, 1);
    vboxListeInteresa->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageListeInteresa->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnStaviNaAdslListu = new QPushButton(tr("Stavi na ADSL listu"));
    btnStaviNaAdslListu->setFlat(TRUE);
    btnStaviNaAdslListu->setCursor(Qt::PointingHandCursor);
    vboxListeInteresa->addWidget(btnStaviNaAdslListu);
    QPushButton *btnStaviNaMaxtvListu = new QPushButton(tr("Stavi na MaxTV listu"));
    btnStaviNaMaxtvListu->setFlat(TRUE);
    btnStaviNaMaxtvListu->setCursor(Qt::PointingHandCursor);
    vboxListeInteresa->addWidget(btnStaviNaMaxtvListu);
    QFrame *hLine = new QFrame();
    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    vboxListeInteresa->addWidget(hLine);
    QPushButton *btnPregled = new QPushButton(tr("Pregled"));
    btnPregled->setFlat(TRUE);
    btnPregled->setCursor(Qt::PointingHandCursor);
    vboxListeInteresa->addWidget(btnPregled);

    m_pageListeInteresa->setLayout(vboxListeInteresa);
    m_tboxDonatMenu->addItem(m_pageListeInteresa, tr("Liste interesa"));
}
void WgDonatMenu1::createOtpustDuga()
{
    m_pageOtpustDuga = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageOtpustDuga->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxOtpustDuga = new QVBoxLayout();
    vboxOtpustDuga->setContentsMargins(1, 1, 1, 1);
    vboxOtpustDuga->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageOtpustDuga->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnZahtjev = new QPushButton(tr("Zahtjev"));
    btnZahtjev->setFlat(TRUE);
    btnZahtjev->setCursor(Qt::PointingHandCursor);
    vboxOtpustDuga->addWidget(btnZahtjev);

    m_pageOtpustDuga->setLayout(vboxOtpustDuga);
    m_tboxDonatMenu->addItem(m_pageOtpustDuga, tr("Otpust duga"));
}
void WgDonatMenu1::createCuba()
{
    m_pageCuba = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageCuba->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxCuba = new QVBoxLayout();
    vboxCuba->setContentsMargins(1, 1, 1, 1);
    vboxCuba->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageCuba->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnCuba = new QPushButton(tr("CuBA"));
    btnCuba->setFlat(TRUE);
    btnCuba->setCursor(Qt::PointingHandCursor);
    vboxCuba->addWidget(btnCuba);
    QPushButton *btnPregled = new QPushButton(tr("Pregled"));
    btnPregled->setFlat(TRUE);
    btnPregled->setCursor(Qt::PointingHandCursor);
    vboxCuba->addWidget(btnPregled);
    QFrame *hLine = new QFrame();
    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    vboxCuba->addWidget(hLine);
    QPushButton *btnMojiZastupnici = new QPushButton(tr("Moji zastupnici"));
    btnMojiZastupnici->setFlat(TRUE);
    btnMojiZastupnici->setCursor(Qt::PointingHandCursor);
    vboxCuba->addWidget(btnMojiZastupnici);
    QPushButton *btnFirmeZastupnik = new QPushButton(tr("Firme zastupnik"));
    btnFirmeZastupnik->setFlat(TRUE);
    btnFirmeZastupnik->setCursor(Qt::PointingHandCursor);
    vboxCuba->addWidget(btnFirmeZastupnik);
    QPushButton *btnAzurirajKupca = new QPushButton(tr("Ažuriraj kupca"));
    btnAzurirajKupca->setFlat(TRUE);
    btnAzurirajKupca->setCursor(Qt::PointingHandCursor);
    vboxCuba->addWidget(btnAzurirajKupca);

    m_pageCuba->setLayout(vboxCuba);
    m_tboxDonatMenu->addItem(m_pageCuba, tr("CuBa"));
}
void WgDonatMenu1::createTpartneri()
{
    m_pageTpartneri = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageTpartneri->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxTpartneri = new QVBoxLayout();
    vboxTpartneri->setContentsMargins(1, 1, 1, 1);
    vboxTpartneri->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageTpartneri->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnMojiPartneri = new QPushButton(tr("MOJI PARTNERI"));
    btnMojiPartneri->setFlat(TRUE);
    btnMojiPartneri->setCursor(Qt::PointingHandCursor);
    vboxTpartneri->addWidget(btnMojiPartneri);

    m_pageTpartneri->setLayout(vboxTpartneri);
    m_tboxDonatMenu->addItem(m_pageTpartneri, tr("T-partneri"));
}
void WgDonatMenu1::createPrigovori()
{
    m_pagePrigovori = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pagePrigovori->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxPrigovori = new QVBoxLayout();
    vboxPrigovori->setContentsMargins(1, 1, 1, 1);
    vboxPrigovori->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pagePrigovori->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnPrigovor = new QPushButton(tr("Prigovor"));
    btnPrigovor->setFlat(TRUE);
    btnPrigovor->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnPrigovor);
    QFrame *hLine1 = new QFrame();
    hLine1->setFrameShape(QFrame::HLine);
    hLine1->setFrameShadow(QFrame::Sunken);
    vboxPrigovori->addWidget(hLine1);
    QPushButton *btnPregled = new QPushButton(tr("Pregled"));
    btnPregled->setFlat(TRUE);
    btnPregled->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnPregled);
    QPushButton *btnOdobrenje = new QPushButton(tr("Odobrenje"));
    btnOdobrenje->setFlat(TRUE);
    btnOdobrenje->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnOdobrenje);
    QPushButton *btnExcellOut = new QPushButton(tr("Excel OUT"));
    btnExcellOut->setFlat(TRUE);
    btnExcellOut->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnExcellOut);
    QPushButton *btnExcellIn = new QPushButton(tr("Excel IN"));
    btnExcellIn->setFlat(TRUE);
    btnExcellIn->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnExcellIn);
    QPushButton *btnPismo = new QPushButton(tr("Pismo"));
    btnPismo->setFlat(TRUE);
    btnPismo->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnPismo);
    QFrame *hLine2 = new QFrame();
    hLine2->setFrameShape(QFrame::HLine);
    hLine2->setFrameShadow(QFrame::Sunken);
    vboxPrigovori->addWidget(hLine2);
    QPushButton *btnEmailIn = new QPushButton(tr("Email IN"));
    btnEmailIn->setFlat(TRUE);
    btnEmailIn->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnEmailIn);
    QPushButton *btnEmailOk = new QPushButton(tr("Email OK"));
    btnEmailOk->setFlat(TRUE);
    btnEmailOk->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnEmailOk);
    QFrame *hLine3 = new QFrame();
    hLine3->setFrameShape(QFrame::HLine);
    hLine3->setFrameShadow(QFrame::Sunken);
    vboxPrigovori->addWidget(hLine3);
    QPushButton *btnDjelatniciOd = new QPushButton(tr("Djelatnici OD"));
    btnDjelatniciOd->setFlat(TRUE);
    btnDjelatniciOd->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnDjelatniciOd);
    QPushButton *btnPredlosci = new QPushButton(tr("Predlošci"));
    btnPredlosci->setFlat(TRUE);
    btnPredlosci->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnPredlosci);
    QPushButton *btnExcellOutS = new QPushButton(tr("Excel OUT - S"));
    btnExcellOutS->setFlat(TRUE);
    btnExcellOutS->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnExcellOutS);
    QPushButton *btnExcellInS = new QPushButton(tr("Excel IN - S"));
    btnExcellInS->setFlat(TRUE);
    btnExcellInS->setCursor(Qt::PointingHandCursor);
    vboxPrigovori->addWidget(btnExcellInS);

    m_pagePrigovori->setLayout(vboxPrigovori);
    m_tboxDonatMenu->addItem(m_pagePrigovori, tr("Prigovori"));
}
void WgDonatMenu1::createDataUsluge()
{
    m_pageDataUsluge = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageDataUsluge->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxDataUsluge = new QVBoxLayout();
    vboxDataUsluge->setContentsMargins(1, 1, 1, 1);
    vboxDataUsluge->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageDataUsluge->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnZahtjev = new QPushButton(tr("Zahtjev"));
    btnZahtjev->setFlat(TRUE);
    btnZahtjev->setCursor(Qt::PointingHandCursor);
    vboxDataUsluge->addWidget(btnZahtjev);
    QPushButton *btnPRegled = new QPushButton(tr("Pregled"));
    btnPRegled->setFlat(TRUE);
    btnPRegled->setCursor(Qt::PointingHandCursor);
    vboxDataUsluge->addWidget(btnPRegled);

    m_pageDataUsluge->setLayout(vboxDataUsluge);
    m_tboxDonatMenu->addItem(m_pageDataUsluge, tr("DATA usluge"));
}
void WgDonatMenu1::createUgovoriPopusta()
{
    m_pageUgovoriPopusta = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageUgovoriPopusta->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxUgovoriPopusta = new QVBoxLayout();
    vboxUgovoriPopusta->setContentsMargins(1, 1, 1, 1);
    vboxUgovoriPopusta->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageUgovoriPopusta->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnFirme = new QPushButton(tr("Firme"));
    btnFirme->setFlat(TRUE);
    btnFirme->setCursor(Qt::PointingHandCursor);
    vboxUgovoriPopusta->addWidget(btnFirme);
    QPushButton *btnUgovori = new QPushButton(tr("Ugovori"));
    btnUgovori->setFlat(TRUE);
    btnUgovori->setCursor(Qt::PointingHandCursor);
    vboxUgovoriPopusta->addWidget(btnUgovori);

    m_pageUgovoriPopusta->setLayout(vboxUgovoriPopusta);
    m_tboxDonatMenu->addItem(m_pageUgovoriPopusta, tr("Ugovori popusta"));
}
void WgDonatMenu1::createSla()
{
    m_pageSla = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageSla->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxSla = new QVBoxLayout();
    vboxSla->setContentsMargins(1, 1, 1, 1);
    vboxSla->setSpacing(1);

    QPushButton *btnPrijavaSlaSmetnji = new QPushButton(tr("Prijava SLA smetnji"));
    btnPrijavaSlaSmetnji->setFlat(TRUE);
    btnPrijavaSlaSmetnji->setCursor(Qt::PointingHandCursor);
    vboxSla->addWidget(btnPrijavaSlaSmetnji);
    QPushButton *btnKorekcijaPregled = new QPushButton(tr("Korekcija i pregled"));
    btnKorekcijaPregled->setFlat(TRUE);
    btnKorekcijaPregled->setCursor(Qt::PointingHandCursor);
    vboxSla->addWidget(btnKorekcijaPregled);
    QPushButton *btnPregledSmetnji = new QPushButton(tr("Pregled smetnji"));
    btnPregledSmetnji->setFlat(TRUE);
    btnPregledSmetnji->setCursor(Qt::PointingHandCursor);
    vboxSla->addWidget(btnPregledSmetnji);
    QPushButton *btnOpciSlaPregledi = new QPushButton(tr("Opći SLA pregledi"));
    btnOpciSlaPregledi->setFlat(TRUE);
    btnOpciSlaPregledi->setCursor(Qt::PointingHandCursor);
    vboxSla->addWidget(btnOpciSlaPregledi);

    m_pageSla->setLayout(vboxSla);
    m_tboxDonatMenu->addItem(m_pageSla, tr("SLA"));
}
void WgDonatMenu1::createTehnickiProcesi()
{
    m_pageTehnickiProcesi = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageTehnickiProcesi->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxTehnickiProcesi = new QVBoxLayout();
    vboxTehnickiProcesi->setContentsMargins(1, 1, 1, 1);
    vboxTehnickiProcesi->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageTehnickiProcesi->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnProcesi = new QPushButton(tr("Procesi"));
    btnProcesi->setFlat(TRUE);
    btnProcesi->setCursor(Qt::PointingHandCursor);
    vboxTehnickiProcesi->addWidget(btnProcesi);

    m_pageTehnickiProcesi->setLayout(vboxTehnickiProcesi);
    m_tboxDonatMenu->addItem(m_pageTehnickiProcesi, tr("Tehnički procesi"));
}
void WgDonatMenu1::createTaskManagement()
{
    m_pageTaskManagement = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageTaskManagement->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxTaskManagement = new QVBoxLayout();
    vboxTaskManagement->setContentsMargins(1, 1, 1, 1);
    vboxTaskManagement->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageTaskManagement->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnNoviZadatak = new QPushButton(tr("Novi zadatak"));
    btnNoviZadatak->setFlat(TRUE);
    btnNoviZadatak->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnNoviZadatak);
    QPushButton *btnListeZadataka = new QPushButton(tr("Liste zadataka"));
    btnListeZadataka->setFlat(TRUE);
    btnListeZadataka->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnListeZadataka);
    QPushButton *btnGrupe = new QPushButton(tr("Grupe"));
    btnGrupe->setFlat(TRUE);
    btnGrupe->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnGrupe);
    QPushButton *btnDjelatniciGrupe = new QPushButton(tr("Djelatnici/Grupe"));
    btnDjelatniciGrupe->setFlat(TRUE);
    btnDjelatniciGrupe->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnDjelatniciGrupe);
    QPushButton *btnSupervizori = new QPushButton(tr("Supervizori"));
    btnSupervizori->setFlat(TRUE);
    btnSupervizori->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnSupervizori);
    QPushButton *btnGrupeZadataka = new QPushButton(tr("Grupe zadataka"));
    btnGrupeZadataka->setFlat(TRUE);
    btnGrupeZadataka->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnGrupeZadataka);
    QPushButton *btnTipoviZadataka = new QPushButton(tr("Tipovi zadataka"));
    btnTipoviZadataka->setFlat(TRUE);
    btnTipoviZadataka->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnTipoviZadataka);
    QPushButton *btnZadaciGrupeZadataka = new QPushButton(tr("Zadaci/Grupe zadataka"));
    btnZadaciGrupeZadataka->setFlat(TRUE);
    btnZadaciGrupeZadataka->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnZadaciGrupeZadataka);
    QPushButton *btnTipoviVjestina = new QPushButton(tr("Tipovi vještina"));
    btnTipoviVjestina->setFlat(TRUE);
    btnTipoviVjestina->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnTipoviVjestina);
    QPushButton *btnTipoviDelegiranja = new QPushButton(tr("Tipovi delegiranja"));
    btnTipoviDelegiranja->setFlat(TRUE);
    btnTipoviDelegiranja->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnTipoviDelegiranja);
    QPushButton *btnRezultatiZadataka = new QPushButton(tr("Rezultati zadataka"));
    btnRezultatiZadataka->setFlat(TRUE);
    btnRezultatiZadataka->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnRezultatiZadataka);
    QPushButton *btnRealTimeNadzor = new QPushButton(tr("Real time nadzor"));
    btnRealTimeNadzor->setFlat(TRUE);
    btnRealTimeNadzor->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnRealTimeNadzor);
    QPushButton *btnSektoriGrupa = new QPushButton(tr("Sektori grupa"));
    btnSektoriGrupa->setFlat(TRUE);
    btnSektoriGrupa->setCursor(Qt::PointingHandCursor);
    vboxTaskManagement->addWidget(btnSektoriGrupa);

    m_pageTaskManagement->setLayout(vboxTaskManagement);
    m_tboxDonatMenu->addItem(m_pageTaskManagement, tr("Task management"));
}
void WgDonatMenu1::createZlonamjerniPozivi()
{
    m_pageZlonamjerniPozivi = new QWidget();
    QSizePolicy pageSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageSizePolicy.setHorizontalStretch(0);
    pageSizePolicy.setVerticalStretch(0);
    m_pageZlonamjerniPozivi->setSizePolicy(pageSizePolicy);
    QVBoxLayout *vboxZlonamjerniPozivi = new QVBoxLayout();
    vboxZlonamjerniPozivi->setContentsMargins(1, 1, 1, 1);
    vboxZlonamjerniPozivi->setSpacing(1);
//    QSizePolicy pagePageSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//    pagePageSizePolicy.setHorizontalStretch(0);
//    pagePageSizePolicy.setVerticalStretch(0);
//    m_pageZlonamjerniPozivi->setSizePolicy(pagePageSizePolicy);

    QPushButton *btnPregled = new QPushButton(tr("Pregled"));
    btnPregled->setFlat(TRUE);
    btnPregled->setCursor(Qt::PointingHandCursor);
    vboxZlonamjerniPozivi->addWidget(btnPregled);

    m_pageZlonamjerniPozivi->setLayout(vboxZlonamjerniPozivi);
    m_tboxDonatMenu->addItem(m_pageZlonamjerniPozivi, tr("Zlonamjerni pozivi"));
}

void WgDonatMenu1::createMainImage()
{
    m_imgMainMenuImage = new QLabel();
    m_imgMainMenuImage->setPixmap(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/Tcom1.png")));
    m_imgMainMenuImage->setFrameShape(QFrame::StyledPanel);
    m_vboxDonatMenu->addWidget(m_imgMainMenuImage);
}

// Create Donat main form actions
void WgDonatMenu1::createMainActions()
{

}

WgDonatMenu1::~WgDonatMenu1()
{
    m_imgMainMenuImage->clear();
}

}   // namespace log
