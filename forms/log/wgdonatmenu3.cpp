//
//  wgdonatmenu3.cpp
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

#include "wgdonatmenu3.h"

namespace Log {

WgDonatMenu3::WgDonatMenu3(QWidget *parent) :
    QWidget(parent)
{
    m_vboxDonatSearchResults = new QVBoxLayout();
    m_vboxDonatSearchResults->setContentsMargins(2, 2, 2, 2);
    m_vboxDonatSearchResults->setSpacing(1);
    // [0]
    createDonatSearchResultsTitle();
    m_vboxDonatSearchResults->addWidget(m_fraDonatSearchResultTitle);
    // [1]
    createDonatSearchResultsStranke();
    m_vboxDonatSearchResults->addWidget(m_grdDonatStranke);
    // [2]
    createDonatSearchResultsLoyalty();
    m_vboxDonatSearchResults->addWidget(m_fraDonatSearchResultLoyalty);
    // [3]
    createDonatSearchResultsBrzina();
    m_vboxDonatSearchResults->addWidget(m_fraDonatSearchResultBrzina);
    // [4]
    createDonatSearchResultsZastupnik();
    m_vboxDonatSearchResults->addWidget(m_fraDonatSearchResultZastupnik);
    // [5]
    createDonatSearchResultsToolBar();
    m_vboxDonatSearchResults->addWidget(m_fraDonatSearchResultToolBar);
    // [6]
    createDonatSearchResultsMessages();
    m_vboxDonatSearchResults->addWidget(m_fraDonatSearchResultMessages);

//    QSizePolicy fraDonatSearchResultsSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
//    fraDonatSearchResultsSizePolicy.setHorizontalStretch(0);
//    fraDonatSearchResultsSizePolicy.setVerticalStretch(0);
//    this->setSizePolicy(fraDonatSearchResultsSizePolicy);

    setLayout(m_vboxDonatSearchResults);
}

void WgDonatMenu3::createDonatSearchResultsTitle()
{
    m_fraDonatSearchResultTitle = new QFrame();
    m_fraDonatSearchResultTitle->setContentsMargins(0, 0, 0, 0);
//    m_fraDonatSearchResultTitle->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxDonatSearchResultTitleLayout = new QHBoxLayout();
    hboxDonatSearchResultTitleLayout->setContentsMargins(0, 2, 0, 2);
    hboxDonatSearchResultTitleLayout->setSpacing(1);

    //[0]
    QLabel *lblDonatSearchResultStrankeNazivTitle = new QLabel(tr("Naziv i adresa stranke"));
    lblDonatSearchResultStrankeNazivTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblDonatSearchResultStrankeNazivTitleSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    lblDonatSearchResultStrankeNazivTitleSizePolicy.setHorizontalStretch(0);
    lblDonatSearchResultStrankeNazivTitleSizePolicy.setVerticalStretch(0);
    lblDonatSearchResultStrankeNazivTitle->setSizePolicy(lblDonatSearchResultStrankeNazivTitleSizePolicy);
    hboxDonatSearchResultTitleLayout->addWidget(lblDonatSearchResultStrankeNazivTitle);
    //[1]
    QLabel *lblDonatSearchResultStrankeRezultatTitle = new QLabel(tr("Rezultat"));
    lblDonatSearchResultStrankeRezultatTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblDonatSearchResultStrankeRezultatTitleSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    lblDonatSearchResultStrankeRezultatTitleSizePolicy.setHorizontalStretch(0);
    lblDonatSearchResultStrankeRezultatTitleSizePolicy.setVerticalStretch(0);
    lblDonatSearchResultStrankeRezultatTitle->setSizePolicy(lblDonatSearchResultStrankeRezultatTitleSizePolicy);
    hboxDonatSearchResultTitleLayout->addWidget(lblDonatSearchResultStrankeRezultatTitle);
    //[2]
    m_cboDonatSearchResult = new QComboBox();
    m_cboDonatSearchResult->addItem(tr(""));
    m_cboDonatSearchResult->addItem(tr("1 - 50"));
    m_cboDonatSearchResult->addItem(tr("50 - 100"));
    m_cboDonatSearchResult->setCurrentIndex(0);
    m_cboDonatSearchResult->setEditable(TRUE);
//    m_cboDonatSearchResult->setFrameShape(QFrame::StyledPanel);
    QSizePolicy cboDonatSearchResultSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    cboDonatSearchResultSizePolicy.setHorizontalStretch(0);
    cboDonatSearchResultSizePolicy.setVerticalStretch(0);
    m_cboDonatSearchResult->setSizePolicy(cboDonatSearchResultSizePolicy);
    hboxDonatSearchResultTitleLayout->addWidget(m_cboDonatSearchResult);

    m_fraDonatSearchResultTitle->setLayout(hboxDonatSearchResultTitleLayout);
}

void WgDonatMenu3::createDonatSearchResultsStranke()
{
    m_grdDonatStranke = new QTableWidget();
    m_grdDonatStranke->setContentsMargins(4, 4, 0, 0);
    m_grdDonatStranke->setFrameShape(QFrame::StyledPanel);
    m_grdDonatStranke->setMinimumWidth(640);
    // Create headers
    QStringList labels;
    labels << "StrankaID" << "Formatirani Naziv" << "Formatirana Adresa"
           << "AdresaID" << "Validirana Adresa" << "TipStrankeID";
    m_grdDonatStranke->setColumnCount(6);
    m_grdDonatStranke->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_grdDonatStranke->setHorizontalHeaderLabels(labels);
    m_grdDonatStranke->horizontalHeader()->setStretchLastSection(true);
    m_grdDonatStranke->setColumnWidth(0, 1);
    m_grdDonatStranke->setColumnWidth(1, 280);
    m_grdDonatStranke->setColumnWidth(2, 310);
    m_grdDonatStranke->setColumnWidth(3, 0);
    m_grdDonatStranke->setColumnWidth(4, 14);
    m_grdDonatStranke->setColumnWidth(5, 0);
    m_grdDonatStranke->hideColumn(0);
    m_grdDonatStranke->hideColumn(3);
    m_grdDonatStranke->hideColumn(5);
    m_grdDonatStranke->verticalHeader()->hide();
    m_grdDonatStranke->horizontalHeader()->hide();
    m_grdDonatStranke->setAlternatingRowColors(TRUE);
    m_grdDonatStranke->setShowGrid(false);
    m_grdDonatStranke->setSelectionMode(QAbstractItemView::SingleSelection);
    m_grdDonatStranke->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void WgDonatMenu3::createDonatSearchResultsLoyalty()
{
    m_fraDonatSearchResultLoyalty = new QFrame();
    m_fraDonatSearchResultLoyalty->setContentsMargins(0, 0, 0, 0);
//    m_fraDonatSearchResultLoyalty->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxDonatSearchResultLoyaltyLayout = new QHBoxLayout();
    hboxDonatSearchResultLoyaltyLayout->setContentsMargins(0, 2, 0, 2);
    hboxDonatSearchResultLoyaltyLayout->setSpacing(1);

    // [0]
    QLabel *lblDonatLoyaltyIdTitle = new QLabel(tr("LOYALTY ID"));
    lblDonatLoyaltyIdTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblDonatLoyaltyIdTitleSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    lblDonatLoyaltyIdTitleSizePolicy.setHorizontalStretch(0);
    lblDonatLoyaltyIdTitleSizePolicy.setVerticalStretch(0);
    lblDonatLoyaltyIdTitle->setSizePolicy(lblDonatLoyaltyIdTitleSizePolicy);
    hboxDonatSearchResultLoyaltyLayout->addWidget(lblDonatLoyaltyIdTitle);
    // [1]
    m_txtStrankaLoyaltyId = new QLabel();
    m_txtStrankaLoyaltyId->setFrameShape(QFrame::StyledPanel);
    m_txtStrankaLoyaltyId->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxDonatSearchResultLoyaltyLayout->addWidget(m_txtStrankaLoyaltyId);
    // [2]
    QLabel *lblDonatLoyaltyIdValidniBodovi = new QLabel(tr("VALIDNI BODOVI"));
    lblDonatLoyaltyIdValidniBodovi->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblDonatLoyaltyIdValidniBodoviSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    lblDonatLoyaltyIdValidniBodoviSizePolicy.setHorizontalStretch(0);
    lblDonatLoyaltyIdValidniBodoviSizePolicy.setVerticalStretch(0);
    lblDonatLoyaltyIdValidniBodovi->setSizePolicy(lblDonatLoyaltyIdValidniBodoviSizePolicy);
    hboxDonatSearchResultLoyaltyLayout->addWidget(lblDonatLoyaltyIdValidniBodovi);
    // [3]
    m_txtStrankaLoyaltyValidniBodovi = new QLabel();
    m_txtStrankaLoyaltyValidniBodovi->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    m_txtStrankaLoyaltyValidniBodovi->setFrameShape(QFrame::StyledPanel);
    hboxDonatSearchResultLoyaltyLayout->addWidget(m_txtStrankaLoyaltyValidniBodovi);
    // [4]
    QLabel *lblDonatLoyaltyPotencijalniBodovi = new QLabel(tr("POTENCIJALNI BODOVI"));
    lblDonatLoyaltyPotencijalniBodovi->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblDonatLoyaltyPotencijalniBodoviSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    lblDonatLoyaltyPotencijalniBodoviSizePolicy.setHorizontalStretch(0);
    lblDonatLoyaltyPotencijalniBodoviSizePolicy.setVerticalStretch(0);
    lblDonatLoyaltyPotencijalniBodovi->setSizePolicy(lblDonatLoyaltyPotencijalniBodoviSizePolicy);
    hboxDonatSearchResultLoyaltyLayout->addWidget(lblDonatLoyaltyPotencijalniBodovi);
    // [5]
    m_txtStrankaLoyaltyPotencijalniBodovi = new QLabel();
    m_txtStrankaLoyaltyPotencijalniBodovi->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    m_txtStrankaLoyaltyPotencijalniBodovi->setFrameShape(QFrame::StyledPanel);
    hboxDonatSearchResultLoyaltyLayout->addWidget(m_txtStrankaLoyaltyPotencijalniBodovi);
    // [6]
    m_btnLoyalty = new QPushButton();
    m_btnLoyalty->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/POVECALO.png")));
    // m_btnLoyalty->setCursor(Qt::PointingHandCursor);
    // m_btnLoyalty->setFlat(TRUE);
    QSizePolicy btnLoyaltySizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnLoyaltySizePolicy.setHorizontalStretch(0);
    btnLoyaltySizePolicy.setVerticalStretch(0);
    m_btnLoyalty->setSizePolicy(btnLoyaltySizePolicy);
    m_btnLoyalty->setToolTip(tr("Loyalty"));
    hboxDonatSearchResultLoyaltyLayout->addWidget(m_btnLoyalty);

    m_fraDonatSearchResultLoyalty->setLayout(hboxDonatSearchResultLoyaltyLayout);
}

void WgDonatMenu3::createDonatSearchResultsBrzina()
{
    m_fraDonatSearchResultBrzina = new QFrame();
    m_fraDonatSearchResultBrzina->setContentsMargins(0, 0, 0, 0);
//    m_fraDonatSearchResultBrzina->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxDonatSearchResultBrzinaLayout = new QHBoxLayout();
    hboxDonatSearchResultBrzinaLayout->setContentsMargins(0, 2, 0, 2);
    hboxDonatSearchResultBrzinaLayout->setSpacing(1);
    // [0]
    m_btnStrankaPromjenaAdslStatusa = new QPushButton();
    m_btnStrankaPromjenaAdslStatusa->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/INT_2_16x16.png")));
    // m_btnStrankaPromjenaAdslStatusa->setCursor(Qt::PointingHandCursor);
    // m_btnStrankaPromjenaAdslStatusa->setFlat(TRUE);
    m_btnStrankaPromjenaAdslStatusa->setToolTip(tr("Promijena ADSL statusa"));
    QSizePolicy btnStrankaPromjenaAdslStatusaSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaPromjenaAdslStatusaSizePolicy.setHorizontalStretch(0);
    btnStrankaPromjenaAdslStatusaSizePolicy.setVerticalStretch(0);
    m_btnStrankaPromjenaAdslStatusa->setSizePolicy(btnStrankaPromjenaAdslStatusaSizePolicy);
    hboxDonatSearchResultBrzinaLayout->addWidget(m_btnStrankaPromjenaAdslStatusa);
    // [1]
    m_txtStrankaAdslStatus = new QLabel();
    m_txtStrankaAdslStatus->setFrameShape(QFrame::StyledPanel);
    m_txtStrankaAdslStatus->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxDonatSearchResultBrzinaLayout->addWidget(m_txtStrankaAdslStatus);
    // [2]
    m_btnStrankaPromijenaIptvStatusa = new QPushButton();
    m_btnStrankaPromijenaIptvStatusa->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/monitor_16x16.png")));
    // m_btnStrankaPromijenaIptvStatusa->setCursor(Qt::PointingHandCursor);
    // m_btnStrankaPromijenaIptvStatusa->setFlat(TRUE);
    m_btnStrankaPromijenaIptvStatusa->setToolTip(tr("Promijena IPTV statusa"));
    QSizePolicy btnStrankaPromijenaIptvStatusaSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaPromijenaIptvStatusaSizePolicy.setHorizontalStretch(0);
    btnStrankaPromijenaIptvStatusaSizePolicy.setVerticalStretch(0);
    m_btnStrankaPromijenaIptvStatusa->setSizePolicy(btnStrankaPromijenaIptvStatusaSizePolicy);
    hboxDonatSearchResultBrzinaLayout->addWidget(m_btnStrankaPromijenaIptvStatusa);
    // [3]
    m_txtStrankaMaxtvStatus = new QLabel();
    m_txtStrankaMaxtvStatus->setFrameShape(QFrame::StyledPanel);
    m_txtStrankaMaxtvStatus->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxDonatSearchResultBrzinaLayout->addWidget(m_txtStrankaMaxtvStatus);
    // [4]
    m_btnStrankaMjerenjeBrzine = new QPushButton();
    m_btnStrankaMjerenjeBrzine->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ctxwiz_cls.gif")));
    // m_btnStrankaMjerenjeBrzine->setCursor(Qt::PointingHandCursor);
    // m_btnStrankaMjerenjeBrzine->setFlat(TRUE);
    m_btnStrankaMjerenjeBrzine->setToolTip(tr("MJERENJE BRZINE"));
    QSizePolicy btnStrankaMjerenjeBrzine(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaMjerenjeBrzine.setHorizontalStretch(0);
    btnStrankaMjerenjeBrzine.setVerticalStretch(0);
    m_btnStrankaMjerenjeBrzine->setSizePolicy(btnStrankaMjerenjeBrzine);
    hboxDonatSearchResultBrzinaLayout->addWidget(m_btnStrankaMjerenjeBrzine);

    m_fraDonatSearchResultBrzina->setLayout(hboxDonatSearchResultBrzinaLayout);
}

void WgDonatMenu3::createDonatSearchResultsZastupnik()
{
    m_fraDonatSearchResultZastupnik = new QFrame();
    m_fraDonatSearchResultZastupnik->setContentsMargins(0, 0, 0, 0);
//    m_fraDonatSearchResultZastupnik->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxDonatSearchResultZastupnikLayout = new QHBoxLayout();
    hboxDonatSearchResultZastupnikLayout->setContentsMargins(0, 2, 0, 2);
    hboxDonatSearchResultZastupnikLayout->setSpacing(1);
    // [0]
    m_btnStrankaZatupnik1 = new QPushButton();
    m_btnStrankaZatupnik1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ULOGA_ID_16x16.png")));
    // m_btnStrankaZatupnik1->setCursor(Qt::PointingHandCursor);
    // m_btnStrankaZatupnik1->setFlat(TRUE);
    m_btnStrankaZatupnik1->setToolTip(tr(""));
    QSizePolicy btnStrankaZatupnik1(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaZatupnik1.setHorizontalStretch(0);
    btnStrankaZatupnik1.setVerticalStretch(0);
    m_btnStrankaZatupnik1->setSizePolicy(btnStrankaZatupnik1);
    hboxDonatSearchResultZastupnikLayout->addWidget(m_btnStrankaZatupnik1);
    // [1]
    m_txtStrankaZastupnik = new QLabel();
    m_txtStrankaZastupnik->setFrameShape(QFrame::StyledPanel);
    m_txtStrankaZastupnik->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxDonatSearchResultZastupnikLayout->addWidget(m_txtStrankaZastupnik);
    // [2]
    m_btnStrankaZatupnik2 = new QPushButton();
    m_btnStrankaZatupnik2->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/POVECALO.png")));
    // m_btnStrankaZatupnik2->setCursor(Qt::PointingHandCursor);
    // m_btnStrankaZatupnik2->setFlat(TRUE);
    m_btnStrankaZatupnik2->setToolTip(tr(""));
    QSizePolicy btnStrankaZatupnik2(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaZatupnik2.setHorizontalStretch(0);
    btnStrankaZatupnik2.setVerticalStretch(0);
    m_btnStrankaZatupnik2->setSizePolicy(btnStrankaZatupnik2);
    hboxDonatSearchResultZastupnikLayout->addWidget(m_btnStrankaZatupnik2);

    m_fraDonatSearchResultZastupnik->setLayout(hboxDonatSearchResultZastupnikLayout);
}

void WgDonatMenu3::createDonatSearchResultsToolBar()
{
    m_fraDonatSearchResultToolBar = new QFrame();
    m_fraDonatSearchResultToolBar->setContentsMargins(0, 0, 0, 0);
//    m_fraDonatSearchResultToolBar->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraDonatSearchResultToolBarSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    fraDonatSearchResultToolBarSizePolicy.setHorizontalStretch(0);
    fraDonatSearchResultToolBarSizePolicy.setVerticalStretch(0);
    m_fraDonatSearchResultToolBar->setSizePolicy(fraDonatSearchResultToolBarSizePolicy);
    QHBoxLayout *hboxDonatSearchResultToolBarLayout = new QHBoxLayout();
    hboxDonatSearchResultToolBarLayout->setContentsMargins(0, 2, 0, 2);
    hboxDonatSearchResultToolBarLayout->setSpacing(1);
    // [0]
    QToolBox *tboxStrankaZahtjevi = new QToolBox();
    tboxStrankaZahtjevi->setFrameShape(QFrame::StyledPanel);
    QWidget *pageStrankaZahtjevi = new QWidget();
    QSizePolicy pageStrankaZahtjeviSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageStrankaZahtjeviSizePolicy.setHorizontalStretch(0);
    pageStrankaZahtjeviSizePolicy.setVerticalStretch(0);
    pageStrankaZahtjevi->setSizePolicy(pageStrankaZahtjeviSizePolicy);
    QVBoxLayout *vboxStrankaZahtjevi = new QVBoxLayout();
    vboxStrankaZahtjevi->setContentsMargins(1, 1, 1, 1);
    vboxStrankaZahtjevi->setSpacing(1);
    // [0]
    m_btnStrankaPregledZahtjeva = new QPushButton(tr("Pregled"));
    m_btnStrankaPregledZahtjeva->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStrankaPregledZahtjeva->setFlat(TRUE);
    m_btnStrankaPregledZahtjeva->setCursor(Qt::PointingHandCursor);
    vboxStrankaZahtjevi->addWidget(m_btnStrankaPregledZahtjeva);
    // [1]
    m_btnStrankaPregledNemogucnosti = new QPushButton(tr("Nemogućnost"));
    m_btnStrankaPregledNemogucnosti->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStrankaPregledNemogucnosti->setFlat(TRUE);
    m_btnStrankaPregledNemogucnosti->setCursor(Qt::PointingHandCursor);
    vboxStrankaZahtjevi->addWidget(m_btnStrankaPregledNemogucnosti);

    pageStrankaZahtjevi->setLayout(vboxStrankaZahtjevi);
    tboxStrankaZahtjevi->addItem(pageStrankaZahtjevi, tr("Zahtjevi"));
    hboxDonatSearchResultToolBarLayout->addWidget(tboxStrankaZahtjevi);
    // [1]
    QToolBox *tboxStrankaUgovori = new QToolBox();
    tboxStrankaUgovori->setFrameShape(QFrame::StyledPanel);
    QWidget *pageStrankaUgovori = new QWidget();
    QSizePolicy pageStrankaUgovoriSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageStrankaUgovoriSizePolicy.setHorizontalStretch(0);
    pageStrankaUgovoriSizePolicy.setVerticalStretch(0);
    pageStrankaUgovori->setSizePolicy(pageStrankaUgovoriSizePolicy);
    QVBoxLayout *vboxStrankaUgovori = new QVBoxLayout();
    vboxStrankaUgovori->setContentsMargins(1, 1, 1, 1);
    vboxStrankaUgovori->setSpacing(1);
    // [0]
    m_btnStrankaPregledUgovora = new QPushButton(tr("Pregled ugovora"));
    m_btnStrankaPregledUgovora->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStrankaPregledUgovora->setFlat(TRUE);
    m_btnStrankaPregledUgovora->setCursor(Qt::PointingHandCursor);
    vboxStrankaUgovori->addWidget(m_btnStrankaPregledUgovora);
    // [1]
    m_btnStrankaSklapanjeUgovora = new QPushButton(tr("Sklapanje ugovora"));
    m_btnStrankaSklapanjeUgovora->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStrankaSklapanjeUgovora->setFlat(TRUE);
    m_btnStrankaSklapanjeUgovora->setCursor(Qt::PointingHandCursor);
    vboxStrankaUgovori->addWidget(m_btnStrankaSklapanjeUgovora);

    pageStrankaUgovori->setLayout(vboxStrankaUgovori);
    tboxStrankaUgovori->addItem(pageStrankaUgovori, tr("Ugovori"));
    hboxDonatSearchResultToolBarLayout->addWidget(tboxStrankaUgovori);

    // [2]
    QToolBox *tboxStrankaMaticniPodaci = new QToolBox();
    tboxStrankaMaticniPodaci->setFrameShape(QFrame::StyledPanel);
    QWidget *pageStrankaMaticniPodaci = new QWidget();
    QSizePolicy pageStrankaMaticniPodaciSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageStrankaMaticniPodaciSizePolicy.setHorizontalStretch(0);
    pageStrankaMaticniPodaciSizePolicy.setVerticalStretch(0);
    pageStrankaMaticniPodaci->setSizePolicy(pageStrankaMaticniPodaciSizePolicy);
    QVBoxLayout *vboxStrankaMaticniPodaci = new QVBoxLayout();
    vboxStrankaMaticniPodaci->setContentsMargins(1, 1, 1, 1);
    vboxStrankaMaticniPodaci->setSpacing(1);
    // [0]
    m_btnStrankaZahtjevStranke = new QPushButton(tr("Zahtjev stranke"));
    m_btnStrankaZahtjevStranke->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStrankaZahtjevStranke->setFlat(TRUE);
    m_btnStrankaZahtjevStranke->setCursor(Qt::PointingHandCursor);
    vboxStrankaMaticniPodaci->addWidget(m_btnStrankaZahtjevStranke);
    // [1]
    m_btnStrankaInterno = new QPushButton(tr("Interno"));
    m_btnStrankaInterno->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStrankaInterno->setFlat(TRUE);
    m_btnStrankaInterno->setCursor(Qt::PointingHandCursor);
    vboxStrankaMaticniPodaci->addWidget(m_btnStrankaInterno);

    pageStrankaMaticniPodaci->setLayout(vboxStrankaMaticniPodaci);
    tboxStrankaMaticniPodaci->addItem(pageStrankaMaticniPodaci, tr("Matični podaci"));
    hboxDonatSearchResultToolBarLayout->addWidget(tboxStrankaMaticniPodaci);

    // [3]
    QToolBox *tboxStrankaObavijesti = new QToolBox();
    tboxStrankaObavijesti->setFrameShape(QFrame::StyledPanel);
    QWidget *pageStrankaObavijesti = new QWidget();
    QSizePolicy pageStrankaObavijestiSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    pageStrankaObavijestiSizePolicy.setHorizontalStretch(0);
    pageStrankaObavijestiSizePolicy.setVerticalStretch(0);
    pageStrankaObavijesti->setSizePolicy(pageStrankaObavijestiSizePolicy);
    QVBoxLayout *vboxStrankaObavijsti = new QVBoxLayout();
    vboxStrankaObavijsti->setContentsMargins(1, 1, 1, 1);
    vboxStrankaObavijsti->setSpacing(1);
    // [0]
    m_btnStrankaSlanjeObavijesti = new QPushButton(tr("Slanje"));
    m_btnStrankaSlanjeObavijesti->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStrankaSlanjeObavijesti->setFlat(TRUE);
    m_btnStrankaSlanjeObavijesti->setCursor(Qt::PointingHandCursor);
    vboxStrankaObavijsti->addWidget(m_btnStrankaSlanjeObavijesti);
    // [1]
    m_btnStrankaPoslaneObavijesti = new QPushButton(tr("Poslane"));
    m_btnStrankaPoslaneObavijesti->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnStrankaPoslaneObavijesti->setFlat(TRUE);
    m_btnStrankaPoslaneObavijesti->setCursor(Qt::PointingHandCursor);
    vboxStrankaObavijsti->addWidget(m_btnStrankaPoslaneObavijesti);

    pageStrankaObavijesti->setLayout(vboxStrankaObavijsti);
    tboxStrankaObavijesti->addItem(pageStrankaObavijesti, tr("Obavijesti"));
    hboxDonatSearchResultToolBarLayout->addWidget(tboxStrankaObavijesti);

    m_fraDonatSearchResultToolBar->setLayout(hboxDonatSearchResultToolBarLayout);
}

void WgDonatMenu3::createDonatSearchResultsMessages()
{
    m_fraDonatSearchResultMessages = new QFrame();
    m_fraDonatSearchResultMessages->setContentsMargins(0, 0, 0, 0);
//    m_fraDonatSearchResultMessages->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxDonatSearchResultMessagesLayout = new QHBoxLayout();
    hboxDonatSearchResultMessagesLayout->setContentsMargins(0, 2, 0, 2);
    hboxDonatSearchResultMessagesLayout->setSpacing(1);
    // [0]
    m_lblDonatStrankaMessages = new QLabel();
    m_lblDonatStrankaMessages->setFrameShape(QFrame::StyledPanel);
    m_lblDonatStrankaMessages->setMaximumWidth(640);
    m_lblDonatStrankaMessages->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxDonatSearchResultMessagesLayout->addWidget(m_lblDonatStrankaMessages);

    m_fraDonatSearchResultMessages->setLayout(hboxDonatSearchResultMessagesLayout);
}

WgDonatMenu3::~WgDonatMenu3()
{

}

}   // namespace log
