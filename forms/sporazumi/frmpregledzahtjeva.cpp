/************************************* Module Header **************************************\
* Module Name:  frmpregledzahtjeva.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT pregled zahtjeva form
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

#include "frmpregledzahtjeva.h"
#include "itos.h"
#include "ocinumber.h"
#include "frmstavkesporazuma.h"
#include "frmpregledprocesa.h"
#include "frmwwmspregled.h"
#include "frmdonatpregled.h"
#include "frmpregledsporazuma.h"
#include "frmpregledimovine.h"

namespace Sporazumi {

FrmPregledZahtjeva::FrmPregledZahtjeva(int iTipDokumentaId, unsigned int iStrankaId, QWidget *parent) :
    QMainWindow(parent)
{
    // [0]
    m_fraMainFrame = new QFrame();
    m_fraMainFrame->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *m_hboxMainLayout = new QHBoxLayout();
    m_hboxMainLayout->setContentsMargins(2, 4, 2, 4);
    m_hboxMainLayout->setSpacing(1);

    // [1]
    m_fraFltFrame = new QFrame();
    m_fraFltFrame->setContentsMargins(0, 0, 0, 0);
    createFltFrame();

    // [1]
    m_fraResultsFrame = new QFrame();
    m_fraResultsFrame->setContentsMargins(0, 0, 0, 0);
    createResultFrame();

    m_hboxMainLayout->addWidget(m_fraFltFrame);
    m_hboxMainLayout->addWidget(m_fraResultsFrame);

    m_fraMainFrame->setLayout(m_hboxMainLayout);

    setCentralWidget(m_fraMainFrame);

    createFormActions();
    createFormMenus();
    createFormToolBars();
    createFormStatusBar();

    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    if(iTipDokumentaId == 1)
    {
        setWindowTitle(tr("DONAT - Pregled Zahtjeva"));
    }
    else if(iTipDokumentaId == 3)
    {
        setWindowTitle(tr("DONAT - Pregled Ugovora"));
    }
    // Set minimum form size
    setMinimumSize(1124, 698);
    m_btnZatvori->setFocus();
    m_btnZatvori->setAutoDefault(TRUE);
    m_dtDatum->setDate(QDate::currentDate());

    m_iStrankaId = iStrankaId;
    m_iUlogaStrankeId = 0;
    m_iTipUlogaStrankeId = 0;
    m_iTipDokumenta = iTipDokumentaId;

    m_iSporazumId = 0;

    popuniSveKlase();
    popuniKanalProdaje();
    popuniZahtjeve();
}

void FrmPregledZahtjeva::createFltFrame()
{
    QVBoxLayout *vboxFltFrameLayout = new QVBoxLayout();
    vboxFltFrameLayout->setContentsMargins(0, 0, 0, 0);
    vboxFltFrameLayout->setSpacing(0);
    vboxFltFrameLayout->setAlignment(Qt::AlignTop);

    // [0]
    QFrame *fraTipKupcaTitle = new QFrame();
    fraTipKupcaTitle->setContentsMargins(0, 0, 0, 0);
    fraTipKupcaTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraTipKupcaTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraTipKupcaTitleSizePolicy.setHorizontalStretch(0);
    fraTipKupcaTitleSizePolicy.setVerticalStretch(0);
    fraTipKupcaTitle->setSizePolicy(fraTipKupcaTitleSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(0, 2, 0, 2);
    hboxLayout1->setSpacing(1);
    QLabel *lblTipStrankeTitle = new QLabel(tr("Tip kupca"));
    hboxLayout1->addWidget(lblTipStrankeTitle);
    QPushButton *btnExpandFrame1 = new QPushButton();
    btnExpandFrame1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame1->setCursor(Qt::PointingHandCursor);
    btnExpandFrame1->setFlat(true);
    QSizePolicy btnExpandFrame1SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame1SizePolicy.setHorizontalStretch(0);
    btnExpandFrame1SizePolicy.setVerticalStretch(0);
    btnExpandFrame1->setSizePolicy(btnExpandFrame1SizePolicy);
    hboxLayout1->addWidget(btnExpandFrame1);
    fraTipKupcaTitle->setLayout(hboxLayout1);
    vboxFltFrameLayout->addWidget(fraTipKupcaTitle);

    // [1]
    QFrame *fraTipKupcaFlt = new QFrame();
    fraTipKupcaFlt->setContentsMargins(0, 0, 0, 0);
    fraTipKupcaFlt->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraTipKupcaFltSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraTipKupcaFltSizePolicy.setHorizontalStretch(0);
    fraTipKupcaFltSizePolicy.setVerticalStretch(0);
    fraTipKupcaFlt->setSizePolicy(fraTipKupcaFltSizePolicy);
    QVBoxLayout *vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setContentsMargins(0, 2, 0, 2);
    vboxLayout2->setSpacing(1);
    m_btnPrivatni = new QPushButton(tr("Privatni"));
    m_btnPrivatni->setFlat(true);
    m_btnPrivatni->setCursor(Qt::PointingHandCursor);
    vboxLayout2->addWidget(m_btnPrivatni);
    m_btnKljucni = new QPushButton(tr("Ključni"));
    m_btnKljucni->setFlat(true);
    m_btnKljucni->setCursor(Qt::PointingHandCursor);
    vboxLayout2->addWidget(m_btnKljucni);
    m_btnPoslovni = new QPushButton(tr("Poslovni"));
    m_btnPoslovni->setFlat(true);
    m_btnPoslovni->setCursor(Qt::PointingHandCursor);
    vboxLayout2->addWidget(m_btnPoslovni);
    QFrame *fraLine1 = new QFrame();
    fraLine1->setContentsMargins(2, 2, 2, 2);
    fraLine1->setFrameShape(QFrame::StyledPanel);
    fraLine1->setFrameShadow(QFrame::Sunken);
    fraLine1->setMinimumHeight(5);
    QSizePolicy fraLine1SizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraLine1SizePolicy.setHorizontalStretch(0);
    fraLine1SizePolicy.setVerticalStretch(0);
    fraLine1->setSizePolicy(fraLine1SizePolicy);
    vboxLayout2->addWidget(fraLine1);
    QFrame *fraZaDatumFlt = new QFrame();
    fraZaDatumFlt->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayoutZaDatum = new QHBoxLayout();
    hboxLayoutZaDatum->setContentsMargins(0, 2, 0, 2);
    hboxLayoutZaDatum->setSpacing(0);
    QLabel *lblZaDatumTitle = new QLabel(tr("Za datum :"));
    hboxLayoutZaDatum->addWidget(lblZaDatumTitle);
    m_dtDatum = new QDateTimeEdit();
    m_dtDatum->setDisplayFormat(tr("dd. MM. yyyy"));
    hboxLayoutZaDatum->addWidget(m_dtDatum);
    fraZaDatumFlt->setLayout(hboxLayoutZaDatum);
    vboxLayout2->addWidget(fraZaDatumFlt);
    fraTipKupcaFlt->setLayout(vboxLayout2);
    vboxFltFrameLayout->addWidget(fraTipKupcaFlt);

    // [3]
    QFrame *fraPriodTitle = new QFrame();
    fraPriodTitle->setContentsMargins(0, 0, 0, 0);
    fraPriodTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraPriodTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraPriodTitleSizePolicy.setHorizontalStretch(0);
    fraPriodTitleSizePolicy.setVerticalStretch(0);
    fraPriodTitle->setSizePolicy(fraPriodTitleSizePolicy);
    QHBoxLayout *hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setContentsMargins(0, 2, 0, 2);
    hboxLayout3->setSpacing(1);
    QLabel *lblPeriodTitle = new QLabel(tr("Period"));
    hboxLayout3->addWidget(lblPeriodTitle);
    QPushButton *btnExpandFrame2 = new QPushButton();
    btnExpandFrame2->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame2->setFlat(true);
    btnExpandFrame2->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame2SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame2SizePolicy.setHorizontalStretch(0);
    btnExpandFrame2SizePolicy.setVerticalStretch(0);
    btnExpandFrame2->setSizePolicy(btnExpandFrame2SizePolicy);
    hboxLayout3->addWidget(btnExpandFrame2);
    fraPriodTitle->setLayout(hboxLayout3);
    vboxFltFrameLayout->addWidget(fraPriodTitle);

    // [4]
    QFrame *fraPeriodFlt = new QFrame();
    fraPeriodFlt->setContentsMargins(0, 0, 0, 0);
    fraPeriodFlt->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraPeriodFltSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraPeriodFltSizePolicy.setHorizontalStretch(0);
    fraPeriodFltSizePolicy.setVerticalStretch(0);
    fraPeriodFlt->setSizePolicy(fraPeriodFltSizePolicy);
    QVBoxLayout *vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setContentsMargins(0, 2, 0, 2);
    vboxLayout4->setSpacing(1);
    m_btnDanas = new QPushButton(tr("Danas"));
    m_btnDanas->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDanas->setFlat(true);
    m_btnDanas->setCursor(Qt::PointingHandCursor);
    vboxLayout4->addWidget(m_btnDanas);
    m_btnOvajTjedan = new QPushButton(tr("Ovaj tjedan"));
    m_btnOvajTjedan->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnOvajTjedan->setFlat(true);
    m_btnOvajTjedan->setCursor(Qt::PointingHandCursor);
    vboxLayout4->addWidget(m_btnOvajTjedan);
    m_btnOvajMjesec = new QPushButton(tr("Ovaj mjesec"));
    m_btnOvajMjesec->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnOvajMjesec->setFlat(true);
    m_btnOvajMjesec->setCursor(Qt::PointingHandCursor);
    vboxLayout4->addWidget(m_btnOvajMjesec);
    fraPeriodFlt->setLayout(vboxLayout4);
    vboxFltFrameLayout->addWidget(fraPeriodFlt);

    // [5]
    QFrame *fraStatusTitle = new QFrame();
    fraStatusTitle->setContentsMargins(0, 0, 0, 0);
    fraStatusTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraStatusTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraStatusTitleSizePolicy.setHorizontalStretch(0);
    fraStatusTitleSizePolicy.setVerticalStretch(0);
    fraStatusTitle->setSizePolicy(fraStatusTitleSizePolicy);
    QHBoxLayout *hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setContentsMargins(0, 2, 0, 2);
    hboxLayout5->setSpacing(1);
    QLabel *lblStatusTitle = new QLabel(tr("Status"));
    hboxLayout5->addWidget(lblStatusTitle);
    QPushButton *btnExpandFrame5 = new QPushButton();
    btnExpandFrame5->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame5->setFlat(true);
    btnExpandFrame5->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame5SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame5SizePolicy.setHorizontalStretch(0);
    btnExpandFrame5SizePolicy.setVerticalStretch(0);
    btnExpandFrame5->setSizePolicy(btnExpandFrame5SizePolicy);
    hboxLayout5->addWidget(btnExpandFrame5);
    fraStatusTitle->setLayout(hboxLayout5);
    vboxFltFrameLayout->addWidget(fraStatusTitle);

    // [6]
    QFrame *fraStatusFlt = new QFrame();
    fraStatusFlt->setContentsMargins(0, 0, 0, 0);
    fraStatusFlt->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraStatusFltSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraStatusFltSizePolicy.setHorizontalStretch(0);
    fraStatusFltSizePolicy.setVerticalStretch(0);
    fraStatusFlt->setSizePolicy(fraStatusFltSizePolicy);
    QVBoxLayout *vboxLayout6 = new QVBoxLayout();
    vboxLayout6->setContentsMargins(0, 2, 0, 2);
    vboxLayout6->setSpacing(1);
    m_btnSvi = new QPushButton(tr("Svi"));
    m_btnSvi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnSvi->setFlat(true);
    m_btnSvi->setCursor(Qt::PointingHandCursor);
    vboxLayout6->addWidget(m_btnSvi);
    m_btnUtijeku = new QPushButton(tr("U tijeku"));
    m_btnUtijeku->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnUtijeku->setFlat(true);
    m_btnUtijeku->setCursor(Qt::PointingHandCursor);
    vboxLayout6->addWidget(m_btnUtijeku);
    m_btnRezerviran = new QPushButton(tr("Rezerviran"));
    m_btnRezerviran->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnRezerviran->setFlat(true);
    m_btnRezerviran->setCursor(Qt::PointingHandCursor);
    vboxLayout6->addWidget(m_btnRezerviran);
    m_btnStorniran = new QPushButton(tr("Storniran"));
    m_btnStorniran->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStorniran->setFlat(true);
    m_btnStorniran->setCursor(Qt::PointingHandCursor);
    vboxLayout6->addWidget(m_btnStorniran);
    QFrame *fraLine2 = new QFrame();
    fraLine2->setContentsMargins(2, 2, 2, 2);
    fraLine2->setFrameShape(QFrame::StyledPanel);
    fraLine2->setFrameShadow(QFrame::Sunken);
    fraLine2->setMinimumHeight(5);
    QSizePolicy fraLine2SizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraLine2SizePolicy.setHorizontalStretch(0);
    fraLine2SizePolicy.setVerticalStretch(0);
    fraLine2->setSizePolicy(fraLine2SizePolicy);
    vboxLayout6->addWidget(fraLine2);
    m_btnValidacija = new QPushButton(tr("Validacija"));
    m_btnValidacija->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnValidacija->setFlat(true);
    m_btnValidacija->setCursor(Qt::PointingHandCursor);
    vboxLayout6->addWidget(m_btnValidacija);
    m_btnPojedinacno = new QPushButton(tr("Pojedinačno"));
    m_btnPojedinacno->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnPojedinacno->setFlat(true);
    m_btnPojedinacno->setCursor(Qt::PointingHandCursor);
    m_btnPojedinacno->setVisible(false);
    vboxLayout6->addWidget(m_btnPojedinacno);
    fraStatusFlt->setLayout(vboxLayout6);
    vboxFltFrameLayout->addWidget(fraStatusFlt);

    // [7]
    QFrame *fraSporazumTitle = new QFrame();
    fraSporazumTitle->setContentsMargins(0, 0, 0, 0);
    fraSporazumTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraSporazumTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraSporazumTitleSizePolicy.setHorizontalStretch(0);
    fraSporazumTitleSizePolicy.setVerticalStretch(0);
    fraSporazumTitle->setSizePolicy(fraSporazumTitleSizePolicy);
    QHBoxLayout *hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setContentsMargins(0, 2, 0, 2);
    hboxLayout7->setSpacing(1);
    QLabel *lblSporazumTitle = new QLabel(tr("Sporazum"));
    hboxLayout7->addWidget(lblSporazumTitle);
    QPushButton *btnExpandFrame7 = new QPushButton();
    btnExpandFrame7->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame7->setFlat(true);
    btnExpandFrame7->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame7SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame7SizePolicy.setHorizontalStretch(0);
    btnExpandFrame7SizePolicy.setVerticalStretch(0);
    btnExpandFrame7->setSizePolicy(btnExpandFrame7SizePolicy);
    hboxLayout7->addWidget(btnExpandFrame7);
    fraSporazumTitle->setLayout(hboxLayout7);
    vboxFltFrameLayout->addWidget(fraSporazumTitle);

    // [8]
    QFrame *fraSporazumToolBar = new QFrame();
    fraSporazumToolBar->setContentsMargins(0, 0, 0, 0);
    fraSporazumToolBar->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraSporazumToolBarSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraSporazumToolBarSizePolicy.setHorizontalStretch(0);
    fraSporazumToolBarSizePolicy.setVerticalStretch(0);
    fraSporazumToolBar->setSizePolicy(fraSporazumToolBarSizePolicy);
    QVBoxLayout *vboxLayout8 = new QVBoxLayout();
    vboxLayout8->setContentsMargins(0, 2, 0, 2);
    vboxLayout8->setSpacing(1);
    m_btnStorno = new QPushButton(tr("S T O R N O"));
    m_btnStorno->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
    m_btnStorno->setFlat(true);
    m_btnStorno->setCursor(Qt::PointingHandCursor);
    vboxLayout8->addWidget(m_btnStorno);
    m_btnStornoDonat = new QPushButton(tr("STORNO ( DONAT )"));
    m_btnStornoDonat->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
    m_btnStornoDonat->setFlat(true);
    m_btnStornoDonat->setEnabled(false);
    m_btnStornoDonat->setCursor(Qt::PointingHandCursor);
    vboxLayout8->addWidget(m_btnStornoDonat);
    m_btnNastavakRealizacije = new QPushButton(tr("NASTAVAK REALIZACIJE"));
    m_btnNastavakRealizacije->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OLOVKA.GIF")));
    m_btnNastavakRealizacije->setFlat(true);
    m_btnNastavakRealizacije->setCursor(Qt::PointingHandCursor);
    vboxLayout8->addWidget(m_btnNastavakRealizacije);
    m_btnPretvoriU1Kunu = new QPushButton(tr("PRETVORI u 1 kn"));
    m_btnPretvoriU1Kunu->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ZAMJENA.gif")));
    m_btnPretvoriU1Kunu->setFlat(true);
    m_btnPretvoriU1Kunu->setCursor(Qt::PointingHandCursor);
    vboxLayout8->addWidget(m_btnPretvoriU1Kunu);
    fraSporazumToolBar->setLayout(vboxLayout8);
    vboxFltFrameLayout->addWidget(fraSporazumToolBar);

    m_fraFltFrame->setLayout(vboxFltFrameLayout);
}

void FrmPregledZahtjeva::createResultFrame()
{
    QVBoxLayout *vboxResultFrameLayout = new QVBoxLayout();
    vboxResultFrameLayout->setContentsMargins(0, 0, 0, 0);
    vboxResultFrameLayout->setSpacing(0);
    vboxResultFrameLayout->setAlignment(Qt::AlignTop);

    // [0]
    QFrame *fraMojiDokumentiTitle = new QFrame();
    fraMojiDokumentiTitle->setContentsMargins(0, 0, 0, 0);
    fraMojiDokumentiTitle->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(0, 2, 0, 2);
    hboxLayout1->setSpacing(1);
    m_cboKlase = new QComboBox();
    m_cboKlase->addItem(tr("Klasa"), QVariant(tr("Sve klase")));
    hboxLayout1->addWidget(m_cboKlase);
    m_lblMojeKlase = new QLabel(tr("Sve klase"));
    hboxLayout1->addWidget(m_lblMojeKlase);
    m_lblMojiDokumenti = new QLabel(tr("Moji dokumenti"));
    hboxLayout1->addWidget(m_lblMojiDokumenti);
    fraMojiDokumentiTitle->setLayout(hboxLayout1);
    vboxResultFrameLayout->addWidget(fraMojiDokumentiTitle);

    // [1]
    QFrame *fraMojiDokumenti = new QFrame();
    fraMojiDokumenti->setContentsMargins(0, 0, 0, 0);
//    fraMojiDokumenti->setFrameShape(QFrame::StyledPanel);
//    QSizePolicy fraMojiDokumentieSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//    fraMojiDokumentieSizePolicy.setHorizontalStretch(0);
//    fraMojiDokumentieSizePolicy.setVerticalStretch(0);
//    fraMojiDokumenti->setSizePolicy(fraMojiDokumentieSizePolicy);
    QHBoxLayout *hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setContentsMargins(0, 2, 0, 2);
    hboxLayout2->setSpacing(1);
    m_grdZahtjevi = new QTableWidget();
    m_grdZahtjevi->setContentsMargins(4, 4, 0, 0);
    m_grdZahtjevi->setFrameShape(QFrame::StyledPanel);
    m_grdZahtjevi->setMinimumWidth(680);
    // Create headers
    QStringList labels;
    labels << "RB" << "DATUM" << "BROJ" << "KUPAC" << "JOP"
           << "StatusId" << "SporazumId" << "Ugovor Ind" << "Tip Sporazuma Id" << "Kupac Id";
    m_grdZahtjevi->setColumnCount(10);
    m_grdZahtjevi->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_grdZahtjevi->setHorizontalHeaderLabels(labels);
    m_grdZahtjevi->horizontalHeader()->setStretchLastSection(false);
    m_grdZahtjevi->setColumnWidth(0, 25);
    m_grdZahtjevi->setColumnWidth(1, 80);
    m_grdZahtjevi->setColumnWidth(2, 100);
    m_grdZahtjevi->setColumnWidth(3, 400);
    m_grdZahtjevi->setColumnWidth(4, 70);
    m_grdZahtjevi->setColumnWidth(5, 0);
    m_grdZahtjevi->setColumnWidth(6, 5);
    m_grdZahtjevi->setColumnWidth(7, 0);
    m_grdZahtjevi->setColumnWidth(8, 0);
    m_grdZahtjevi->setColumnWidth(9, 0);
//    m_grdZahtjevi->hideColumn(0);
//    m_grdZahtjevi->hideColumn(3);
//    m_grdZahtjevi->hideColumn(5);
    m_grdZahtjevi->verticalHeader()->hide();
//    m_grdZahtjevi->horizontalHeader()->hide();
    m_grdZahtjevi->setAlternatingRowColors(TRUE);
    m_grdZahtjevi->setShowGrid(true);
    m_grdZahtjevi->setSelectionMode(QAbstractItemView::SingleSelection);
    m_grdZahtjevi->setSelectionBehavior(QAbstractItemView::SelectRows);
    hboxLayout2->addWidget(m_grdZahtjevi);
    m_fraZahtjevToolBox = new QFrame();
    m_fraZahtjevToolBox->setContentsMargins(0, 0, 0, 0);
//    m_fraZahtjevToolBox->setFrameShape(QFrame::StyledPanel);
    m_fraZahtjevToolBox->setMaximumWidth(190);
    m_fraZahtjevToolBox->setMinimumWidth(190);
    createZahtjevToolBox();
    hboxLayout2->addWidget(m_fraZahtjevToolBox);

    fraMojiDokumenti->setLayout(hboxLayout2);
    vboxResultFrameLayout->addWidget(fraMojiDokumenti);

    m_fraResultsFrame->setLayout(vboxResultFrameLayout);
}

void FrmPregledZahtjeva::createZahtjevToolBox()
{
    QVBoxLayout *vboxZahtjevToolBoxLayout = new QVBoxLayout();
    vboxZahtjevToolBoxLayout->setContentsMargins(0, 0, 0, 0);
    vboxZahtjevToolBoxLayout->setSpacing(0);
    vboxZahtjevToolBoxLayout->setAlignment(Qt::AlignTop);

    // [0]
    m_scrZahtjevToolBox = new QScrollArea();
    m_scrZahtjevToolBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    createZahtjevToolBoxes();
    vboxZahtjevToolBoxLayout->addWidget(m_scrZahtjevToolBox);
    // [1]
    QFrame *fraIspisTitle = new QFrame();
    fraIspisTitle->setContentsMargins(0, 0, 0, 0);
    fraIspisTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraIspisTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraIspisTitleSizePolicy.setHorizontalStretch(0);
    fraIspisTitleSizePolicy.setVerticalStretch(0);
    fraIspisTitle->setSizePolicy(fraIspisTitleSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(0, 2, 0, 2);
    hboxLayout1->setSpacing(1);
    QLabel *lblIspisTitle = new QLabel(tr("Ispis"));
    hboxLayout1->addWidget(lblIspisTitle);
    QPushButton *btnExpandFrame1 = new QPushButton();
    btnExpandFrame1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame1->setFlat(true);
    btnExpandFrame1->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame1SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame1SizePolicy.setHorizontalStretch(0);
    btnExpandFrame1SizePolicy.setVerticalStretch(0);
    btnExpandFrame1->setSizePolicy(btnExpandFrame1SizePolicy);
    hboxLayout1->addWidget(btnExpandFrame1);
    fraIspisTitle->setLayout(hboxLayout1);
    vboxZahtjevToolBoxLayout->addWidget(fraIspisTitle);
    // [2]
    QFrame *fraIspisToolBox = new QFrame();
    fraIspisToolBox->setContentsMargins(0, 0, 0, 0);
    fraIspisToolBox->setFrameShape(QFrame::StyledPanel);
    QVBoxLayout *vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setContentsMargins(0, 2, 0, 2);
    vboxLayout2->setSpacing(1);
    m_btnDokument = new QPushButton(tr("Dokument"));
    m_btnDokument->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokument->setFlat(true);
    m_btnDokument->setCursor(Qt::PointingHandCursor);
    vboxLayout2->addWidget(m_btnDokument);
    m_btnLista = new QPushButton(tr("Lista"));
    m_btnLista->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnLista->setFlat(true);
    m_btnLista->setCursor(Qt::PointingHandCursor);
    m_btnLista->setVisible(false);
    vboxLayout2->addWidget(m_btnLista);
    fraIspisToolBox->setLayout(vboxLayout2);
    vboxZahtjevToolBoxLayout->addWidget(fraIspisToolBox);
    // [3]
    m_btnZatvori = new QPushButton(tr("Z A T V O R I"));
    m_btnZatvori->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
    m_btnZatvori->setCursor(Qt::PointingHandCursor);
    vboxZahtjevToolBoxLayout->addWidget(m_btnZatvori);

    m_fraZahtjevToolBox->setLayout(vboxZahtjevToolBoxLayout);
}

void FrmPregledZahtjeva::createZahtjevToolBoxes()
{
    QVBoxLayout *vboxZahtjevToolBoxesLayout = new QVBoxLayout();
    vboxZahtjevToolBoxesLayout->setContentsMargins(0, 2, 0, 2);
    vboxZahtjevToolBoxesLayout->setSpacing(1);
    vboxZahtjevToolBoxesLayout->setAlignment(Qt::AlignTop);
    // [0]
    QFrame *fraKanalProdajeTitle = new QFrame();
    fraKanalProdajeTitle->setContentsMargins(0, 0, 0, 0);
    fraKanalProdajeTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraKanalProdajeTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraKanalProdajeTitleSizePolicy.setHorizontalStretch(0);
    fraKanalProdajeTitleSizePolicy.setVerticalStretch(0);
    fraKanalProdajeTitle->setSizePolicy(fraKanalProdajeTitleSizePolicy);
    QHBoxLayout *hboxLayout0 = new QHBoxLayout();
    hboxLayout0->setContentsMargins(0, 2, 0, 2);
    hboxLayout0->setSpacing(1);
    QLabel *lblKanalProdajeTitle = new QLabel(tr("Kanal prodaje"));
    hboxLayout0->addWidget(lblKanalProdajeTitle);
    QPushButton *btnExpandFrame0 = new QPushButton();
    btnExpandFrame0->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame0->setFlat(true);
    btnExpandFrame0->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame0SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame0SizePolicy.setHorizontalStretch(0);
    btnExpandFrame0SizePolicy.setVerticalStretch(0);
    btnExpandFrame0->setSizePolicy(btnExpandFrame0SizePolicy);
    hboxLayout0->addWidget(btnExpandFrame0);
    fraKanalProdajeTitle->setLayout(hboxLayout0);
    vboxZahtjevToolBoxesLayout->addWidget(fraKanalProdajeTitle);
    // [1]
    QFrame *fraKanalProdajeToolBox = new QFrame();
    fraKanalProdajeToolBox->setContentsMargins(0, 0, 0, 0);
    fraKanalProdajeToolBox->setFrameShape(QFrame::StyledPanel);
    QVBoxLayout *vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setContentsMargins(0, 2, 0, 2);
    vboxLayout1->setSpacing(1);
    m_btnKanal = new QPushButton(tr("Kanal"));
//    m_btnKanal->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnKanal->setFlat(true);
    m_btnKanal->setCursor(Qt::PointingHandCursor);
    vboxLayout1->addWidget(m_btnKanal);
    m_btnMojiDokumenti = new QPushButton(tr("Moji dokumenti"));
//    m_btnMojiDokumenti->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnMojiDokumenti->setFlat(true);
    m_btnMojiDokumenti->setCursor(Qt::PointingHandCursor);
    m_btnMojiDokumenti->setObjectName(tr("ok"));
    m_btnMojiDokumenti->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OK.gif")));
    vboxLayout1->addWidget(m_btnMojiDokumenti);
    fraKanalProdajeToolBox->setLayout(vboxLayout1);
    vboxZahtjevToolBoxesLayout->addWidget(fraKanalProdajeToolBox);
    // [2]
    QFrame *fraOznaciTitle = new QFrame();
    fraOznaciTitle->setContentsMargins(0, 0, 0, 0);
    fraOznaciTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraOznaciTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraOznaciTitleSizePolicy.setHorizontalStretch(0);
    fraOznaciTitleSizePolicy.setVerticalStretch(0);
    fraOznaciTitle->setSizePolicy(fraOznaciTitleSizePolicy);
    QHBoxLayout *hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setContentsMargins(0, 2, 0, 2);
    hboxLayout2->setSpacing(1);
    QLabel *lblOznaciTitle = new QLabel(tr("Oznaći"));
    hboxLayout2->addWidget(lblOznaciTitle);
    QPushButton *btnExpandFrame2 = new QPushButton();
    btnExpandFrame2->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame2->setFlat(true);
    btnExpandFrame2->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame2SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame2SizePolicy.setHorizontalStretch(0);
    btnExpandFrame2SizePolicy.setVerticalStretch(0);
    btnExpandFrame2->setSizePolicy(btnExpandFrame2SizePolicy);
    hboxLayout2->addWidget(btnExpandFrame2);
    fraOznaciTitle->setLayout(hboxLayout2);
    vboxZahtjevToolBoxesLayout->addWidget(fraOznaciTitle);
    // [3]
    QFrame *fraOznaciToolBox = new QFrame();
    fraOznaciToolBox->setContentsMargins(0, 0, 0, 0);
    fraOznaciToolBox->setFrameShape(QFrame::StyledPanel);
    QVBoxLayout *vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setContentsMargins(0, 2, 0, 2);
    vboxLayout3->setSpacing(1);
    m_btnSve = new QPushButton(tr("Sve"));
    m_btnSve->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnSve->setFlat(true);
    m_btnSve->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnSve);
    m_btnNista = new QPushButton(tr("Ništa"));
    m_btnNista->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnNista->setFlat(true);
    m_btnNista->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnNista);
    fraOznaciToolBox->setLayout(vboxLayout3);
    vboxZahtjevToolBoxesLayout->addWidget(fraOznaciToolBox);
    // [4]
    QFrame *fraPregledTitle = new QFrame();
    fraPregledTitle->setContentsMargins(0, 0, 0, 0);
    fraPregledTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraPregledTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraPregledTitleSizePolicy.setHorizontalStretch(0);
    fraPregledTitleSizePolicy.setVerticalStretch(0);
    fraPregledTitle->setSizePolicy(fraPregledTitleSizePolicy);
    QHBoxLayout *hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setContentsMargins(0, 2, 0, 2);
    hboxLayout4->setSpacing(1);
    QLabel *lblPregledTitle = new QLabel(tr("Pregled"));
    hboxLayout4->addWidget(lblPregledTitle);
    QPushButton *btnExpandFrame4 = new QPushButton();
    btnExpandFrame4->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame4->setFlat(true);
    btnExpandFrame4->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame4SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame4SizePolicy.setHorizontalStretch(0);
    btnExpandFrame4SizePolicy.setVerticalStretch(0);
    btnExpandFrame4->setSizePolicy(btnExpandFrame4SizePolicy);
    hboxLayout4->addWidget(btnExpandFrame4);
    fraPregledTitle->setLayout(hboxLayout4);
    vboxZahtjevToolBoxesLayout->addWidget(fraPregledTitle);
    // [5]
    QFrame *fraPregledToolBox = new QFrame();
    fraPregledToolBox->setContentsMargins(0, 0, 0, 0);
    fraPregledToolBox->setFrameShape(QFrame::StyledPanel);
//    QSizePolicy fraPregledToolBoxSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//    fraPregledToolBoxSizePolicy.setHorizontalStretch(0);
//    fraPregledToolBoxSizePolicy.setVerticalStretch(0);
//    fraPregledToolBox->setSizePolicy(fraPregledToolBoxSizePolicy);
    QVBoxLayout *vboxLayout5 = new QVBoxLayout();
    vboxLayout5->setContentsMargins(0, 2, 0, 2);
    vboxLayout5->setSpacing(1);
    m_btnSporazum = new QPushButton(tr("Sporazum"));
    m_btnSporazum->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnSporazum->setFlat(true);
    m_btnSporazum->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnSporazum);
    m_btnImovina = new QPushButton(tr("Imovina"));
    m_btnImovina->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnImovina->setFlat(true);
    m_btnImovina->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnImovina);
    m_btnStanjaDonat = new QPushButton(tr("Stanja DONAT"));
    m_btnStanjaDonat->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStanjaDonat->setFlat(true);
    m_btnStanjaDonat->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnStanjaDonat);
    m_btnStanjaWwms = new QPushButton(tr("Stanja WWMS"));
    m_btnStanjaWwms->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStanjaWwms->setFlat(true);
    m_btnStanjaWwms->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnStanjaWwms);
    m_btnDetaljno = new QPushButton(tr("Detaljno"));
    m_btnDetaljno->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDetaljno->setFlat(true);
    m_btnDetaljno->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnDetaljno);
    m_btnProcesi = new QPushButton(tr("Procesi"));
    m_btnProcesi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnProcesi->setFlat(true);
    m_btnProcesi->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnProcesi);
    m_btnDisKarta = new QPushButton(tr("Dis karta"));
    m_btnDisKarta->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDisKarta->setFlat(true);
    m_btnDisKarta->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnDisKarta);
    fraPregledToolBox->setLayout(vboxLayout5);
    vboxZahtjevToolBoxesLayout->addWidget(fraPregledToolBox);
    // [6]
    QFrame *fraDokumentTitle = new QFrame();
    fraDokumentTitle->setContentsMargins(0, 0, 0, 0);
    fraDokumentTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraDokumentTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraDokumentTitleSizePolicy.setHorizontalStretch(0);
    fraDokumentTitleSizePolicy.setVerticalStretch(0);
    fraDokumentTitle->setSizePolicy(fraDokumentTitleSizePolicy);
    QHBoxLayout *hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setContentsMargins(0, 2, 0, 2);
    hboxLayout6->setSpacing(1);
    QLabel *lblDokumentTitle = new QLabel(tr("Dokument"));
    hboxLayout6->addWidget(lblDokumentTitle);
    m_btnDokumentTitleExpand = new QPushButton();
    m_btnDokumentTitleExpand->setObjectName(tr("col"));
    m_btnDokumentTitleExpand->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueDown.gif")));
    m_btnDokumentTitleExpand->setFlat(true);
    m_btnDokumentTitleExpand->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame6SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame6SizePolicy.setHorizontalStretch(0);
    btnExpandFrame6SizePolicy.setVerticalStretch(0);
    m_btnDokumentTitleExpand->setSizePolicy(btnExpandFrame6SizePolicy);
    hboxLayout6->addWidget(m_btnDokumentTitleExpand);
    fraDokumentTitle->setLayout(hboxLayout6);
    vboxZahtjevToolBoxesLayout->addWidget(fraDokumentTitle);
    // [7]
    m_fraDokumentToolBox = new QFrame();
    m_fraDokumentToolBox->setContentsMargins(0, 0, 0, 0);
    m_fraDokumentToolBox->setFrameShape(QFrame::StyledPanel);
    m_fraDokumentToolBox->setVisible(false);
    QVBoxLayout *vboxLayout7 = new QVBoxLayout();
    vboxLayout7->setContentsMargins(0, 2, 0, 2);
    vboxLayout7->setSpacing(1);
    m_btnNapomena = new QPushButton(tr("Napomena"));
    m_btnNapomena->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnNapomena->setFlat(true);
    m_btnNapomena->setCursor(Qt::PointingHandCursor);
    vboxLayout7->addWidget(m_btnNapomena);
    m_btnDatoteke = new QPushButton(tr("Datoteke"));
    m_btnDatoteke->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDatoteke->setFlat(true);
    m_btnDatoteke->setCursor(Qt::PointingHandCursor);
    vboxLayout7->addWidget(m_btnDatoteke);
    m_btnSpis = new QPushButton(tr("Spis"));
    m_btnSpis->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnSpis->setFlat(true);
    m_btnSpis->setCursor(Qt::PointingHandCursor);
    vboxLayout7->addWidget(m_btnSpis);
    m_btnJop = new QPushButton(tr("JOP"));
    m_btnJop->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnJop->setFlat(true);
    m_btnJop->setCursor(Qt::PointingHandCursor);
    vboxLayout7->addWidget(m_btnJop);
    m_btnDodijeliJop = new QPushButton(tr("Dodijeli JOP"));
    m_btnDodijeliJop->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDodijeliJop->setFlat(true);
    m_btnDodijeliJop->setCursor(Qt::PointingHandCursor);
    vboxLayout7->addWidget(m_btnDodijeliJop);
    QFrame *fraLine3 = new QFrame();
    fraLine3->setContentsMargins(2, 2, 2, 2);
    fraLine3->setFrameShape(QFrame::StyledPanel);
    fraLine3->setFrameShadow(QFrame::Sunken);
    fraLine3->setMinimumHeight(5);
    vboxLayout7->addWidget(fraLine3);
    m_btnOtpisZaduzenja = new QPushButton(tr("Otpis zaduženja"));
    m_btnOtpisZaduzenja->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnOtpisZaduzenja->setFlat(true);
    m_btnOtpisZaduzenja->setCursor(Qt::PointingHandCursor);
    vboxLayout7->addWidget(m_btnOtpisZaduzenja);
    m_fraDokumentToolBox->setLayout(vboxLayout7);
    vboxZahtjevToolBoxesLayout->addWidget(m_fraDokumentToolBox);
    // [8]
    QFrame *fraAdminTitle = new QFrame();
    fraAdminTitle->setContentsMargins(0, 0, 0, 0);
    fraAdminTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraAdminTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraAdminTitleSizePolicy.setHorizontalStretch(0);
    fraAdminTitleSizePolicy.setVerticalStretch(0);
    fraAdminTitle->setSizePolicy(fraAdminTitleSizePolicy);
    QHBoxLayout *hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setContentsMargins(0, 2, 0, 2);
    hboxLayout8->setSpacing(1);
    QLabel *lblAdminTitle = new QLabel(tr("Admin"));
    hboxLayout8->addWidget(lblAdminTitle);
    m_btnAdminTitleExpand = new QPushButton();
    m_btnAdminTitleExpand->setObjectName(tr("col"));
    m_btnAdminTitleExpand->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueDown.gif")));
    m_btnAdminTitleExpand->setFlat(true);
    m_btnAdminTitleExpand->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame8SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame8SizePolicy.setHorizontalStretch(0);
    btnExpandFrame8SizePolicy.setVerticalStretch(0);
    m_btnAdminTitleExpand->setSizePolicy(btnExpandFrame8SizePolicy);
    hboxLayout8->addWidget(m_btnAdminTitleExpand);
    fraAdminTitle->setLayout(hboxLayout8);
    vboxZahtjevToolBoxesLayout->addWidget(fraAdminTitle);
    // [9]
    m_fraAdminToolBox = new QFrame();
    m_fraAdminToolBox->setContentsMargins(0, 0, 0, 0);
    m_fraAdminToolBox->setFrameShape(QFrame::StyledPanel);
    m_fraAdminToolBox->setVisible(false);
    QVBoxLayout *vboxLayout9 = new QVBoxLayout();
    vboxLayout9->setContentsMargins(0, 2, 0, 2);
    vboxLayout9->setSpacing(1);
    m_btnUlaznePoruke = new QPushButton(tr("Ulazne poruke"));
    m_btnUlaznePoruke->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnUlaznePoruke->setFlat(true);
    m_btnUlaznePoruke->setCursor(Qt::PointingHandCursor);
    vboxLayout9->addWidget(m_btnUlaznePoruke);
    m_btnPromijenaKpro = new QPushButton(tr("Promijena k. pro..."));
    m_btnPromijenaKpro->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnPromijenaKpro->setFlat(true);
    m_btnPromijenaKpro->setCursor(Qt::PointingHandCursor);
    vboxLayout9->addWidget(m_btnPromijenaKpro);
    m_btnDatumZahtjeva = new QPushButton(tr("Datum zahtjeva"));
    m_btnDatumZahtjeva->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDatumZahtjeva->setFlat(true);
    m_btnDatumZahtjeva->setCursor(Qt::PointingHandCursor);
    vboxLayout9->addWidget(m_btnDatumZahtjeva);
    m_fraAdminToolBox->setLayout(vboxLayout9);
    vboxZahtjevToolBoxesLayout->addWidget(m_fraAdminToolBox);

    m_scrZahtjevToolBox->setLayout(vboxZahtjevToolBoxesLayout);
}

void FrmPregledZahtjeva::createFormActions()
{
    connect(m_cboKlase,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_cboKlase_currentIndexChanged(int)));
    connect(m_grdZahtjevi,
            SIGNAL(itemPressed(QTableWidgetItem*)),
            this,
            SLOT(on_grdZahtjevi_itemPressed(QTableWidgetItem*)));
    // [Tip Kupca]
    connect(m_btnPrivatni,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPrivatni_clicked()));
    connect(m_btnKljucni,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnKljucni_clicked()));
    connect(m_btnPoslovni,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPoslovni_clicked()));
    // [Period]
    connect(m_btnDanas,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDanas_clicked()));
    connect(m_btnOvajTjedan,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnOvajTjedan_clicked()));
    connect(m_btnOvajMjesec,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnOvajMjesec_clicked()));
    // [Status]
    connect(m_btnSvi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnSvi_clicked()));
    connect(m_btnUtijeku,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnUtijeku_clicked()));
    connect(m_btnRezerviran,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnRezerviran_clicked()));
    connect(m_btnStorniran,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnStorniran_clicked()));
    connect(m_btnValidacija,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnValidacija_clicked()));
    connect(m_btnPojedinacno,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPojedinacno_clicked()));
    // [Sporazum]
    connect(m_btnStorno,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnStorno_clicked()));
    connect(m_btnStornoDonat,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnStornoDonat_clicked()));
    connect(m_btnNastavakRealizacije,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnNastavakRealizacije_clicked()));
    connect(m_btnPretvoriU1Kunu,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPretvoriU1Kunu_clicked()));
    // [Kanal prodaje]
    connect(m_btnKanal,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnKanal_clicked()));
    connect(m_btnMojiDokumenti,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnbtnMojiDokumenti_clicked()));
    // [Oznaci]
    connect(m_btnSve,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnSve_clicked()));
    connect(m_btnNista,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnNista_clicked()));
    // [Pregled]
    connect(m_btnSporazum,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnSporazum_clicked()));
    connect(m_btnImovina,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnImovina_clicked()));
    connect(m_btnStanjaDonat,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnStanjaDonat_clicked()));
    connect(m_btnStanjaWwms,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnStanjaWwms_clicked()));
    connect(m_btnDetaljno,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDetaljno_clicked()));
    connect(m_btnProcesi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnProcesi_clicked()));
    connect(m_btnDisKarta,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDisKarta_clicked()));
    // [Dokument]
    connect(m_btnNapomena,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnNapomena_clicked()));
    connect(m_btnDatoteke,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDatoteke_clicked()));
    connect(m_btnSpis,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnSpis_clicked()));
    connect(m_btnJop,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnJop_clicked()));
    connect(m_btnDodijeliJop,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDodijeliJop_clicked()));
    connect(m_btnOtpisZaduzenja,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnOtpisZaduzenja_clicked()));
    // [Admin]
    connect(m_btnUlaznePoruke,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnUlaznePoruke_clicked()));
    connect(m_btnPromijenaKpro,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPromijenaKpro_clicked()));
    connect(m_btnDatumZahtjeva,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDatumZahtjeva_clicked()));
    // [Ispis]
    connect(m_btnDokument,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokument_clicked()));

    connect(m_btnDokumentTitleExpand,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentTitleExpand_clicked()));
    connect(m_btnAdminTitleExpand,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnAdminTitleExpand_clicked()));

    connect(m_btnZatvori,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnZatvori_clicked()));

}

void FrmPregledZahtjeva::createFormMenus()
{

}

void FrmPregledZahtjeva::createFormToolBars()
{

}

void FrmPregledZahtjeva::createFormStatusBar()
{
    QLabel *lblDonatDate = new QLabel(tr("     ") + QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")) + tr("     "));
    lblDonatDate->setFrameShape(QFrame::StyledPanel);
    QLabel *lblDonatTime = new QLabel(QDateTime::currentDateTime().toString(tr("hh:mm")));
    lblDonatTime->setFrameShape(QFrame::StyledPanel);
    QLabel *lblStatusbarMessage = new QLabel(tr("                              "));
    lblStatusbarMessage->setFrameShape(QFrame::StyledPanel);
    QLabel *lblDonatDbInfo = new QLabel(QString::fromStdString(g_DonatDatebase) + tr(" - ") + QString::fromStdString(g_DonatUser));
    lblDonatDbInfo->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblDonatDbInfoSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    lblDonatDbInfoSizePolicy.setHorizontalStretch(0);
    lblDonatDbInfoSizePolicy.setVerticalStretch(0);
    lblDonatDbInfo->setSizePolicy(lblDonatDbInfoSizePolicy);

    statusBar()->addWidget(lblDonatDate);
    statusBar()->addWidget(lblDonatTime);
    statusBar()->addWidget(lblStatusbarMessage);
    statusBar()->addWidget(lblDonatDbInfo);
}

void FrmPregledZahtjeva::popuniSveKlase()
{
	string strSqlStatement;
	strSqlStatement.append("SELECT LPRODUKATA_ID, NAZIV FROM V_LINIJE_PRODUKATA ORDER BY RBK ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            m_cboKlase->addItem(
                        QString::fromStdString(rs->getString(2)),
                        QVariant(rs->getInt(1)));
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}

void FrmPregledZahtjeva::popuniKanalProdaje()
{
	string strSqlStatement;
	strSqlStatement.append("SELECT SUM(DECODE(KORISNIK_ID_2,'ROLA_KC',1,0)) KC, ");
	strSqlStatement.append(" SUM(DECODE(KORISNIK_ID_2,'ROLA_LAKC',1,0)) LAKC ");
	strSqlStatement.append("FROM VEZE_KORISNIKA ");
	strSqlStatement.append("WHERE KORISNIK_ID = '");
	strSqlStatement.append(g_DonatUser);
	strSqlStatement.append("'");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

	int iKC = 0;
	int iLAKC = 0;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
           iKC = rs->getInt(1);
           iLAKC = rs->getInt(2);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if((iKC + iLAKC) > 0)
    {
        m_iTipKanalaProdaje = 0;
        m_strKanalProdaje = cttl::itos(iKC + iLAKC);
    }
    else
    {
        if(iKC > 0)
        {
            m_iTipKanalaProdaje = 1;
            m_strKanalProdaje = "1";
        }
        else
        {
            if(iLAKC > 0)
            {
                m_iTipKanalaProdaje = 2;
                m_strKanalProdaje = "2";
            }
        }
    }

}

void FrmPregledZahtjeva::popuniZahtjeve()
{
    m_grdZahtjevi->clearContents();
    m_grdZahtjevi->setRowCount(0);
    m_iSporazumId = 0;

	string strTipSporazumaId;
	if(m_iTipDokumenta == 1)
	{
		strTipSporazumaId.append("1, 4, 7, 8, 11, 12");
	}
	else
	{
		strTipSporazumaId.append(cttl::itos(m_iTipDokumenta));
	}

	string strSqlStatement;
	strSqlStatement.append("SELECT /*+ RULE */   ");
	strSqlStatement.append(" to_char(DATUM_OD, 'DD.MM.YYYY') AS OD, ");
	strSqlStatement.append(" BROJ_DOK, FORMATIRANI_NAZIV, ADRESA, STATUS_ID, ");
	strSqlStatement.append(" SPORAZUM_ID, UGOVOR_IND, JOP, TSPORAZUMA_ID, KUPAC_ID ");
	strSqlStatement.append("FROM V_PREGLED_SPORAZUMI2 WHERE ");
	strSqlStatement.append(" KUPAC_ID = ");
	strSqlStatement.append(cttl::itos(m_iStrankaId));
	strSqlStatement.append(" AND VSPORAZUMA_ID!=0 AND TSPORAZUMA_ID IN (");
	strSqlStatement.append(strTipSporazumaId);
	strSqlStatement.append(") ");
	if(m_cboKlase->currentIndex() != 0)
	{
		strSqlStatement.append(" AND KLASA ='");
		strSqlStatement.append(m_cboKlase->currentText().toStdString());
		strSqlStatement.append("'");
	}
	strSqlStatement.append(" ORDER BY SPORAZUM_ID");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_grdZahtjevi->rowCount();
            m_grdZahtjevi->insertRow(row);
            m_grdZahtjevi->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
            m_grdZahtjevi->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(1))));
            m_grdZahtjevi->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_grdZahtjevi->setItem(row, 3, new QTableWidgetItem(
                                       QString::fromStdString(rs->getString(3))
                                       + tr(" , ")
                                       + QString::fromStdString(rs->getString(4))));
            m_grdZahtjevi->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(8))));
            m_grdZahtjevi->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getInt(5))));
            m_grdZahtjevi->setItem(row, 6, new QTableWidgetItem(QString::number(rs->getUInt(6))));
            m_grdZahtjevi->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(rs->getString(7))));
            m_grdZahtjevi->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(rs->getString(8))));
            m_grdZahtjevi->setItem(row, 9, new QTableWidgetItem(QString::number(rs->getUInt(9))));
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

}

// [ Event Handlers ]
void FrmPregledZahtjeva::on_cboKlase_currentIndexChanged(int index)
{
    if(index == 0)
    {
        m_lblMojeKlase->setText(tr("Sve klase"));
        m_iFltLinijaProduktaId = 0;
        return;
    }
    m_lblMojeKlase->setText(m_cboKlase->currentText());
    m_iFltLinijaProduktaId = m_cboKlase->itemData(index).toInt();
}
void FrmPregledZahtjeva::on_btnDokumentTitleExpand_clicked()
{
    m_btnDokumentTitleExpand->icon().detach();
    if(m_btnDokumentTitleExpand->objectName() == tr("exp"))
    {
        m_btnDokumentTitleExpand->setObjectName(tr("col"));
        m_btnDokumentTitleExpand->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueDown.gif")));
        m_fraDokumentToolBox->setVisible(false);
    }
    else
    {
        m_btnDokumentTitleExpand->setObjectName(tr("exp"));
        m_btnDokumentTitleExpand->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
        m_fraDokumentToolBox->setVisible(true);
    }
}
void FrmPregledZahtjeva::on_btnAdminTitleExpand_clicked()
{
    m_btnAdminTitleExpand->icon().detach();
    if(m_btnAdminTitleExpand->objectName() == tr("exp"))
    {
        m_btnAdminTitleExpand->setObjectName(tr("col"));
        m_btnAdminTitleExpand->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueDown.gif")));
        m_fraAdminToolBox->setVisible(false);
    }
    else
    {
        m_btnAdminTitleExpand->setObjectName(tr("exp"));
        m_btnAdminTitleExpand->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
        m_fraAdminToolBox->setVisible(true);
    }
}
void FrmPregledZahtjeva::on_btnPrivatni_clicked()
{
    if(m_btnPrivatni->objectName() != tr("ok"))
    {
        m_btnPrivatni->setObjectName(tr("ok"));
        m_btnPrivatni->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OK.gif")));
        m_btnKljucni->setIcon(QIcon());
        m_btnKljucni->setObjectName(tr(""));
        m_btnPoslovni->setIcon(QIcon());
        m_btnPoslovni->setObjectName(tr(""));
    }
}
void FrmPregledZahtjeva::on_btnKljucni_clicked()
{
    if(m_btnKljucni->objectName() != tr("ok"))
    {
        m_btnKljucni->setObjectName(tr("ok"));
        m_btnKljucni->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OK.gif")));
        m_btnPrivatni->setObjectName(tr(""));
        m_btnPrivatni->setIcon(QIcon());
        m_btnPoslovni->setObjectName(tr(""));
        m_btnPoslovni->setIcon(QIcon());
    }
}
void FrmPregledZahtjeva::on_btnPoslovni_clicked()
{
    if(m_btnPoslovni->objectName() != tr("ok"))
    {
        m_btnPoslovni->setObjectName(tr("ok"));
        m_btnPoslovni->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OK.gif")));
        m_btnPrivatni->setObjectName(tr(""));
        m_btnPrivatni->setIcon(QIcon());
        m_btnKljucni->setObjectName(tr(""));
        m_btnKljucni->setIcon(QIcon());
    }
}
void FrmPregledZahtjeva::on_btnDanas_clicked()
{

}
void FrmPregledZahtjeva::on_btnOvajTjedan_clicked()
{

}
void FrmPregledZahtjeva::on_btnOvajMjesec_clicked()
{

}
void FrmPregledZahtjeva::on_btnSvi_clicked()
{

}
void FrmPregledZahtjeva::on_btnUtijeku_clicked()
{

}
void FrmPregledZahtjeva::on_btnRezerviran_clicked()
{

}
void FrmPregledZahtjeva::on_btnStorniran_clicked()
{

}
void FrmPregledZahtjeva::on_btnValidacija_clicked()
{

}
void FrmPregledZahtjeva::on_btnPojedinacno_clicked()
{

}
void FrmPregledZahtjeva::on_btnStorno_clicked()
{

}
void FrmPregledZahtjeva::on_btnStornoDonat_clicked()
{

}
void FrmPregledZahtjeva::on_btnNastavakRealizacije_clicked()
{

}
void FrmPregledZahtjeva::on_btnPretvoriU1Kunu_clicked()
{

}
void FrmPregledZahtjeva::on_btnKanal_clicked()
{
    if(m_btnKanal->objectName() != tr("ok"))
    {
        m_btnKanal->setObjectName(tr("ok"));
        m_btnKanal->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OK.gif")));
        m_btnMojiDokumenti->setObjectName(tr(""));
        m_btnMojiDokumenti->setIcon(QIcon());
    }
}
void FrmPregledZahtjeva::on_btnbtnMojiDokumenti_clicked()
{
    if(m_btnMojiDokumenti->objectName() != tr("ok"))
    {
        m_btnMojiDokumenti->setObjectName(tr("ok"));
        m_btnMojiDokumenti->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OK.gif")));
        m_btnKanal->setObjectName(tr(""));
        m_btnKanal->setIcon(QIcon());
    }
}
void FrmPregledZahtjeva::on_btnDokument_clicked()
{
}
void FrmPregledZahtjeva::on_btnSve_clicked()
{
    if(m_grdZahtjevi->rowCount() == 0)
        return;

    m_grdZahtjevi->selectAll();
}
void FrmPregledZahtjeva::on_btnNista_clicked()
{
    if(m_grdZahtjevi->rowCount() == 0)
        return;

    m_grdZahtjevi->clearSelection();
}
void FrmPregledZahtjeva::on_btnSporazum_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat user password change
    FrmStavkeSporazuma *frmStavkeSporazuma = new FrmStavkeSporazuma(m_iSporazumId, this);
    frmStavkeSporazuma->exec();
    delete frmStavkeSporazuma;
}
void FrmPregledZahtjeva::on_btnImovina_clicked()
{
//    if(m_iGrupaImovineId == 0)
//        return;

//    // Show Donat stavke sporazuma
//    FrmPregledImovine *frmPregledImovine = new FrmPregledImovine(m_iGrupaImovineId, this);
//    frmPregledImovine->exec();
//    delete frmPregledImovine;
}
void FrmPregledZahtjeva::on_btnStanjaDonat_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat - status
    FrmDonatPregled *frmDonatTicketPregled = new FrmDonatPregled(m_iSporazumId, this);
    frmDonatTicketPregled->exec();
    delete frmDonatTicketPregled;
}
void FrmPregledZahtjeva::on_btnStanjaWwms_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat - WWMS Ticket status
    FrmWwmsPregled *frmWwmsTicketPregled = new FrmWwmsPregled(m_iSporazumId, m_iTipDokumenta, this);
    frmWwmsTicketPregled->exec();
    delete frmWwmsTicketPregled;
}
void FrmPregledZahtjeva::on_btnDetaljno_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat detaljan pregled sporazuma
    FrmPregledSporazuma *frmDetaljanPregledSporazuma = new FrmPregledSporazuma(m_iSporazumId, this);
    frmDetaljanPregledSporazuma->exec();
    delete frmDetaljanPregledSporazuma;

}
void FrmPregledZahtjeva::on_btnProcesi_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat order management processes
    FrmPregledProcesa *frmPregledProcesa = new FrmPregledProcesa(m_iSporazumId, this);
    frmPregledProcesa->exec();
    delete frmPregledProcesa;
}
void FrmPregledZahtjeva::on_btnDisKarta_clicked()
{

}
void FrmPregledZahtjeva::on_btnNapomena_clicked()
{

}
void FrmPregledZahtjeva::on_btnDatoteke_clicked()
{

}
void FrmPregledZahtjeva::on_btnSpis_clicked()
{

}
void FrmPregledZahtjeva::on_btnJop_clicked()
{

}
void FrmPregledZahtjeva::on_btnDodijeliJop_clicked()
{

}
void FrmPregledZahtjeva::on_btnOtpisZaduzenja_clicked()
{

}
void FrmPregledZahtjeva::on_btnUlaznePoruke_clicked()
{

}
void FrmPregledZahtjeva::on_btnPromijenaKpro_clicked()
{

}
void FrmPregledZahtjeva::on_btnDatumZahtjeva_clicked()
{

}

void FrmPregledZahtjeva::on_btnZatvori_clicked()
{
    this->close();
}
void FrmPregledZahtjeva::on_grdZahtjevi_itemPressed(QTableWidgetItem* itemZahtjev)
{
    m_iSporazumId = m_grdZahtjevi->item(itemZahtjev->row(), 6)->text().toUInt();

}

FrmPregledZahtjeva::~FrmPregledZahtjeva()
{

}

}   // namespace sporazumi
