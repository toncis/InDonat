/************************************* Module Header **************************************\
* Module Name:  frmdonatmenu2.cpp
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

#include "frmdonatmenu2.h"
#include "frmdonatabout.h"
#include "frmdonatuserrole.h"
#include "frmdonatpasswordchange.h"
#include "forms/sporazumi/frmpregledzahtjeva.h"
#include "forms/sporazumi/frmpregledsporazuma.h"
#include "forms/stranka/frmstrankaocv.h"
#include "forms/stranka/frmstrankafiz.h"
#include "forms/stranka/frmstrankaprav.h"
#include "forms/kontakt/frmugovorneobveze.h"
#include "forms/kontakt/frmcpeoprema.h"
#include "forms/kontakt/frmdonatzahtjevall.h"
#include "itos.h"
#include "ocinumber.h"

namespace Log {

FrmDonatMenu2::FrmDonatMenu2(QWidget *parent) :
    QMainWindow(parent)
{
    // [0]
    m_fraDonatMainFrame = new QFrame();
    m_fraDonatMainFrame->setContentsMargins(0, 0, 0, 0);
    m_hboxDonatMainLayout = new QHBoxLayout();
    m_hboxDonatMainLayout->setContentsMargins(2, 4, 2, 4);
    m_hboxDonatMainLayout->setSpacing(1);

    m_wgDonatToolBar = new WgDonatMenu1();

    m_fraDonatMenu1 = new QFrame();
    m_fraDonatMenu1->setContentsMargins(0, 0, 0, 0);

    // [1]
    m_vboxDonatMenuLayout = new QVBoxLayout();
    m_vboxDonatMenuLayout->setContentsMargins(0, 0, 0, 0);
    m_vboxDonatMenuLayout->setSpacing(0);
    m_wgDonatSearch = new WgDonatMenu2();
    m_fraDonatSearchResult = new QFrame();
    m_fraDonatSearchResult->setContentsMargins(0, 0, 0, 0);
//    QSizePolicy fraDonatSearchResultSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    fraDonatSearchResultSizePolicy.setHorizontalStretch(0);
//    fraDonatSearchResultSizePolicy.setVerticalStretch(0);
//    m_fraDonatSearchResult->setSizePolicy(fraDonatSearchResultSizePolicy);
    // [2]
    m_hboxDonatSearchResultLayout = new QHBoxLayout();
    m_hboxDonatSearchResultLayout->setContentsMargins(0, 0, 0, 0);
    m_hboxDonatSearchResultLayout->setSpacing(0);
    m_wgDonatStranke = new WgDonatMenu3();
    m_wgDonatImovina = new WgDonatMenu4();
    m_hboxDonatSearchResultLayout->addWidget(m_wgDonatStranke);
    m_hboxDonatSearchResultLayout->addWidget(m_wgDonatImovina);
    m_fraDonatSearchResult->setLayout(m_hboxDonatSearchResultLayout);

    m_vboxDonatMenuLayout->addWidget(m_wgDonatSearch);
    m_vboxDonatMenuLayout->addWidget(m_fraDonatSearchResult);

    m_fraDonatMenu1->setLayout(m_vboxDonatMenuLayout);

    m_hboxDonatMainLayout->addWidget(m_wgDonatToolBar);
    m_hboxDonatMainLayout->addWidget(m_fraDonatMenu1);

    m_fraDonatMainFrame->setLayout(m_hboxDonatMainLayout);

    setCentralWidget(m_fraDonatMainFrame);

    createFrmDonatActions();
    createFrmDonatMenus();
    createFrmDonatToolBars();
    createFrmDonatStatusBar();

    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT"));
    // Set minimum form size
    setMinimumSize(1150, 860);
    m_wgDonatSearch->m_txtDonatSearch->setFocus();
    m_wgDonatSearch->m_btnDonatTrazi->setAutoDefault(TRUE);
    m_wgDonatSearch->m_btnDonatTrazi->setDefault(TRUE);
    m_wgDonatImovina->m_fraStrankaImovinaKlasaTitle->setVisible(FALSE);
    m_SearchMode = TraziPoNazivKorisnika;
    m_bPunoGrupaImovine = false;
    m_iGrupaImovineId = 0;
    m_iStrankaId = 0;
    m_iKupacId = 0;
}

// [ Private Member Functions ]
// Create Donat main form menu
void FrmDonatMenu2::createFrmDonatMenus()
{
    // [File]
    m_mnuFile = menuBar()->addMenu(tr("&File"));
    m_mnuFile->addAction(m_actExit);
    // [Zaporka]
    m_mnuPromijenaZaporke = menuBar()->addMenu(tr("&Promjena zaporke"));
    m_mnuPromijenaZaporke->addAction(m_actPromijenaZaporke);
    // [Sifarnik]
    m_mnuSifarnik = menuBar()->addMenu(tr("&Šifarnik"));
    m_mnuSifarnik->addAction(m_actTitula);
    m_mnuSifarnik->addAction(m_actModemi);
    m_mnuSifarnik->addAction(m_actKonAgenti);
    m_mnuSifarnik->addAction(m_actKonTehnologija);
    m_mnuSifarnik->addAction(m_actKonHelp);
    m_mnuSifarnik->addAction(m_actKonZdrawko);
    m_mnuSifarnik->addAction(m_actKonAnkete);
    m_mnuSifarnik->addAction(m_actKonTht);
    m_mnuSifarnik->addAction(m_actKonOstalo);
    // [Odrzavanje]
    m_mnuOdrzavanje = menuBar()->addMenu(tr("&Održavanje"));
    m_mnuOdrzavanje->addAction(m_actAzurirajRipote);
    m_mnuOdrzavanje->addAction(m_actAvayaRegistracija);
    m_mnuOdrzavanje->addAction(m_actMojeRole);
    // [About]
    m_mnuAbout = menuBar()->addMenu(tr("&O programu"));
    m_mnuAbout->addAction(m_actAbout);
    // m_mnuAbout->addSeparator();
}
// Create Donat main form statusbar
void FrmDonatMenu2::createFrmDonatStatusBar()
{
    m_lblDonatDate = new QLabel(tr("     ") + QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")) + tr("     "));
    m_lblDonatDate->setFrameShape(QFrame::StyledPanel);
    m_lblDonatTime = new QLabel(QDateTime::currentDateTime().toString(tr("hh:mm")));
    m_lblDonatTime->setFrameShape(QFrame::StyledPanel);
    m_lblStatusbarMessage = new QLabel(tr("                              "));
    m_lblStatusbarMessage->setFrameShape(QFrame::StyledPanel);
    m_lblDonatDbInfo = new QLabel(QString::fromStdString(g_DonatDatebase) + tr(" - ") + QString::fromStdString(g_DonatUser));
    m_lblDonatDbInfo->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblDonatDbInfoSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    lblDonatDbInfoSizePolicy.setHorizontalStretch(0);
    lblDonatDbInfoSizePolicy.setVerticalStretch(0);
    m_lblDonatDbInfo->setSizePolicy(lblDonatDbInfoSizePolicy);

    statusBar()->addWidget(m_lblDonatDate);
    statusBar()->addWidget(m_lblDonatTime);
    statusBar()->addWidget(m_lblStatusbarMessage);
    statusBar()->addWidget(m_lblDonatDbInfo);
//    statusBar()->showMessage(tr("Ready"));
}
// Create Donat main form toolbars
void FrmDonatMenu2::createFrmDonatToolBars()
{
}

// Create Donat main form actions
void FrmDonatMenu2::createFrmDonatActions()
{
    // [File]
    m_actExit = new QAction(tr("C&lose"), this);
    m_actExit->setShortcuts(QKeySequence::Quit);
    m_actExit->setStatusTip(tr("Exit the application"));
    m_actExit->setIcon(QIcon::fromTheme("application-exit"));
    connect(m_actExit, SIGNAL(triggered()), this, SLOT(close()));
    // [Zaporka]
    m_actPromijenaZaporke = new QAction(tr("&Zaporka"), this);
    m_actPromijenaZaporke->setStatusTip(tr("Promijena korisničke zaporke"));
    m_actPromijenaZaporke->setIcon(QIcon::fromTheme("security-high"));
    connect(m_actPromijenaZaporke, SIGNAL(triggered()), this, SLOT(on_actionPromijenaZaporke_triggered()));
    // [Sifarnik]
    m_actTitula = new QAction(tr("T&itula"), this);
    m_actTitula->setStatusTip(tr("Pregled svih titula"));
    m_actModemi = new QAction(tr("&Modemi"), this);
    m_actModemi->setStatusTip(tr("Pregled svih modema"));
    m_actKonAgenti = new QAction(tr("KON - &AGENTI"), this);
    m_actKonAgenti->setStatusTip(tr("Pregled svih Kontaknih grupa i agenata"));
    m_actKonTehnologija = new QAction(tr("KON - &TEHNOLOGIJA"), this);
    m_actKonTehnologija->setStatusTip(tr("Pregled svih kontaktnih tehnologija"));
    m_actKonHelp = new QAction(tr("KON - &HELP"), this);
    m_actKonHelp->setStatusTip(tr("Pregled svih mogućih kontaknih asistencija"));
    m_actKonZdrawko = new QAction(tr("KON - &Zdravko"), this);
    m_actKonZdrawko->setStatusTip(tr("Pregled svih zadržavanja korisnika"));
    m_actKonAnkete = new QAction(tr("KON - A&NKETE"), this);
    m_actKonAnkete->setStatusTip(tr("Pregled svih kontaktnih anketa"));
    m_actKonTht = new QAction(tr("KON - &THT"), this);
    m_actKonTht->setStatusTip(tr("Pregled Kontakte T-HT organizacije"));
    m_actKonOstalo = new QAction(tr("KON - &OSTALO"), this);
    m_actKonOstalo->setStatusTip(tr("Pregled svih ostalih kontaknih šifri"));
    // [Odrzavanje]
    m_actAzurirajRipote = new QAction(tr("Ažuriraj &Ripote"), this);
    m_actAzurirajRipote->setStatusTip(tr("Update svih Crytal Report-a"));
    m_actAzurirajRipote->setIcon(QIcon::fromTheme("software-update-available"));
    m_actAvayaRegistracija = new QAction(tr("&Avaya registracija"), this);
    m_actAvayaRegistracija->setStatusTip(tr("Direktno spajanje na softphone uređaje"));
    m_actMojeRole = new QAction(tr("&Moje role"), this);
    m_actMojeRole->setStatusTip(tr("Pregled DONAT rola za korisnika"));
    m_actMojeRole->setIcon(QIcon::fromTheme("security-low"));
    connect(m_actMojeRole, SIGNAL(triggered()), this, SLOT(on_actionMojeRole_triggered()));
    // [About]
    m_actAbout = new QAction(tr("&O programu"), this);
    m_actAbout->setStatusTip(tr("O DONAT klijentu"));
    m_actAbout->setIcon(QIcon::fromTheme("help-about"));
    connect(m_actAbout, SIGNAL(triggered()), this, SLOT(on_actionAbout_triggered()));

    connect(m_wgDonatSearch->m_btnDonatTrazi,
            SIGNAL(clicked()),
            this,
            SLOT(on_actionDonatTrazi_clicked()));
    connect(m_wgDonatSearch->m_cboDonatSearch,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_cboFltSearchMode_currentIndexChanged(int)));
    connect(m_wgDonatStranke->m_grdDonatStranke,
            SIGNAL(itemPressed(QTableWidgetItem*)),
            this,
            SLOT(on_grdDonatStranke_itemPressed(QTableWidgetItem*)));
    connect(m_wgDonatImovina->m_treeStrankaGrupaImovine,
                SIGNAL(itemPressed(QTreeWidgetItem*, int)),
                this,
                SLOT(on_treeStrankaGrupaImovine_itemPressed(QTreeWidgetItem*, int)));
    connect(m_wgDonatImovina->m_treeStrankaImovina,
                SIGNAL(itemPressed(QTreeWidgetItem*, int)),
                this,
                SLOT(on_treeStrankaImovina_itemPressed(QTreeWidgetItem*, int)));
    connect(m_wgDonatStranke->m_btnStrankaPregledZahtjeva,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnStrankaPregledZahtjeva_clicked()));
    connect(m_wgDonatStranke->m_btnStrankaPregledUgovora,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnStrankaPregledUgovora_clicked()));
    connect(m_wgDonatImovina->m_btnStrankaUgovorneObveze,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnStrankaPregledUgovora_clicked()));

    // [Dokumenti Donat menu]
    connect(m_wgDonatToolBar->m_btnZahtjevMax23,
            SIGNAL(clicked()),
            this,
            SLOT(on_actionDokumentiZahtjevMax23_clicked()));
    connect(m_wgDonatToolBar->m_btnCpeOprema,
            SIGNAL(clicked()),
            this,
            SLOT(on_actionDokumentiCpeOprema_clicked()));
    connect(m_wgDonatToolBar->m_btnPregled,
            SIGNAL(clicked()),
            this,
            SLOT(on_actionPregledSporazumaDetaljno_clicked()));

    // [Stranka Donat menu]
    connect(m_wgDonatToolBar->m_btnFizickaOsoba,
            SIGNAL(clicked()),
            this,
            SLOT(on_actionFizickaOsoba_clicked()));
    connect(m_wgDonatToolBar->m_btnPravnaOsoba,
            SIGNAL(clicked()),
            this,
            SLOT(on_actionPravnaOsoba_clicked()));
    connect(m_wgDonatToolBar->m_btnOcv,
            SIGNAL(clicked()),
            this,
            SLOT(on_actionStrankaOcv_clicked()));


}

// Clearform data
void FrmDonatMenu2::clearDonatSearchResults()
{
    m_wgDonatStranke->m_grdDonatStranke->clearContents();
    m_wgDonatStranke->m_grdDonatStranke->setRowCount(0);

    m_wgDonatSearch->m_lstUlogeStranaka->clear();
    m_wgDonatSearch->m_lblOsnoveUlogeTitle->clear();

	m_wgDonatStranke->m_txtStrankaLoyaltyId->clear();
	m_wgDonatStranke->m_txtStrankaLoyaltyValidniBodovi->clear();
	m_wgDonatStranke->m_txtStrankaLoyaltyPotencijalniBodovi->clear();

    m_wgDonatStranke->m_txtStrankaZastupnik->clear();
    m_wgDonatStranke->m_btnStrankaZatupnik2->setEnabled(false);

    m_wgDonatStranke->m_txtStrankaAdslStatus->clear();
    m_wgDonatStranke->m_txtStrankaMaxtvStatus->clear();

    m_wgDonatStranke->m_lblDonatStrankaMessages->clear();

    m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa"));
    m_wgDonatImovina->m_cboStrankaImovinaKlase->clear();
    m_wgDonatImovina->m_treeStrankaGrupaImovine->clear();
    m_wgDonatImovina->m_txtStrankaGrupaImovineId->clear();
    m_wgDonatImovina->m_txtStrankaUgovorneObveze->clear();
    m_wgDonatImovina->m_imgStrankaUgovorneObveze->clear();
    m_wgDonatImovina->m_cboStrankaImovinaKlase->disconnect(SIGNAL(currentIndexChanged(int)));

    m_wgDonatImovina->m_txtStrankaImovinaId->clear();
    m_wgDonatImovina->m_treeStrankaImovina->clear();
    m_wgDonatImovina->m_txtStrankaImovinaStatus->clear();
    m_wgDonatImovina->m_lstStrankaImovinaStatus->clear();

    m_iKupacId = 0;
    m_iStrankaId = 0;

    m_iGrupaImovineId = 0;
    m_iGrupaImovineIsStatus = 0;

    m_iImovinaId = 0;
    m_iImovinaIdStatus = 0;

}
void FrmDonatMenu2::clearDonatStranka()
{
	m_wgDonatStranke->m_txtStrankaLoyaltyId->clear();
	m_wgDonatStranke->m_txtStrankaLoyaltyValidniBodovi->clear();
	m_wgDonatStranke->m_txtStrankaLoyaltyPotencijalniBodovi->clear();

    m_wgDonatStranke->m_txtStrankaZastupnik->clear();
    m_wgDonatStranke->m_btnStrankaZatupnik2->setEnabled(false);

    m_wgDonatStranke->m_txtStrankaAdslStatus->clear();
    m_wgDonatStranke->m_txtStrankaMaxtvStatus->clear();

    m_wgDonatStranke->m_lblDonatStrankaMessages->clear();

    m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa"));
    m_wgDonatImovina->m_cboStrankaImovinaKlase->clear();
    m_wgDonatImovina->m_treeStrankaGrupaImovine->clear();
    m_wgDonatImovina->m_txtStrankaGrupaImovineId->clear();
    m_wgDonatImovina->m_txtStrankaUgovorneObveze->clear();
    m_wgDonatImovina->m_imgStrankaUgovorneObveze->clear();
    m_wgDonatImovina->m_cboStrankaImovinaKlase->disconnect(SIGNAL(currentIndexChanged(int)));

    m_wgDonatImovina->m_txtStrankaImovinaId->clear();
    m_wgDonatImovina->m_treeStrankaImovina->clear();
    m_wgDonatImovina->m_txtStrankaImovinaStatus->clear();
    m_wgDonatImovina->m_lstStrankaImovinaStatus->clear();

    m_iGrupaImovineId = 0;
    m_iGrupaImovineIsStatus = 0;

    m_iImovinaId = 0;
    m_iImovinaIdStatus = 0;
}

// [ Donat Search ]
void FrmDonatMenu2::traziDonatKorisnikaPoNazivu()
{
    int iBrojac = 0;

    string strSqlStatement;
    strSqlStatement.append("BEGIN P_VRATI_PREGLED_STRANKE_NOVI(:naziv, :mjesto_id_par, :mjesto, :ulica_id_par, :ulica, :akt, :brojac); END;");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setString(1, m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
        sqlStatement->setNull(2, OCCISTRING);
        sqlStatement->setNull(3, OCCISTRING);
        sqlStatement->setNull(4, OCCISTRING);
        sqlStatement->setNull(5, OCCISTRING);
        sqlStatement->setNull(6, OCCIINT);
        sqlStatement->registerOutParam(7, OCCIINT);
        sqlStatement->executeUpdate();
        iBrojac = sqlStatement->getInt(7);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iBrojac == 0)
    {
        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
        return;
    }

    strSqlStatement.erase();
    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append(" FROM TEMP_STRANKE_FILTER WHERE BROJAC < ");
    strSqlStatement.append(cttl::itos(iBrojac));
    strSqlStatement.append(" ORDER BY BROJAC");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_wgDonatStranke->m_grdDonatStranke->rowCount();
            m_wgDonatStranke->m_grdDonatStranke->insertRow(row);
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 0, new QTableWidgetItem(QString::number(rs->getUInt(1))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 3, new QTableWidgetItem(QString::number(rs->getUInt(4))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getUInt(6))));
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
void FrmDonatMenu2::traziDonatKorisnikaPoBrojuTelefona()
{
	string strSqlStatement;
	strSqlStatement.append("SELECT DISTINCT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
	strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
	strSqlStatement.append("FROM   V_PREGLED_STRANKE_TELBR ");
	strSqlStatement.append("WHERE TEL_BROJ = '");
	strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
	strSqlStatement.append("'");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_wgDonatStranke->m_grdDonatStranke->rowCount();
            m_wgDonatStranke->m_grdDonatStranke->insertRow(row);
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 0, new QTableWidgetItem(QString::number(rs->getUInt(1))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 3, new QTableWidgetItem(QString::number(rs->getUInt(4))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getUInt(6))));
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
void FrmDonatMenu2::traziDonatKorisnikaPoJmbg()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append("FROM   V_PREGLED_STRANKE_MBR ");
    strSqlStatement.append("WHERE LPAD(MBR, 13, '0') = LPAD('");
    strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
    strSqlStatement.append("', 13, '0')");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_wgDonatStranke->m_grdDonatStranke->rowCount();
            m_wgDonatStranke->m_grdDonatStranke->insertRow(row);
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 0, new QTableWidgetItem(QString::number(rs->getUInt(1))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 3, new QTableWidgetItem(QString::number(rs->getUInt(4))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getUInt(6))));
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
void FrmDonatMenu2::traziDonatKorisnikaPoOib()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append("FROM   V_PREGLED_STRANKE_OIB ");
    strSqlStatement.append("WHERE LPAD(BROJ_ISPRAVE, 13, '0') = LPAD('");
    strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
    strSqlStatement.append("', 13, '0')");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_wgDonatStranke->m_grdDonatStranke->rowCount();
            m_wgDonatStranke->m_grdDonatStranke->insertRow(row);
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 0, new QTableWidgetItem(QString::number(rs->getUInt(1))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 3, new QTableWidgetItem(QString::number(rs->getUInt(4))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getUInt(6))));
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
void FrmDonatMenu2::traziDonatKorisnikaPoUlogaStrankeId()
{
	string strSqlStatement;
	strSqlStatement.append("SELECT ROOT_STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
	strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, DECODE(TIP_STRANKE1,'Privatni',1,2) TSTRANKE1_ID ");
	strSqlStatement.append("FROM   KONTAKTI WHERE ACCOUNT_ID = ");
	strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_wgDonatStranke->m_grdDonatStranke->rowCount();
            m_wgDonatStranke->m_grdDonatStranke->insertRow(row);
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 0, new QTableWidgetItem(QString::number(rs->getUInt(1))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 3, new QTableWidgetItem(QString::number(rs->getUInt(4))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getUInt(6))));
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
void FrmDonatMenu2::traziDonatKorisnikaPoTicketId()
{
    std::list<unsigned int> lstGupaImovineId;

    string strSqlStatement;
    strSqlStatement.append("SELECT /*+ rule*/ P.ID ");
    strSqlStatement.append("FROM  ORDER_2 O, POSLOVNI_PROCESI P ");
    strSqlStatement.append("WHERE \"TicketId\" = '");
    strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
    strSqlStatement.append("' AND O.\"Id\" = P.PROCES_ID");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            unsigned int iGrupaImovineId = rs->getUInt(1);
            lstGupaImovineId.push_back(iGrupaImovineId);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(lstGupaImovineId.empty())
    {
        QMessageBox::information(this, tr("DONAT - Customer search"),
                                    tr("Ne postoji Ticket_id!"),
                                    QMessageBox::Close);

        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
        return;
    }

    string strGrupaImovineId;
    list<unsigned int>::const_iterator itGrupaImovineId;
    for(itGrupaImovineId=lstGupaImovineId.begin(); itGrupaImovineId!=lstGupaImovineId.end(); ++itGrupaImovineId)
    {
        if(!strGrupaImovineId.empty())
        {
            strGrupaImovineId.append(", ");
        }
        strGrupaImovineId.append(cttl::itos(*itGrupaImovineId));
    }

    strSqlStatement.erase();
    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append("FROM  DONAT.V_PREGLED_STRANKE_TELBR ");
    strSqlStatement.append("WHERE GIMOVINE_ID IN (");
    strSqlStatement.append(strGrupaImovineId);
    strSqlStatement.append(")");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_wgDonatStranke->m_grdDonatStranke->rowCount();
            m_wgDonatStranke->m_grdDonatStranke->insertRow(row);
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 0, new QTableWidgetItem(QString::number(rs->getUInt(1))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 3, new QTableWidgetItem(QString::number(rs->getUInt(4))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getUInt(6))));
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    lstGupaImovineId.clear();

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}
void FrmDonatMenu2::traziDonatKorisnikaPoAssetId()
{
	string strSqlStatement;
	strSqlStatement.append("SELECT DISTINCT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
	strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
	strSqlStatement.append("FROM   V_PREGLED_STRANKE_TELBR ");
	strSqlStatement.append("WHERE GIMOVINE_ID = ");
	strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_wgDonatStranke->m_grdDonatStranke->rowCount();
            m_wgDonatStranke->m_grdDonatStranke->insertRow(row);
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 0, new QTableWidgetItem(QString::number(rs->getUInt(1))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 3, new QTableWidgetItem(QString::number(rs->getUInt(4))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_wgDonatStranke->m_grdDonatStranke->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getUInt(6))));
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

// [ Customer data ]
void FrmDonatMenu2::popuniStrankaUlogeStranaka()
{
	m_wgDonatSearch->m_lstUlogeStranaka->clear();

	if(m_iStrankaId == 0)
	{
		return;
	}

	m_wgDonatSearch->m_lblOsnoveUlogeTitle->setText(tr("Osnovne uloge"));

	string strSqlStatement;
	strSqlStatement.append("SELECT ");
	strSqlStatement.append(" ULSTRANKE_ID, NAZIV_ULSTR, FORMATIRANA_ADRESA, FORMATIRANI_NAZIV, TULSTRANKE_ID ");
	strSqlStatement.append("FROM ");
	strSqlStatement.append(" HIJERARHIJA_STR_ADRESE h1 ");
	strSqlStatement.append("WHERE ");
	strSqlStatement.append(cttl::itos(m_iStrankaId));
	strSqlStatement.append(" IN (h1.ROOT_STRANKA_ID) ");
	strSqlStatement.append("AND h1.TULSTRANKE_ID IN (1, 11) ");
	strSqlStatement.append("UNION ALL ");
	strSqlStatement.append("SELECT ");
	strSqlStatement.append(" ULSTRANKE_ID, NAZIV_ULSTR, FORMATIRANA_ADRESA, FORMATIRANI_NAZIV, TULSTRANKE_ID ");
	strSqlStatement.append("FROM ");
	strSqlStatement.append("  HIJERARHIJA_STR_ADRESE h2 ");
	strSqlStatement.append("WHERE ");
	strSqlStatement.append(cttl::itos(m_iStrankaId));
	strSqlStatement.append(" IN (h2.ROOT_STRANKA_ID) ");
	strSqlStatement.append("AND h2.TULSTRANKE_ID NOT IN (1, 11, 13, 15) ");
	strSqlStatement.append("ORDER BY ");
	strSqlStatement.append("  2");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QListWidgetItem *listWidgetItem = new QListWidgetItem();
            string strUlogaStrankeId = cttl::getStrAsONumber(rs->getNumber(1));
            QString strUlogaStrankeNaziv;
            strUlogaStrankeNaziv.append(QString::fromStdString(strUlogaStrankeId));
            strUlogaStrankeNaziv.append(tr(" - "));
            strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(2)));
            strUlogaStrankeNaziv.append(tr(" - "));
            strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(4)));
            strUlogaStrankeNaziv.append(tr(" ... "));
            strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(3)));
            listWidgetItem->setText(strUlogaStrankeNaziv);
            listWidgetItem->setToolTip(strUlogaStrankeNaziv);
            m_wgDonatSearch->m_lstUlogeStranaka->addItem(listWidgetItem);
            if(rs->getUInt(5) == 1) m_iKupacId = atoll(strUlogaStrankeId.c_str());
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
void FrmDonatMenu2::popuniStrankaZastupnika()
{
	if(m_iKupacId == 0)
	{
		return;
	}

	bool bPopuniKontaktTelefon = false;
	string strKorisnikId;
	string strKorisnikTip;
	string strKorisnikNaziv;
	string strKorisnikNazivDop;

	string strSqlStatement;
	strSqlStatement.append("SELECT R.KOR_ID, R.KOR_TIP, R.KOR_NAZ, R.KOR_NAZ_DOP FROM PS_FIRME P,PS_HEAD R WHERE ");
	strSqlStatement.append(cttl::itos(m_iKupacId));
	strSqlStatement.append("  IN (P.FIR_ID, P.FIR_NAD_ID) AND R.FIR_ID = P.FIR_NAD_ID ");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strKorisnikId = rs->getString(1);
            strKorisnikTip = rs->getString(2);
            strKorisnikNaziv = rs->getString(3);
            strKorisnikNazivDop = rs->getString(4);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }


    string strZastupnik;
    if(strKorisnikTip == "T-COM ZASTUPNIK"
            || strKorisnikTip == "T-MOB ZASTUPNIK"
            || strKorisnikTip == "T-SAVJETNIK")
    {
        strZastupnik.append(strKorisnikTip);
        strZastupnik.append(" ... ");
        strZastupnik.append(strKorisnikNaziv);
        bPopuniKontaktTelefon = true;
    }
    else if(strKorisnikTip == "T-CENTAR")
    {
        strZastupnik.append(strKorisnikTip);
    }
    else if(strKorisnikTip == "T-PARTNER")
    {
        strZastupnik.append(strKorisnikTip);
        strZastupnik.append(" ... ");
        strZastupnik.append(strKorisnikNazivDop);
    }

	if(bPopuniKontaktTelefon == true)
	{
		string strNaziv;
		string strTelefon = "-";
		string strFax = "-";
		string strEmail = "-";

		strSqlStatement.erase();
		strSqlStatement.append("SELECT NAZIV, NVL(TELEFON, '-') TELEFON, NVL(FAX, '-') FAX, NVL(EMAIL, '-') EMAIL FROM KORISNICI WHERE KORISNIK_ID = '");
		strSqlStatement.append(strKorisnikId);
		strSqlStatement.append("' ");
		sqlStatement->setSQL(strSqlStatement);

		try
		{
			ResultSet *rs = sqlStatement->executeQuery();
			if(rs->next())
			{
				strNaziv = rs->getString(1);
				strTelefon = rs->getString(2);
				strFax = rs->getString(3);
				strEmail = rs->getString(4);
			}
			sqlStatement->closeResultSet(rs);
		}
		catch(SQLException &ex)
		{
			QMessageBox::critical(this, tr("DONAT - Database Error"),
										   QString::fromStdString(ex.getMessage()),
										   QMessageBox::Close);
		}

		if(strTelefon != "-")
		{
			strZastupnik.append(" ... ");
			strZastupnik.append(strTelefon);
		}
		if(strEmail != "-")
		{
			if(strTelefon == "-")
			{
				strZastupnik.append(" ... ");
				strZastupnik.append(strEmail);
			}
			else
			{
				strZastupnik.append(" ... ");
				strZastupnik.append(strEmail);
			}
		}

	}

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    m_wgDonatStranke->m_txtStrankaZastupnik->setText(QString::fromStdString(strZastupnik));
}
void FrmDonatMenu2::popuniStrankaLoyalty()
{
	m_wgDonatStranke->m_txtStrankaLoyaltyId->clear();
	m_wgDonatStranke->m_txtStrankaLoyaltyValidniBodovi->clear();
	m_wgDonatStranke->m_txtStrankaLoyaltyPotencijalniBodovi->clear();

	unsigned int iLoyaltyId = 0;

	string strSqlStatement;
	strSqlStatement.append("SELECT ULSTRANKE_ID FROM HIJERARHIJA_STR_ADRESE WHERE ");
	strSqlStatement.append(cttl::itos(m_iStrankaId));
	strSqlStatement.append("  IN (ROOT_STRANKA_ID) AND TULSTRANKE_ID = 13 ORDER BY TULSTRANKE_ID ");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iLoyaltyId = rs->getUInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

	if(iLoyaltyId == 0)
	{
		g_DonatConn->terminateStatement(sqlStatement);
		strSqlStatement.erase();
		return;
	}

	m_wgDonatStranke->m_txtStrankaLoyaltyId->setText(QString::number(iLoyaltyId));

    // Loyality Status i razlog
    string strLoyaltyNaziv;
    int iStatusId = 0;

    strSqlStatement.erase();
    strSqlStatement.append("SELECT P.STATUS_ID, P.RAZLOGDEAKT_ID, NVL(R.NAZIV,'-') NAZIV FROM ULOGE_STRANAKA P, RAZLOZI_DEAKTIVACIJE R WHERE P.ULSTRANKE_ID =");
    strSqlStatement.append(cttl::itos(iLoyaltyId));
    strSqlStatement.append("  AND R.RAZLOGDEAKT_ID(+) = P.RAZLOGDEAKT_ID ");

    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iStatusId = rs->getUInt(1);
            strLoyaltyNaziv = rs->getString(3);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iStatusId == 0)
    {
        QString strLoyaltyRazlogiStatus;
        strLoyaltyRazlogiStatus.append(QString::number(iStatusId));
        strLoyaltyRazlogiStatus.append(tr(" - "));
        strLoyaltyRazlogiStatus.append(QString::fromStdString(strLoyaltyNaziv));
        m_wgDonatStranke->m_txtStrankaLoyaltyId->setToolTip(strLoyaltyRazlogiStatus);
    }

    // Validni bodovi
    int iValidniBodovi = 0;
    strSqlStatement.erase();
    strSqlStatement.append("SELECT nvl(SUM(IZNOS_BODOVA),0) BODOVI FROM STANJE_LP WHERE TBODLP_ID=1 AND LOYALTY_ID = ");
    strSqlStatement.append(cttl::itos(iLoyaltyId));

    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iValidniBodovi = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    m_wgDonatStranke->m_txtStrankaLoyaltyValidniBodovi->setText(QString::number(iValidniBodovi));

    // Potencijalni bodovi
    int iPotencijalniBodovi = 0;
    strSqlStatement.erase();
    strSqlStatement.append("SELECT NVL(SUM(IZNOS_BODOVA),0) BODOVI FROM STANJE_LP WHERE TBODLP_ID = 3 AND LOYALTY_ID = ");
    strSqlStatement.append(cttl::itos(iLoyaltyId));

    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iPotencijalniBodovi = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    m_wgDonatStranke->m_txtStrankaLoyaltyPotencijalniBodovi->setText(QString::number(iPotencijalniBodovi));

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

}
void FrmDonatMenu2::popuniStrankaTarifniStatus()
{
	int iSmijeTarifa = 0;

	string strSqlStatement;
	strSqlStatement.append("SELECT SMIJE_LI_TARIFA(");
	strSqlStatement.append(cttl::itos(m_iKupacId));
	strSqlStatement.append(") SMIJE FROM DUAL ");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iSmijeTarifa = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iSmijeTarifa == 0)
    {
        m_wgDonatStranke->m_btnStrankaZatupnik2->setEnabled(false);
    }
    else
    {
        m_wgDonatStranke->m_btnStrankaZatupnik2->setEnabled(true);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}
void FrmDonatMenu2::popuniStrankaAdslStatus()
{
    m_wgDonatStranke->m_txtStrankaAdslStatus->clear();

    string strTelefonskiBroj;
    try
    {
        strTelefonskiBroj = m_strTelefonskiBroj.substr(0, 10);
    }
    catch(exception& e)
    {
        strTelefonskiBroj.clear();
    }
    if(strTelefonskiBroj.empty())
    {
        return;
    }

    int iStatus = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT STATUS FROM TEL_STATUS WHERE TEL_BROJ = '");
    strSqlStatement.append(strTelefonskiBroj);
    strSqlStatement.append("' ");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iStatus = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iStatus == 0)
    {
        m_wgDonatStranke->m_txtStrankaAdslStatus->setText(tr("Potrebno ažurirati podatke u DIS-u"));
    }
    else
    {
        string strDescription;

        strSqlStatement.erase();
        strSqlStatement.append("SELECT DESCRIPTION FROM A_DSL_MESSAGES WHERE A_DSL_MESSAGE_ID = ");
        strSqlStatement.append(cttl::itos(iStatus));

        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            if(rs->next())
            {
                strDescription = rs->getString(1);
            }
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }

        m_wgDonatStranke->m_txtStrankaAdslStatus->setText(QString::fromStdString(strDescription));
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}
void FrmDonatMenu2::popuniStrankaIptvStatus()
{
    m_wgDonatStranke->m_txtStrankaMaxtvStatus->clear();

    string strTelefonskiBroj;
    try
    {
        strTelefonskiBroj = m_strTelefonskiBroj.substr(0, 10);
    }
    catch(exception& e)
    {
        strTelefonskiBroj.clear();
    }
    if(strTelefonskiBroj.empty())
    {
        return;
    }

    int iIptv = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT NVL(IPTV,-1) IPTV FROM TEL_STATUS WHERE TEL_BROJ = '");
    strSqlStatement.append(strTelefonskiBroj);
    strSqlStatement.append("' ");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iIptv = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iIptv == 0)
    {
        m_wgDonatStranke->m_txtStrankaMaxtvStatus->setText(tr("Potrebno ažurirati podatke u DIS-u"));
    }
    else
    {
        string strDescription;

        strSqlStatement.erase();
        strSqlStatement.append("SELECT NVL(MESSAGE_DESCR,'-') MESSAGE_DESCR FROM A_DSL_IPTV_MESSAGES WHERE MESSAGE_ID = ");
        strSqlStatement.append(cttl::itos(iIptv));

        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            if(rs->next())
            {
                strDescription = rs->getString(1);
            }
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }

        m_wgDonatStranke->m_txtStrankaMaxtvStatus->setText(QString::fromStdString(strDescription));
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}
void FrmDonatMenu2::popuniStrankaPenali()
{
    if (m_iGrupaImovineId == 0)
        return;

	string strSqlStatement;
	strSqlStatement.append("SELECT NVL(MAX(IND),0) IND FROM PRIKAZ_UG_OBVEZE WHERE GIMOVINE_ID = ");
	strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    int iUgovornaObvezaInd = 0;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iUgovornaObvezaInd = rs->getInt(1);
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

    if(iUgovornaObvezaInd == 0)
        return;

    m_wgDonatImovina->m_txtStrankaUgovorneObveze->setText(
                tr("UGOVORNA OBVEZA  ... ")
                + QString::number(iUgovornaObvezaInd)
                + tr(" DANA"));

    if(iUgovornaObvezaInd < 30)
    {
        m_wgDonatImovina->m_imgStrankaUgovorneObveze->setPixmap(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zuti.JPG")));
    }
    else if(iUgovornaObvezaInd < 120)
    {
        m_wgDonatImovina->m_imgStrankaUgovorneObveze->setPixmap(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
    }
    else if(iUgovornaObvezaInd > 119)
    {
        m_wgDonatImovina->m_imgStrankaUgovorneObveze->setPixmap(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
    }
}

void FrmDonatMenu2::popuniStrankaPoruke()
{
    m_wgDonatStranke->m_lblDonatStrankaMessages->clear();

    std::list<string> lstPoruke;

	string strSqlStatement;
	strSqlStatement.append("SELECT SQL_TEXT, TIP FROM PORUKE");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            string strSqlStatementToDo;
            strSqlStatementToDo.append(rs->getString(1));
            switch(rs->getInt(2))
            {
                case 1:	 // GrupaImovineId
                {
                    strSqlStatementToDo.append(cttl::itos(m_iGrupaImovineId));
                    break;
                }
                case 2:  // KUPAC_ID
                {
                    strSqlStatementToDo.append(cttl::itos(m_iKupacId));
                    break;
                }
            }
            lstPoruke.push_back(strSqlStatementToDo);
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

    list<string>::const_iterator strPoruka;
    for(strPoruka=lstPoruke.begin(); strPoruka!=lstPoruke.end(); ++strPoruka)
    {
        popuniStrankaPoruku(*strPoruka);
    }
    m_wgDonatStranke->m_lblDonatStrankaMessages->setToolTip(m_wgDonatStranke->m_lblDonatStrankaMessages->text());
}
void FrmDonatMenu2::popuniStrankaPoruku(string strSqlStatement)
{
	string strPoruka;

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strPoruka = rs->getString(1);
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

    strPoruka = cttl::trim(strPoruka);
    if(strPoruka.empty())
    {
        return;
    }

    if(m_wgDonatStranke->m_lblDonatStrankaMessages->text().isEmpty())
    {
        m_wgDonatStranke->m_lblDonatStrankaMessages->setText(QString::fromStdString(strPoruka));
    }
    else
    {
        m_wgDonatStranke->m_lblDonatStrankaMessages->text().append(tr(" ... "));
        m_wgDonatStranke->m_lblDonatStrankaMessages->text().append(QString::fromStdString(strPoruka));
    }
}
void FrmDonatMenu2::popuniStrankaSveKlase()
{
	int iBrojac = 0;

	string strSqlStatement;
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setAutoCommit(true);

	if(m_SearchMode == TraziPoBrojTelefona)
	{
		strSqlStatement.append("DELETE FROM TEMP_ASSET_FILTER");
		sqlStatement->setSQL(strSqlStatement);

		try
		{
			sqlStatement->executeUpdate();
		}
		catch(SQLException &ex)
		{
			QMessageBox::critical(this, tr("DONAT - Database Error"),
										   QString::fromStdString(ex.getMessage()),
										   QMessageBox::Close);
		}

		m_wgDonatImovina->m_cboStrankaImovinaKlase->clear();
		m_wgDonatImovina->m_fraStrankaImovinaKlasaTitle->setVisible(false);

	}
	else
	{
		strSqlStatement.append("BEGIN P_POVEZANI_KUPCI(:kupac_id_par, :brojac); END;");
		sqlStatement->setSQL(strSqlStatement);

		try
		{
			Number nProva = cttl::getONumber(m_iKupacId);
			sqlStatement->setNumber(1, nProva);
			sqlStatement->registerOutParam(2, OCCIINT);
			sqlStatement->executeUpdate();
			iBrojac = sqlStatement->getInt(2);
		}
		catch(SQLException &ex)
		{
			QMessageBox::critical(this, tr("DONAT - Database Error"),
										   QString::fromStdString(ex.getMessage()),
										   QMessageBox::Close);
		}

		if(iBrojac == 0)
		{
			m_wgDonatImovina->m_fraStrankaImovinaKlasaTitle->setVisible(false);
			g_DonatConn->terminateStatement(sqlStatement);
			strSqlStatement.erase();
			return;
		}

		m_wgDonatImovina->m_cboStrankaImovinaKlase->clear();
		m_wgDonatImovina->m_cboStrankaImovinaKlase->addItem(tr("Sve klase"), QVariant(tr("Sve klase")));

		string strKlasa;
		int iKlasaCount = 0;

		strSqlStatement.erase();
		strSqlStatement.append("SELECT TEL_LIN_ID, COUNT(TEL_LIN_ID) BROJ FROM TEMP_ASSET_FILTER GROUP BY TEL_LIN_ID ORDER BY TEL_LIN_ID DESC ");
		sqlStatement->setSQL(strSqlStatement);

		try
		{
			ResultSet *rs = sqlStatement->executeQuery();
			while(rs->next())
			{
				strKlasa = rs->getString(1);
				iKlasaCount = rs->getInt(2);
				m_wgDonatImovina->m_cboStrankaImovinaKlase->addItem(
							QString::fromStdString(strKlasa) +
							tr(" ... ") +
							QString::number(iKlasaCount),
							QVariant(QString::fromStdString(strKlasa)));

			}
			sqlStatement->closeResultSet(rs);
		}
		catch(SQLException &ex)
		{
			QMessageBox::critical(this, tr("DONAT - Database Error"),
										   QString::fromStdString(ex.getMessage()),
										   QMessageBox::Close);
		}

		if(iBrojac > 10)
		{
			m_wgDonatImovina->m_fraStrankaImovinaKlasaTitle->setVisible(true);
			m_wgDonatImovina->m_fraStrankaGrupaImovineTitle->setVisible(false);
			m_bPunoGrupaImovine = true;
			connect(m_wgDonatImovina->m_cboStrankaImovinaKlase,
					SIGNAL(currentIndexChanged(int)),
					this,
					SLOT(on_cboStrankaImovinaKlase_currentIndexChanged(int)));
		}
		else
		{
			m_wgDonatImovina->m_fraStrankaImovinaKlasaTitle->setVisible(false);
			m_wgDonatImovina->m_fraStrankaGrupaImovineTitle->setVisible(true);
			m_bPunoGrupaImovine = false;
			m_wgDonatImovina->m_cboStrankaImovinaKlase->disconnect(SIGNAL(currentIndexChanged(int)));
		}
	}

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    popuniStrankaGrupeImovine();
}
void FrmDonatMenu2::popuniStrankaGrupeImovine()
{
	bool bTelBrojIsNumber;
    int iTelBroj = m_wgDonatSearch->m_txtDonatSearch->text().toInt(&bTelBrojIsNumber);

	switch(m_SearchMode)
	{
		case TraziPoNazivKorisnika:
		{
			if(bTelBrojIsNumber == true)
			{
				string strSqlStatement;
				strSqlStatement.append("SELECT GIMOVINE_ID, SLOG_STATUS FROM B_HIJERARHIJA WHERE TEL_BROJ = '");
				strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
				strSqlStatement.append("' AND KUPAC_ID IN (SELECT ULSTRANKE_ID FROM ULOGE_STRANAKA WHERE ROOT_STRANKA_ID = ");
				strSqlStatement.append(cttl::itos(m_iStrankaId));
				strSqlStatement.append(") AND SLOG_STATUS >= 0 AND SLOG_STATUS < 11 ");
				strSqlStatement.append("ORDER BY SLOG_STATUS DESC, TEL_LIN_ID DESC ");
				Statement *sqlStatement = g_DonatConn->createStatement();
				sqlStatement->setSQL(strSqlStatement);

				try
				{
					ResultSet *rs = sqlStatement->executeQuery();
					if(rs->next())
					{
						m_iGrupaImovineId = rs->getUInt(1);
						m_iGrupaImovineIsStatus = rs->getUInt(2);
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

				if(m_iGrupaImovineId != 0)
				{
					m_strTelefonskiBroj = m_wgDonatSearch->m_txtDonatSearch->text().toStdString();
				}
				switch(m_iGrupaImovineIsStatus)
				{
					case 0 :
					{
						m_iGrupaImovineIsTip = 4;
						break;
					}
					case 1 :
					{
						m_iGrupaImovineIsTip = 2;
						break;
					}
					case 2 :
					{
						m_iGrupaImovineIsTip = 1;
						break;
					}
				}
				if(m_iGrupaImovineIsStatus > 4)
				{
					m_iGrupaImovineIsTip = 3;
				}
				popuniZaGrupuImovine();
			}
			else
			{
				popuniSveGrupeImovine();
			}
			break;
		}
		case TraziPoBrojTelefona:
		{
			string strSqlStatement;
			strSqlStatement.append("SELECT GIMOVINE_ID, SLOG_STATUS FROM B_HIJERARHIJA WHERE TEL_BROJ = '");
			strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
			strSqlStatement.append("' AND KUPAC_ID = ");
			strSqlStatement.append(cttl::itos(m_iKupacId));
			strSqlStatement.append(" AND SLOG_STATUS >= 0 AND SLOG_STATUS < 11 ");
			strSqlStatement.append("ORDER BY SLOG_STATUS DESC, TEL_LIN_ID DESC ");
			Statement *sqlStatement = g_DonatConn->createStatement();
			sqlStatement->setSQL(strSqlStatement);

			try
			{
				ResultSet *rs = sqlStatement->executeQuery();
				if(rs->next())
				{
					m_iGrupaImovineId = rs->getUInt(1);
					m_iGrupaImovineIsStatus = rs->getUInt(2);
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

			if(m_iGrupaImovineId != 0)
			{
				m_strTelefonskiBroj = m_wgDonatSearch->m_txtDonatSearch->text().toStdString();
			}
			switch(m_iGrupaImovineIsStatus)
			{
				case 0 :
				{
					m_iGrupaImovineIsTip = 4;
					break;
				}
				case 1 :
				{
					m_iGrupaImovineIsTip = 2;
					break;
				}
				case 2 :
				{
					m_iGrupaImovineIsTip = 1;
					break;
				}
			}
			if(m_iGrupaImovineIsStatus > 4)
			{
				m_iGrupaImovineIsTip = 3;
			}
			popuniZaGrupuImovine();
			break;
		}
		case TraziPoJmbg:
		{
			popuniSveGrupeImovine();
			break;
		}
		case TraziPoOib:
		{
			popuniSveGrupeImovine();
			break;
		}
		case TraziPoUlogaStrankeId:
		{
			popuniSveGrupeImovine();
			break;
		}
		case TraziPoTicketId:
		{
			if(bTelBrojIsNumber == false)
			{
				return;
			}
			string strSqlStatement;
			strSqlStatement.append("SELECT /*+ RULE */ GI.GIMOVINE_ID, GI.STATUS_ID SLOG_STATUS FROM (SELECT /*+ RULE */ MAX(P.ID) GIMOVINE_ID FROM ORDER_2 O, POSLOVNI_PROCESI P  WHERE \"TicketId\"='");
			strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
			strSqlStatement.append("' AND O.\"Id\"=P.PROCES_ID) O,GRUPE_IMOVINE GI WHERE GI.GIMOVINE_ID = O.GIMOVINE_ID");
			Statement *sqlStatement = g_DonatConn->createStatement();
			sqlStatement->setSQL(strSqlStatement);

			try
			{
				ResultSet *rs = sqlStatement->executeQuery();
				if(rs->next())
				{
					m_iGrupaImovineId = rs->getUInt(1);
					m_iGrupaImovineIsStatus = rs->getUInt(2);
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

			switch(m_iGrupaImovineIsStatus)
			{
				case 0 :
				{
					m_iGrupaImovineIsTip = 4;
					break;
				}
				case 1 :
				{
					m_iGrupaImovineIsTip = 2;
					break;
				}
				case 2 :
				{
					m_iGrupaImovineIsTip = 1;
					break;
				}
			}
			if(m_iGrupaImovineIsStatus > 4)
			{
				m_iGrupaImovineIsTip = 3;
			}
			popuniZaGrupuImovine();
			break;
		}
		case TraziPoAssetId:
		{
			if(bTelBrojIsNumber == false)
			{
				return;
			}

			string strSqlStatement;
			strSqlStatement.append("SELECT GIMOVINE_ID, SLOG_STATUS FROM B_HIJERARHIJA WHERE GIMOVINE_ID = ");
			strSqlStatement.append(m_wgDonatSearch->m_txtDonatSearch->text().toStdString());
			strSqlStatement.append(" AND SLOG_STATUS >= 0 AND SLOG_STATUS < 11 ");
			strSqlStatement.append("ORDER BY SLOG_STATUS DESC, TEL_LIN_ID DESC ");
			Statement *sqlStatement = g_DonatConn->createStatement();
			sqlStatement->setSQL(strSqlStatement);

			try
			{
				ResultSet *rs = sqlStatement->executeQuery();
				if(rs->next())
				{
					m_iGrupaImovineId = rs->getUInt(1);
					m_iGrupaImovineIsStatus = rs->getUInt(2);
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

			switch(m_iGrupaImovineIsStatus)
			{
				case 0 :
				{
					m_iGrupaImovineIsTip = 4;
					break;
				}
				case 1 :
				{
					m_iGrupaImovineIsTip = 2;
					break;
				}
				case 2 :
				{
					m_iGrupaImovineIsTip = 1;
					break;
				}
			}
			if(m_iGrupaImovineIsStatus > 4)
			{
				m_iGrupaImovineIsTip = 3;
			}
			popuniZaGrupuImovine();

			break;
		}
		case TraziPoGrupna:
		{
			popuniSveGrupeImovine();
			break;
		}
		case TraziPoHijerahija:
		{
			popuniSveGrupeImovine();
			break;
		}
		default :
		{
			popuniSveGrupeImovine();
			break;
		}
	}
}
void FrmDonatMenu2::popuniZaGrupuImovine()
{
	// 1. izbriši tree za GrupeImovine
	// 2. izbrisi tree za Imovinu
	// 3. izbrisi listview za Status imovine
	// 4. izbriši status za ADSL

	if(m_iGrupaImovineId == 0)
	{
		return;
	}
	if(m_iGrupaImovineIsStatus == 0)
	{
		return;
	}

	unsigned int iDodatniAsssetId;
	bool bJeAdsl = getIsGrupaImovineIdMAXadsl(m_iGrupaImovineId);
	if(bJeAdsl == true)
	{
		iDodatniAsssetId = vratiBasicAsset(m_iGrupaImovineId);
	}
	else
	{
		iDodatniAsssetId = vratiAdslAsset(m_iGrupaImovineId);
	}

	string strGrupeImovine;
	strGrupeImovine.append("(");
	strGrupeImovine.append(cttl::itos(m_iGrupaImovineId));
	if(iDodatniAsssetId != 0)
	{
		strGrupeImovine.append(", ");
		strGrupeImovine.append(cttl::itos(iDodatniAsssetId));
	}
	strGrupeImovine.append(")");
	popuniGrupeImovine1(strGrupeImovine);
	popuniUlogeStrankeZaTelefon();
}
void FrmDonatMenu2::popuniUlogeStrankeZaTelefon()
{
	if(m_iGrupaImovineId == 0)
	{
		return;
	}

	m_wgDonatSearch->m_lblOsnoveUlogeTitle->clear();
	m_wgDonatSearch->m_lstUlogeStranaka->clear();

	long long iAssetId = 0;
	int iTipVeze = 0;
	string strTrajanje;
	// Privremeni vlasnik
	string strSqlStatement;
	strSqlStatement.append("SELECT NVL(MAX(GIMOVINE_ID1),-1) ASSET, MAX(TIP_VEZE_IMOV_ID) STAT2 ");
	strSqlStatement.append(",NVL(TO_CHAR(MAX(DATUM_OD),'DD.MM.YYYY'),'0') TRAJANJE ");
	strSqlStatement.append(" FROM VEZE_IMOVINE WHERE GIMOVINE_ID2 = ");
	strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
	strSqlStatement.append(" AND TIP_VEZE_IMOV_ID IN (5,6)");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iAssetId = cttl::getLongLongAsONumber(rs->getNumber(1));
            iTipVeze = rs->getInt(2);
            strTrajanje = rs->getString(3);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iAssetId == -1)
    {
        if(m_wgDonatImovina->m_treeStrankaGrupaImovine->topLevelItemCount() > 0)
        {
            m_wgDonatSearch->m_lblOsnoveUlogeTitle->setText(m_wgDonatImovina->m_treeStrankaGrupaImovine->currentItem()->text(0));
//            m_wgDonatSearch->m_lblOsnoveUlogeTitle->setText(m_wgDonatImovina->m_treeStrankaGrupaImovine->selectedItems().first()->text(0));
        }
    }
    else
    {
        if(iTipVeze == 5)
        {
            m_wgDonatSearch->m_lblOsnoveUlogeTitle->setText(
                        m_wgDonatImovina->m_treeStrankaGrupaImovine->currentItem()->text(0)
                        + tr("   Priv. vlasnik (rent) ")
                        + QString::fromStdString(strTrajanje));
        }
        else
        {
            m_wgDonatSearch->m_lblOsnoveUlogeTitle->setText(
                        m_wgDonatImovina->m_treeStrankaGrupaImovine->currentItem()->text(0)
                        + tr("   Priv. vlasnik (obitelj) ")
                        + QString::fromStdString(strTrajanje));
        }
    }

	long long iGrupaImovineInstalacija = 0;
	string strUlogeGrupeImovine = vratiUlogeGrupeImovine(m_iGrupaImovineId);
	if(strUlogeGrupeImovine.empty())
	{
		return;
	}
	strSqlStatement.erase();
	strSqlStatement.append("SELECT ULSTRANKE_ID, NAZIV_ULSTR, FORMATIRANA_ADRESA, FORMATIRANI_NAZIV, TULSTRANKE_ID");
	strSqlStatement.append(" FROM HIJERARHIJA_STR_ADRESE2 WHERE ULSTRANKE_ID IN ");
	strSqlStatement.append(strUlogeGrupeImovine);
	strSqlStatement.append(" ORDER BY TULSTRANKE_ID ");
	sqlStatement->setSQL(strSqlStatement);
	try
	{
		ResultSet *rs = sqlStatement->executeQuery();
		while(rs->next())
		{
			QListWidgetItem *listWidgetItem = new QListWidgetItem();
			string strUlogaStrankeId = cttl::getStrAsONumber(rs->getNumber(1));
			QString strUlogaStrankeNaziv;
			strUlogaStrankeNaziv.append(QString::fromStdString(strUlogaStrankeId));
			strUlogaStrankeNaziv.append(tr(" - "));
			strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(2)));
			strUlogaStrankeNaziv.append(tr(" - "));
			strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(4)));
			strUlogaStrankeNaziv.append(tr(" ... "));
			strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(3)));
			listWidgetItem->setText(strUlogaStrankeNaziv);
			listWidgetItem->setToolTip(strUlogaStrankeNaziv);
			m_wgDonatSearch->m_lstUlogeStranaka->addItem(listWidgetItem);
			if(rs->getUInt(5) == 4) iGrupaImovineInstalacija = atoll(strUlogaStrankeId.c_str());
		}
		sqlStatement->closeResultSet(rs);
	}
	catch(SQLException &ex)
	{
		QMessageBox::critical(this, tr("DONAT - Database Error"),
									   QString::fromStdString(ex.getMessage()),
									   QMessageBox::Close);
	}


	if(iGrupaImovineInstalacija == 0)
	{
		return;
	}
	strSqlStatement.erase();
	strSqlStatement.append("SELECT ULSTRANKE_ID, NAZIV_ULSTR, FORMATIRANA_ADRESA, FORMATIRANI_NAZIV, TULSTRANKE_ID ");
	strSqlStatement.append("FROM HIJERARHIJA_STR_ADRESE2 WHERE TULSTRANKE_ID=12 AND ULSTRANKE_NAD_ID =");
	strSqlStatement.append(cttl::itos(iGrupaImovineInstalacija));
	sqlStatement->setSQL(strSqlStatement);
	try
	{
		ResultSet *rs = sqlStatement->executeQuery();
		while(rs->next())
		{
			QListWidgetItem *listWidgetItem = new QListWidgetItem();
			string strUlogaStrankeId = cttl::getStrAsONumber(rs->getNumber(1));
			QString strUlogaStrankeNaziv;
			strUlogaStrankeNaziv.append(QString::fromStdString(strUlogaStrankeId));
			strUlogaStrankeNaziv.append(tr(" - "));
			strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(2)));
			strUlogaStrankeNaziv.append(tr(" - "));
			strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(4)));
			strUlogaStrankeNaziv.append(tr(" ... "));
			strUlogaStrankeNaziv.append(QString::fromStdString(rs->getString(3)));
			listWidgetItem->setText(strUlogaStrankeNaziv);
			listWidgetItem->setToolTip(strUlogaStrankeNaziv);
			m_wgDonatSearch->m_lstUlogeStranaka->addItem(listWidgetItem);
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
// [ Grupa Imovine ]
void FrmDonatMenu2::popuniSveGrupeImovine()
{
	string strGrupeImovineIn;
	strGrupeImovineIn = vratiPovezaniKupci(m_iKupacId);
	if(strGrupeImovineIn.empty())
	{
		return;
	}

	string strSqlStatement;
	strSqlStatement.append("SELECT /*+ RULE */ B1, B2, TEL_BROJ, GI.GIMOVINE_ID, TEL_LIN_ID, IMOVINA_ID, SLOG_STATUS,");
	strSqlStatement.append(" TO_CHAR(BH.DATUM_DO,'DD.MM.RR') DATUM_DO ");
	strSqlStatement.append("FROM B_HIJERARHIJA BH,GRUPE_IMOVINE GI WHERE BH.GIMOVINE_ID=GI.GIMOVINE_ID ");
	strSqlStatement.append(" AND GI.GIMOVINE_ID IN ");
	strSqlStatement.append(strGrupeImovineIn);
	strSqlStatement.append(" AND B1>0 AND B2 != 9 ");
	strSqlStatement.append(" AND GI.STATUS_ID>0 AND SLOG_STATUS>0 ");
	strSqlStatement.append(" AND NOT (B1!=1 AND TEL_BROJ='0') ");
	strSqlStatement.append(" ORDER BY B1,SLOG_STATUS DESC,TEL_BROJ,TEL_LIN_ID DESC ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

	QList<QTreeWidgetItem *> listGrupaImovine;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemGrupaImovine = new QTreeWidgetItem();
            itemGrupaImovine->setText(1, QString::number(rs->getUInt(4)));
            itemGrupaImovine->setText(0, QString::fromStdString(rs->getString(3)) + tr("    ") + QString::fromStdString(rs->getString(5)));
            itemGrupaImovine->setText(2, QString::number(rs->getInt(1)));
            itemGrupaImovine->setText(3, QString::number(rs->getInt(2)));
            itemGrupaImovine->setText(4, QString::fromStdString(rs->getString(3)));
            itemGrupaImovine->setText(5, QString::fromStdString(rs->getString(5)));
            itemGrupaImovine->setText(6, QString::number(rs->getUInt(6)));
            itemGrupaImovine->setText(7, QString::number(rs->getInt(7)));
            itemGrupaImovine->setText(8, QString::fromStdString(rs->getString(8)));
            listGrupaImovine.append(itemGrupaImovine);
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

    if(!listGrupaImovine.empty())
    {
        bool bImaNonBasicAssets = false;
        for(int i = 0; i < listGrupaImovine.size(); ++i)
        {
             if(listGrupaImovine.at(i)->text(2).toInt() == 1)
             {
                if(listGrupaImovine.at(i)->text(5) == "ADSL" ||
                   listGrupaImovine.at(i)->text(5) == "MaxTV" ||
                   listGrupaImovine.at(i)->text(5) == "MaxPhone" ||
                   listGrupaImovine.at(i)->text(5) == "HT net" ||
                   listGrupaImovine.at(i)->text(5) == "ISP - davatelj Internet usluga")
                {
                    bImaNonBasicAssets = true;
                    continue;
                }

                if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                {
                   listGrupaImovine.at(i)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                }
                if(listGrupaImovine.at(i)->text(7).toInt() > 1)
                {
                    listGrupaImovine.at(i)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                }
                // Zastavica
                int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(1).toUInt());
                if(iZastavica != 0)
                {
                    if(iZastavica < 30)
                    {
                        listGrupaImovine.at(i)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                    }
                    else
                    {
                        if(iZastavica < 120)
                        {
                            listGrupaImovine.at(i)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        }
                        else
                        {
                            listGrupaImovine.at(i)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        }
                    }
                }
                // Churn
                string strRizik = vratiChurnPhoneRizik(listGrupaImovine.at(i)->text(4).toStdString());
                if(strRizik == "L")
                {
                    listGrupaImovine.at(i)->setIcon(10, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/sve_rijeseni.gif")));
                }
                else if (strRizik == "M") {
                    listGrupaImovine.at(i)->setIcon(10, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/rijeseni_nerijeseni.gif")));
                }
                else if (strRizik == "H") {
                    listGrupaImovine.at(i)->setIcon(10, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/sve_nerijeseni.gif")));
                }
             }
             else
             {
                 if(listGrupaImovine.at(i)->text(5) == "ADSL" ||
                    listGrupaImovine.at(i)->text(5) == "MaxTV" ||
                    listGrupaImovine.at(i)->text(5) == "MaxPhone" ||
                    listGrupaImovine.at(i)->text(5) == "HT net" ||
                    listGrupaImovine.at(i)->text(5) == "ISP - davatelj Internet usluga")
                 {
                     bImaNonBasicAssets = true;
                     continue;
                 }

                 for(int j = 0; j < listGrupaImovine.size(); ++j)
                 {
                     if(j == i)
                     {
                         continue;
                     }
                     if(listGrupaImovine.at(j)->text(1).toUInt() == listGrupaImovine.at(i)->text(1).toUInt())
                     {
                         listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(4));
                         if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                         {
                             listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                         }
                         listGrupaImovine.at(j)->addChild(listGrupaImovine.at(i));
                     }
                 }
             }

             if(m_iGrupaImovineId == 0 && listGrupaImovine.at(i)->text(4) == m_wgDonatSearch->m_txtDonatSearch->text())
             {
                 listGrupaImovine.at(i)->setSelected(true);
                 m_wgDonatImovina->m_txtStrankaGrupaImovineId->setText(listGrupaImovine.at(i)->text(1));
                 m_iGrupaImovineId = listGrupaImovine.at(i)->text(1).toUInt();
                 m_iGrupaImovineIsStatus = listGrupaImovine.at(i)->text(7).toUInt();
             }
         }

        if(bImaNonBasicAssets == true)
        {
            for(int i = 0; i < listGrupaImovine.size(); ++i)
            {
                if(listGrupaImovine.at(i)->text(5) == "ADSL")
                {
                    unsigned int iAdslAsset = vratiBasicAsset(listGrupaImovine.at(i)->text(1).toUInt());
                    for(int j = 0; j < listGrupaImovine.size(); ++j)
                    {
                        if(j == i)
                        {
                            continue;
                        }
                        if(listGrupaImovine.at(j)->text(1).toUInt() == iAdslAsset)
                        {
                            listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(5));
                            if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                            }
                            if(listGrupaImovine.at(i)->text(7).toInt() > 1)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                            }
                            // Zastavica
                            int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(1).toUInt(), "ADSL");
                            if(iZastavica != 0)
                            {
                                if(iZastavica < 30)
                                {
                                    listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                                }
                                else
                                {
                                    if(iZastavica < 120)
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                    else
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                }
                            }
                            listGrupaImovine.at(j)->addChild(listGrupaImovine.at(i));
                        }
                    }
                }
                if(listGrupaImovine.at(i)->text(5) == "MaxPhone")
                {
                    unsigned int iAdslAsset = vratiBasicAsset(listGrupaImovine.at(i)->text(1).toUInt());
                    for(int j = 0; j < listGrupaImovine.size(); ++j)
                    {
                        if(j == i)
                        {
                            continue;
                        }
                        if(listGrupaImovine.at(j)->text(1).toUInt() == iAdslAsset)
                        {
                            listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(5) + tr("    ") + listGrupaImovine.at(i)->text(4));
                            if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                            }
                            if(listGrupaImovine.at(i)->text(7).toInt() > 1)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                            }
                            // Zastavica
                            int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(1).toUInt(), "MaxPhone");
                            if(iZastavica != 0)
                            {
                                if(iZastavica < 30)
                                {
                                    listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                                }
                                else
                                {
                                    if(iZastavica < 120)
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                    else
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                }
                            }
                            listGrupaImovine.at(j)->addChild(listGrupaImovine.at(i));
                        }
                    }
                }
                if(listGrupaImovine.at(i)->text(5) == "MaxTV")
                {
                    unsigned int iAdslAsset = vratiBasicAsset(listGrupaImovine.at(i)->text(1).toUInt());
                    for(int j = 0; j < listGrupaImovine.size(); ++j)
                    {
                        if(j == i)
                        {
                            continue;
                        }
                        if(listGrupaImovine.at(j)->text(1).toUInt() == iAdslAsset)
                        {
                            listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(5) + tr("    ") + listGrupaImovine.at(i)->text(4));
                            if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                            }
                            if(listGrupaImovine.at(i)->text(7).toInt() > 1)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                            }
                            // Zastavica
                            int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(1).toUInt(), "MaxTV");
                            if(iZastavica != 0)
                            {
                                if(iZastavica < 30)
                                {
                                    listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                                }
                                else
                                {
                                    if(iZastavica < 120)
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                    else
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                }
                            }
                            listGrupaImovine.at(j)->addChild(listGrupaImovine.at(i));
                        }
                    }
                }
            }
        }

        if(m_iGrupaImovineId == 0)
        {
            m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa"));
            listGrupaImovine.first()->setSelected(true);
            m_wgDonatImovina->m_txtStrankaGrupaImovineId->setText(listGrupaImovine.first()->text(1));
            m_iGrupaImovineId = listGrupaImovine.first()->text(1).toUInt();
            m_iGrupaImovineIsStatus = listGrupaImovine.first()->text(7).toUInt();
            m_wgDonatImovina->m_treeStrankaGrupaImovine->insertTopLevelItems(0, listGrupaImovine);
            m_wgDonatImovina->m_treeStrankaGrupaImovine->setCurrentItem(listGrupaImovine.first());
            m_wgDonatImovina->m_treeStrankaGrupaImovine->expandAll();
        }
        else
        {
            m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa : ") + QString::number(m_iGrupaImovineId));
            m_wgDonatImovina->m_treeStrankaGrupaImovine->insertTopLevelItems(0, listGrupaImovine);
            m_wgDonatImovina->m_treeStrankaGrupaImovine->setCurrentItem(listGrupaImovine.first());
            m_wgDonatImovina->m_treeStrankaGrupaImovine->expandAll();
        }

        popuniSveImovine();
    }
    else
    {
        popuniSveGrupeImovineIskljucene();
    }
}
void FrmDonatMenu2::popuniSveGrupeImovineIskljucene()
{
	string strGrupeImovineIn;
	strGrupeImovineIn = vratiPovezaniKupci(m_iKupacId);
	if(strGrupeImovineIn.empty())
	{
		return;
	}

	string strSqlStatement;
	strSqlStatement.append("SELECT /*+ RULE */ B1, B2, TEL_BROJ, GI.GIMOVINE_ID, TEL_LIN_ID, IMOVINA_ID, SLOG_STATUS,");
	strSqlStatement.append(" TO_CHAR(BH.DATUM_DO,'DD.MM.RR') DATUM_DO ");
	strSqlStatement.append("FROM B_HIJERARHIJA BH,GRUPE_IMOVINE GI WHERE BH.GIMOVINE_ID=GI.GIMOVINE_ID ");
	strSqlStatement.append(" AND GI.GIMOVINE_ID IN ");
	strSqlStatement.append(strGrupeImovineIn);
	strSqlStatement.append(" AND B1>0 AND B2 != 9 ");
	strSqlStatement.append(" AND GI.STATUS_ID=0 AND SLOG_STATUS>=0 ");
	strSqlStatement.append(" AND NOT (B1!=1 AND TEL_BROJ='0') ");
	strSqlStatement.append(" ORDER BY B1, TEL_BROJ ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

	QList<QTreeWidgetItem *> listGrupaImovine;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemGrupaImovine = new QTreeWidgetItem();
            itemGrupaImovine->setText(1, QString::number(rs->getUInt(4)));
            itemGrupaImovine->setText(0, QString::fromStdString(rs->getString(3)) + tr("    ") + QString::fromStdString(rs->getString(5)));
            itemGrupaImovine->setText(2, QString::number(rs->getInt(1)));
            itemGrupaImovine->setText(3, QString::number(rs->getInt(2)));
            itemGrupaImovine->setText(4, QString::fromStdString(rs->getString(3)));
            itemGrupaImovine->setText(5, QString::fromStdString(rs->getString(5)));
            itemGrupaImovine->setText(6, QString::number(rs->getUInt(6)));
            itemGrupaImovine->setText(7, QString::number(rs->getInt(7)));
            itemGrupaImovine->setText(8, QString::fromStdString(rs->getString(8)));
            itemGrupaImovine->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
            listGrupaImovine.append(itemGrupaImovine);
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

    if(!listGrupaImovine.empty())
    {
        listGrupaImovine.first()->setSelected(true);
        m_wgDonatImovina->m_txtStrankaGrupaImovineId->setText(listGrupaImovine.first()->text(1));
        m_iGrupaImovineId = listGrupaImovine.first()->text(1).toUInt();
        m_iGrupaImovineIsStatus = listGrupaImovine.first()->text(7).toUInt();
        m_wgDonatImovina->m_treeStrankaGrupaImovine->insertTopLevelItems(0, listGrupaImovine);
        m_wgDonatImovina->m_treeStrankaGrupaImovine->setCurrentItem(listGrupaImovine.first());
        m_wgDonatImovina->m_treeStrankaGrupaImovine->expandAll();
        m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa : ") + QString::number(m_iGrupaImovineId));

        popuniSveImovine();
    }
}
void FrmDonatMenu2::popuniGrupeImovine1(const string strGrupeImovine)
{
	string strSqlStatement;
	strSqlStatement.append("SELECT /*+ RULE */ B1, B2, TEL_BROJ, GI.GIMOVINE_ID, TEL_LIN_ID, IMOVINA_ID, SLOG_STATUS");
	strSqlStatement.append(" , TO_CHAR(BH.DATUM_DO,'DD.MM.RR') DATUM_DO ");
	strSqlStatement.append(" FROM B_HIJERARHIJA BH, GRUPE_IMOVINE GI WHERE BH.GIMOVINE_ID = GI.GIMOVINE_ID ");
	strSqlStatement.append(" AND GI.GIMOVINE_ID IN ");
	strSqlStatement.append(strGrupeImovine);
//	switch(m_iGrupaImovineIsStatus)
//	{
//		case 1:
//		{
//			strSqlStatement.append(" AND GI.STATUS_ID = 2 AND SLOG_STATUS BETWEEN 1 AND 2 ");
//			break;
//		}
//		case 2:
//		{
//			strSqlStatement.append(" AND GI.STATUS_ID BETWEEN 1 AND 2 AND SLOG_STATUS = 1 ");
//			break;
//		}
//		case 3:
//		{
//			strSqlStatement.append(" AND GI.STATUS_ID > 4 AND SLOG_STATUS > 4 ");
//			break;
//		}
//		case 4:
//		{
//			strSqlStatement.append(" AND GI.STATUS_ID = 0 AND SLOG_STATUS = 0 ");
//			break;
//		}
//	}
	strSqlStatement.append(" AND B1>0 AND B2 != 9 ");
	strSqlStatement.append(" AND NOT (B1!=1 AND TEL_BROJ='0' AND TEL_LIN_ID<>'ADSL') ");
	strSqlStatement.append(" ORDER BY B1,SLOG_STATUS DESC,TEL_BROJ,TEL_LIN_ID DESC ");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

	QList<QTreeWidgetItem *> listGrupaImovine;

	try
	{
		ResultSet *rs = sqlStatement->executeQuery();
		while(rs->next())
		{
			QTreeWidgetItem *itemGrupaImovine = new QTreeWidgetItem();
			itemGrupaImovine->setText(1, QString::number(rs->getUInt(4)));
			itemGrupaImovine->setText(0, QString::fromStdString(rs->getString(3)) + tr("    ") + QString::fromStdString(rs->getString(5)));
			itemGrupaImovine->setText(2, QString::number(rs->getInt(1)));
			itemGrupaImovine->setText(3, QString::number(rs->getInt(2)));
			itemGrupaImovine->setText(4, QString::fromStdString(rs->getString(3)));
			itemGrupaImovine->setText(5, QString::fromStdString(rs->getString(5)));
			itemGrupaImovine->setText(6, QString::number(rs->getUInt(6)));
			itemGrupaImovine->setText(7, QString::number(rs->getInt(7)));
			itemGrupaImovine->setText(8, QString::fromStdString(rs->getString(8)));
			listGrupaImovine.append(itemGrupaImovine);
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

    if(!listGrupaImovine.empty())
    {
        bool bImaNonBasicAssets = false;
        for(int i = 0; i < listGrupaImovine.size(); ++i)
        {
             if(listGrupaImovine.at(i)->text(2).toInt() == 1)
             {
                if(listGrupaImovine.at(i)->text(5) == "ADSL" ||
                   listGrupaImovine.at(i)->text(5) == "MaxTV" ||
                   listGrupaImovine.at(i)->text(5) == "MaxPhone" ||
                   listGrupaImovine.at(i)->text(5) == "HT net" ||
                   listGrupaImovine.at(i)->text(5) == "ISP - davatelj Internet usluga")
                {
                    bImaNonBasicAssets = true;
                    continue;
                }

                if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                {
                   listGrupaImovine.at(i)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                }
                if(listGrupaImovine.at(i)->text(7).toInt() > 1)
                {
                    listGrupaImovine.at(i)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                }
                // Zastavica
                int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(1).toUInt());
                if(iZastavica != 0)
                {
                    if(iZastavica < 30)
                    {
                        listGrupaImovine.at(i)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                    }
                    else
                    {
                        if(iZastavica < 120)
                        {
                            listGrupaImovine.at(i)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        }
                        else
                        {
                            listGrupaImovine.at(i)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        }
                    }
                }
                // Churn
                string strRizik = vratiChurnPhoneRizik(listGrupaImovine.at(i)->text(4).toStdString());
                if(strRizik == "L")
                {
                    listGrupaImovine.at(i)->setIcon(10, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/sve_rijeseni.gif")));
                }
                else if (strRizik == "M") {
                    listGrupaImovine.at(i)->setIcon(10, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/rijeseni_nerijeseni.gif")));
                }
                else if (strRizik == "H") {
                    listGrupaImovine.at(i)->setIcon(10, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/sve_nerijeseni.gif")));
                }
             }
             else
             {
                 if(listGrupaImovine.at(i)->text(5) == "ADSL" ||
                    listGrupaImovine.at(i)->text(5) == "MaxTV" ||
                    listGrupaImovine.at(i)->text(5) == "MaxPhone" ||
                    listGrupaImovine.at(i)->text(5) == "HT net" ||
                    listGrupaImovine.at(i)->text(5) == "ISP - davatelj Internet usluga")
                 {
                     bImaNonBasicAssets = true;
                     continue;
                 }

                 for(int j = 0; j < listGrupaImovine.size(); ++j)
                 {
                     if(j == i)
                     {
                         continue;
                     }
                     if(listGrupaImovine.at(j)->text(1).toUInt() == listGrupaImovine.at(i)->text(1).toUInt())
                     {
                         listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(4));
                         if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                         {
                             listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                         }
                         listGrupaImovine.at(j)->addChild(listGrupaImovine.at(i));
                     }
                 }
             }

             if(m_iGrupaImovineId == 0 && listGrupaImovine.at(i)->text(4) == m_wgDonatSearch->m_txtDonatSearch->text())
             {
                 listGrupaImovine.at(i)->setSelected(true);
                 m_wgDonatImovina->m_txtStrankaGrupaImovineId->setText(listGrupaImovine.at(i)->text(1));
                 m_iGrupaImovineId = listGrupaImovine.at(i)->text(1).toUInt();
                 m_iGrupaImovineIsStatus = listGrupaImovine.at(i)->text(7).toUInt();
             }
         }

        if(bImaNonBasicAssets == true)
        {
            for(int i = 0; i < listGrupaImovine.size(); ++i)
            {
                if(listGrupaImovine.at(i)->text(5) == "ADSL")
                {
                    unsigned int iAdslAsset = vratiBasicAsset(listGrupaImovine.at(i)->text(1).toUInt());
                    for(int j = 0; j < listGrupaImovine.size(); ++j)
                    {
                        if(j == i)
                        {
                            continue;
                        }
                        if(listGrupaImovine.at(j)->text(1).toUInt() == iAdslAsset)
                        {
                            listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(5));
                            if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                            }
                            if(listGrupaImovine.at(i)->text(7).toInt() > 1)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                            }
                            // Zastavica
                            int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(1).toUInt(), "ADSL");
                            if(iZastavica != 0)
                            {
                                if(iZastavica < 30)
                                {
                                    listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                                }
                                else
                                {
                                    if(iZastavica < 120)
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                    else
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                }
                            }
                            listGrupaImovine.at(j)->addChild(listGrupaImovine.at(i));
                        }
                    }
                }
                if(listGrupaImovine.at(i)->text(5) == "MaxPhone")
                {
                    unsigned int iAdslAsset = vratiBasicAsset(listGrupaImovine.at(i)->text(1).toUInt());
                    for(int j = 0; j < listGrupaImovine.size(); ++j)
                    {
                        if(j == i)
                        {
                            continue;
                        }
                        if(listGrupaImovine.at(j)->text(1).toUInt() == iAdslAsset)
                        {
                            listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(5) + tr("    ") + listGrupaImovine.at(i)->text(4));
                            if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                            }
                            if(listGrupaImovine.at(i)->text(7).toInt() > 1)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                            }
                            // Zastavica
                            int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(1).toUInt(), "MaxPhone");
                            if(iZastavica != 0)
                            {
                                if(iZastavica < 30)
                                {
                                    listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                                }
                                else
                                {
                                    if(iZastavica < 120)
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                    else
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                }
                            }
                            listGrupaImovine.at(j)->addChild(listGrupaImovine.at(i));
                        }
                    }
                }
                if(listGrupaImovine.at(i)->text(5) == "MaxTV")
                {
                    unsigned int iAdslAsset = vratiBasicAsset(listGrupaImovine.at(i)->text(1).toUInt());
                    for(int j = 0; j < listGrupaImovine.size(); ++j)
                    {
                        if(j == i)
                        {
                            continue;
                        }
                        if(listGrupaImovine.at(j)->text(1).toUInt() == iAdslAsset)
                        {
                            listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(5) + tr("    ") + listGrupaImovine.at(i)->text(4));
                            if(listGrupaImovine.at(i)->text(7).toInt() == 0)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                            }
                            if(listGrupaImovine.at(i)->text(7).toInt() > 1)
                            {
                                listGrupaImovine.at(j)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                            }
                            // Zastavica
                            int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(1).toUInt(), "MaxTV");
                            if(iZastavica != 0)
                            {
                                if(iZastavica < 30)
                                {
                                    listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                                }
                                else
                                {
                                    if(iZastavica < 120)
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                    else
                                    {
                                        listGrupaImovine.at(j)->setIcon(9, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                                    }
                                }
                            }
                            listGrupaImovine.at(j)->addChild(listGrupaImovine.at(i));
                        }
                    }
                }
            }
        }

        if(m_iGrupaImovineId == 0)
        {
            m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa"));
            listGrupaImovine.first()->setSelected(true);
            m_wgDonatImovina->m_txtStrankaGrupaImovineId->setText(listGrupaImovine.first()->text(1));
            m_iGrupaImovineId = listGrupaImovine.first()->text(1).toUInt();
            m_iGrupaImovineIsStatus = listGrupaImovine.first()->text(7).toUInt();
            m_wgDonatImovina->m_treeStrankaGrupaImovine->insertTopLevelItems(0, listGrupaImovine);
            m_wgDonatImovina->m_treeStrankaGrupaImovine->setCurrentItem(listGrupaImovine.first());
            m_wgDonatImovina->m_treeStrankaGrupaImovine->expandAll();
        }
        else
        {
            m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa : ") + QString::number(m_iGrupaImovineId));
            m_wgDonatImovina->m_treeStrankaGrupaImovine->insertTopLevelItems(0, listGrupaImovine);
            m_wgDonatImovina->m_treeStrankaGrupaImovine->setCurrentItem(listGrupaImovine.first());
            m_wgDonatImovina->m_treeStrankaGrupaImovine->expandAll();
        }

        popuniSveImovine();
    }
}
// [ Imovina ]
void FrmDonatMenu2::popuniSveImovine()
{
	if(m_iGrupaImovineId == 0)
	{
		return;
	}
//	if(m_iGrupaImovineIsTip == 0)
//	{
//		return;
//	}

	string strSqlStatement;
	strSqlStatement.append("SELECT I.IMOVINA_ID, I.NAD_IMOVINA_ID, I.STATUS_ID, I.NIVO, P.NAZIV ");
	strSqlStatement.append("FROM IMOVINA I, PRODUKTI P ");
	strSqlStatement.append("WHERE I.PRODUKT_ID = P.PRODUKT_ID ");
//	switch(m_iGrupaImovineIsTip)
//	{
//		case 1:
//		{
//			strSqlStatement.append(" AND I.STATUS_ID = 2 ");
//			break;
//		}
//		case 2:
//		{
//			strSqlStatement.append(" AND I.STATUS_ID BETWEEN 1 AND 2 ");
//			break;
//		}
//		case 3:
//		{
//			strSqlStatement.append(" AND I.STATUS_ID > 4 ");
//			break;
//		}
//		case 4:
//		{
//			strSqlStatement.append(" AND I.STATUS_ID = 0 ");
//			break;
//		}
//	}
	strSqlStatement.append(" AND I.NIVO>0 ");
	strSqlStatement.append(" AND GIMOVINE_ID = ");
	strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
	strSqlStatement.append(" AND P.GPRODUKATA_ID NOT IN (4, 31) ");
	strSqlStatement.append(" ORDER BY NIVO,IMOVINA_ID ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

	QList<QTreeWidgetItem *> listImovina;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemImovina = new QTreeWidgetItem();
            itemImovina->setText(0, QString::fromStdString(rs->getString(5)));
            itemImovina->setText(1, QString::number(rs->getUInt(1)));
            itemImovina->setText(2, QString::number(rs->getUInt(2)));
            itemImovina->setText(3, QString::number(rs->getInt(3)));
            itemImovina->setText(4, QString::number(rs->getInt(4)));
            itemImovina->setText(5, QString::fromStdString(rs->getString(5)));
            listImovina.append(itemImovina);
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

    if(!listImovina.empty())
    {
        for(int i = 0; i < listImovina.size(); ++i)
        {
             for(int j = 0; j < listImovina.size(); ++j)
             {
                 if(listImovina.at(j)->text(2).toUInt() == listImovina.at(i)->text(1).toUInt())
                 {
                     listImovina.at(i)->addChild(listImovina.at(j));
                 }
             }
        }

        for(int ii = 0; ii < listImovina.size(); ++ii)
        {
            if(listImovina.at(ii)->text(3).toInt() == 0)
            {
                listImovina.at(ii)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
            }

            popuniImovinaAtribute(listImovina.at(ii));
        }

        listImovina.first()->setSelected(true);
        m_wgDonatImovina->m_txtStrankaImovinaId->setText(listImovina.first()->text(1));
        m_iImovinaId = listImovina.first()->text(1).toUInt();
        m_iImovinaIdStatus = listImovina.first()->text(3).toInt();
        m_wgDonatImovina->m_treeStrankaImovina->insertTopLevelItems(0, listImovina);
        m_wgDonatImovina->m_treeStrankaImovina->setCurrentItem(listImovina.first());
//        m_wgDonatImovina->m_treeStrankaImovina->expandAll();
        m_wgDonatImovina->m_treeStrankaImovina->collapseAll();

        popuniImovinaStatus();
    }
}
void FrmDonatMenu2::popuniImovinaAtribute(QTreeWidgetItem *itemImovina)
{
	string strSqlStatement;
	strSqlStatement.append("SELECT ATRIBUT_ID, IMOVATR_ID, SHOWN_VALUE, NAZIV, TVRATR_ID, WWMS_NAZIV ");
	strSqlStatement.append("FROM V_IMOVINA_ATR WHERE IMOVINA_ID = ");
	strSqlStatement.append(itemImovina->text(1).toStdString());
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemImovinaAtributi = new QTreeWidgetItem(itemImovina);
            itemImovinaAtributi->setText(0, QString::fromStdString(rs->getString(4)) + tr(" ... ") + QString::fromStdString(rs->getString(3)));
            itemImovinaAtributi->setText(6, QString::number(rs->getUInt(2)));
            itemImovinaAtributi->setText(7, QString::number(rs->getUInt(1)));
            itemImovinaAtributi->setText(8, QString::fromStdString(rs->getString(3)));
            itemImovinaAtributi->setText(9, QString::fromStdString(rs->getString(4)));
            itemImovinaAtributi->setText(10, QString::number(rs->getInt(5)));
            itemImovinaAtributi->setText(11, QString::fromStdString(rs->getString(6)));
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
void FrmDonatMenu2::popuniImovinaStatus()
{
    if(m_iImovinaId == 0)
    {
        return;
    }
    m_wgDonatImovina->m_txtStrankaImovinaStatus->setText(tr("Grupe"));

	string strSqlStatement;
	strSqlStatement.append("SELECT GI.STATUS_ID, NVL(TO_CHAR(I2.DATUM_OD,'DD.MM.YYYY HH24:MI'),' ') DATUM_OD, ");
	strSqlStatement.append(" NVL(TO_CHAR(I2.DATUM_DO,'DD.MM.YYYY HH24:MI'),'0') DATUM_DO, ");
	strSqlStatement.append(" CASE WHEN GI.DATUM_SUSPENZIJE IS NOT NULL THEN ");
	strSqlStatement.append("   NVL(TO_CHAR(GI.DATUM_SUSPENZIJE,'DD.MM.YYYY HH24:MI'),'0') ELSE '0' END DATUM_SUSPENZIJE, ");
	strSqlStatement.append(" CASE WHEN GI.DATUM_RESUSPENZIJE IS NOT NULL THEN ");
	strSqlStatement.append("   NVL(TO_CHAR(GI.DATUM_RESUSPENZIJE,'DD.MM.YYYY HH24:MI'),'0') ELSE '0' END DATUM_RESUSPENZIJE, S.NAZIV STATUS ");
	strSqlStatement.append("FROM IMOVINA I, STATUS S, GRUPE_IMOVINE GI, IMOVINA I2 WHERE S.STATUS_ID=I.STATUS_ID AND I.GIMOVINE_ID=GI.GIMOVINE_ID ");
	strSqlStatement.append(" AND S.TABLICA='IMOVINA' AND I2.IMOVINA_ID=I.NAD_IMOVINA_ID AND I.IMOVINA_ID= ");
	strSqlStatement.append(cttl::itos(m_iImovinaId));
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            QListWidgetItem *listWidgetItem1 = new QListWidgetItem();
            listWidgetItem1->setText(tr("Status: ") + QString::fromStdString(rs->getString(6)));
            m_wgDonatImovina->m_lstStrankaImovinaStatus->addItem(listWidgetItem1);
            QListWidgetItem *listWidgetItem2 = new QListWidgetItem();
            listWidgetItem2->setText(tr("Aktiviran: ") + QString::fromStdString(rs->getString(2)));
            m_wgDonatImovina->m_lstStrankaImovinaStatus->addItem(listWidgetItem2);
            if(rs->getString(3) != "0")
            {
                QListWidgetItem *listWidgetItem3 = new QListWidgetItem();
                listWidgetItem3->setText(tr("Trajno iskopčan: ") + QString::fromStdString(rs->getString(2)));
                m_wgDonatImovina->m_lstStrankaImovinaStatus->addItem(listWidgetItem3);
            }
            else
            {
                if(rs->getString(4) != "0")
                {
                    QListWidgetItem *listWidgetItem4 = new QListWidgetItem();
                    listWidgetItem4->setText(tr("Priv.iskopčan: ") + QString::fromStdString(rs->getString(4)));
                    m_wgDonatImovina->m_lstStrankaImovinaStatus->addItem(listWidgetItem4);
                }
                if(rs->getString(5) != "0")
                {
                    QListWidgetItem *listWidgetItem5 = new QListWidgetItem();
                    listWidgetItem5->setText(tr("Pon.ukopčan: ") + QString::fromStdString(rs->getString(5)));
                    m_wgDonatImovina->m_lstStrankaImovinaStatus->addItem(listWidgetItem5);
                }
            }
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

// [ General Donat functions ]
// Vrati osnovni asset
unsigned int FrmDonatMenu2::vratiBasicAsset(const unsigned int iGrupaImovineId)
{
	unsigned int retValue = 0;
	string strSqlStatement;
	strSqlStatement.append("SELECT VRATI_BASIC_ASSET('");
	strSqlStatement.append(cttl::itos(iGrupaImovineId));
	strSqlStatement.append("') BROJ FROM DUAL ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getUInt(1);
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
    return retValue;
}
// Vrati ADSL asset
unsigned int FrmDonatMenu2::vratiAdslAsset(const unsigned int iGrupaImovineId)
{
	unsigned int retValue = 0;
	string strSqlStatement;
	strSqlStatement.append("SELECT VRATI_ADSL_ASSET('");
	strSqlStatement.append(cttl::itos(iGrupaImovineId));
	strSqlStatement.append("') BROJ FROM DUAL ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getUInt(1);
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
    return retValue;
}
// Vrati da li je Grupa Imovine ID ADSL
bool FrmDonatMenu2::getIsGrupaImovineIdMAXadsl(const unsigned int iGrupaImovineId)
{
	bool retValue = false;
	string strSqlStatement;
	strSqlStatement.append("SELECT JE_LI_ADSL('");
	strSqlStatement.append(cttl::itos(iGrupaImovineId));
	strSqlStatement.append("') BROJ FROM DUAL ");

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            string strJeLiAdsl = rs->getString(1);
            if(strJeLiAdsl == "A") retValue = true;
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        retValue = false;
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    return retValue;
}
// Vrati Donat povezani kupci za daljnje upite o GImovine
string FrmDonatMenu2::vratiPovezaniKupci(const unsigned int iKupacId)
{
	string retValue;
	string strSqlStatement;
	strSqlStatement.append("SELECT POVEZANI_KUPCI(");
	strSqlStatement.append(cttl::itos(iKupacId));
	strSqlStatement.append(") LISTA_ID FROM DUAL ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getString(1);
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
    return retValue;
}
// Vrati indikator ugovorne obveze
int FrmDonatMenu2::vratiIndikatorZaprikazUgovorneObveze(const unsigned int iGrupaImovineId, string strTip)
{
	int retValue = 0;
	string strSqlStatement;
	strSqlStatement.append("SELECT IND FROM PRIKAZ_UG_OBVEZE WHERE GIMOVINE_ID = ");
	strSqlStatement.append(cttl::itos(iGrupaImovineId));
	if(strTip.empty() == false)
	{
		strSqlStatement.append(" AND TIP = '");
		strSqlStatement.append(strTip);
		strSqlStatement.append("' ");
	}
	strSqlStatement.append(" ORDER BY IND DESC ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getInt(1);
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
    return retValue;
}
// Vrati rizik za preotimanje telefona
string FrmDonatMenu2::vratiChurnPhoneRizik(const string strPhoneNumber)
{
	string retValue;
	string strSqlStatement;
	strSqlStatement.append("SELECT RIZIK FROM CHURN_PHONE WHERE TEL_BROJ = '");
	strSqlStatement.append(strPhoneNumber);
	strSqlStatement.append("' ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getString(1);
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
    return retValue;
}
// Vrati uloge stranke za grupa imovine id
string FrmDonatMenu2::vratiUlogeGrupeImovine(const unsigned int iGrupaImovineId)
{
	string retValue;
	string strSqlStatement;
	strSqlStatement.append("SELECT ULOGE_GRUPE_IMOVINE(");
	strSqlStatement.append(cttl::itos(iGrupaImovineId));
	strSqlStatement.append(") ULOGE FROM DUAL ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getString(1);
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
    return retValue;
}

// [ Event Handlers ]
void FrmDonatMenu2::on_actionAbout_triggered()
{
    // Show Donat about form
    Log::FrmDonatAbout *frmAbout = new Log::FrmDonatAbout();
    frmAbout->exec();
    delete frmAbout;
}
void FrmDonatMenu2::on_actionPromijenaZaporke_triggered()
{
    // Show Donat user password change
    FrmDonatPasswordChange *frmDonatPasswordChange = new FrmDonatPasswordChange();
    frmDonatPasswordChange->exec();
    delete frmDonatPasswordChange;
}
void FrmDonatMenu2::on_actionMojeRole_triggered()
{
    // Show Donat user roles
    FrmDonatUserRole *frmDonatUserRoles = new FrmDonatUserRole();
    frmDonatUserRoles->exec();
    delete frmDonatUserRoles;
}

void FrmDonatMenu2::on_actionDonatTrazi_clicked()
{
    if(m_wgDonatSearch->m_txtDonatSearch->text().isEmpty())
    {
        return;
    }

    clearDonatSearchResults();

    setCursor(Qt::BusyCursor);

	switch(m_SearchMode)
	{
		case TraziPoNazivKorisnika:
		{
			bool bFltDonatSearchIsNumber;
            int iDonatSearchNumber = m_wgDonatSearch->m_txtDonatSearch->text().toInt(&bFltDonatSearchIsNumber);
			if(bFltDonatSearchIsNumber == true)
			{
				if(m_wgDonatSearch->m_txtDonatSearch->text().startsWith(tr("0")) == true)
				{
					m_wgDonatSearch->m_cboDonatSearch->setCurrentIndex(1);
					m_SearchMode = TraziPoBrojTelefona;
					traziDonatKorisnikaPoBrojuTelefona();
				}
				else
				{
					m_wgDonatSearch->m_cboDonatSearch->setCurrentIndex(6);
					m_SearchMode = TraziPoAssetId;
					traziDonatKorisnikaPoAssetId();
				}
			}
			else
			{
				traziDonatKorisnikaPoNazivu();
			}
			break;
		}
		case TraziPoBrojTelefona:
		{
			traziDonatKorisnikaPoBrojuTelefona();
			break;
		}
		case TraziPoJmbg:
		{
			traziDonatKorisnikaPoJmbg();
			break;
		}
		case TraziPoOib:
		{
			traziDonatKorisnikaPoOib();
			break;
		}
		case TraziPoUlogaStrankeId:
		{
			traziDonatKorisnikaPoUlogaStrankeId();
			break;
		}
		case TraziPoTicketId:
		{
			traziDonatKorisnikaPoTicketId();
			break;
		}
		case TraziPoAssetId:
		{
			traziDonatKorisnikaPoAssetId();
			break;
		}
		case TraziPoGrupna:
		{
			break;
		}
		case TraziPoHijerahija:
		{
			break;
		}
		default :
		{
			break;
		}
	}

	setCursor(Qt::ArrowCursor);
}
void FrmDonatMenu2::on_cboFltSearchMode_currentIndexChanged(int index)
{
    switch(index)
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
    m_wgDonatSearch->m_txtDonatSearch->setFocus();
}
void FrmDonatMenu2::on_cboStrankaImovinaKlase_currentIndexChanged(int index)
{
    m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa"));
    QVariant oKlasaNaziv =  m_wgDonatImovina->m_cboStrankaImovinaKlase->itemData(index);
    string strKlasaNaziv = oKlasaNaziv.toString().toStdString();
    if(strKlasaNaziv.empty()) return;

    if(strKlasaNaziv == "Sve klase")
    {
        for(int i = 0; i<m_wgDonatImovina->m_treeStrankaGrupaImovine->topLevelItemCount(); i++)
        {
            QTreeWidgetItem *item = m_wgDonatImovina->m_treeStrankaGrupaImovine->topLevelItem(i);
            item->setHidden(false);
            for(int j = 0; j<item->childCount(); j++)
            {
                QTreeWidgetItem *itemChild = item->child(j);
                itemChild->setHidden(false);
            }
        }
    }
    else
    {
        for(int i = 0; i<m_wgDonatImovina->m_treeStrankaGrupaImovine->topLevelItemCount(); i++)
        {
            QTreeWidgetItem *item = m_wgDonatImovina->m_treeStrankaGrupaImovine->topLevelItem(i);
            item->setHidden(true);
            for(int j = 0; j<item->childCount(); j++)
            {
                QTreeWidgetItem *itemChild = item->child(j);
                itemChild->setHidden(true);
            }
        }

        QList<QTreeWidgetItem *> listGrupaImovine = m_wgDonatImovina->m_treeStrankaGrupaImovine->findItems(
                    oKlasaNaziv.toString(),
                    Qt::MatchExactly,
                    5);
        for(int ii = 0; ii < listGrupaImovine.size(); ++ii)
        {
           listGrupaImovine.at(ii)->setHidden(false);
        }
    }
}

void FrmDonatMenu2::on_grdDonatStranke_itemPressed(QTableWidgetItem* itemDonatStranka)
{
    setCursor(Qt::BusyCursor);

    QVariant strankaId = m_wgDonatStranke->m_grdDonatStranke->item(itemDonatStranka->row(), 0)->text();
    m_iStrankaId = strankaId.toUInt();

	clearDonatStranka();
	popuniStrankaUlogeStranaka();
	popuniStrankaZastupnika();
	popuniStrankaLoyalty();
	popuniStrankaTarifniStatus();
	popuniStrankaSveKlase();

	popuniStrankaAdslStatus();
	popuniStrankaIptvStatus();
	popuniStrankaPenali();
	popuniStrankaPoruke();

	setCursor(Qt::ArrowCursor);
}
void FrmDonatMenu2::on_treeStrankaGrupaImovine_itemPressed(QTreeWidgetItem * itemGrupaImovine, int UNUSED(column))
{
    setCursor(Qt::BusyCursor);
    m_iGrupaImovineId = itemGrupaImovine->text(1).toUInt();
    m_iGrupaImovineIsStatus = itemGrupaImovine->text(7).toInt();
    m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa : ") + QString::number(m_iGrupaImovineId));
    m_wgDonatImovina->m_txtStrankaImovinaId->clear();
    m_wgDonatImovina->m_treeStrankaImovina->clear();
    m_wgDonatImovina->m_lstStrankaImovinaStatus->clear();
    m_wgDonatImovina->m_lstStrankaImovinaStatus->clear();
    m_wgDonatImovina->m_txtStrankaUgovorneObveze->clear();
    m_wgDonatImovina->m_imgStrankaUgovorneObveze->clear();
    popuniStrankaPenali();
    popuniSveImovine();
    setCursor(Qt::ArrowCursor);
}
void FrmDonatMenu2::on_treeStrankaImovina_itemPressed(QTreeWidgetItem * itemImovina, int UNUSED(column))
{
    setCursor(Qt::BusyCursor);
    m_wgDonatImovina->m_lstStrankaImovinaStatus->clear();
    m_wgDonatImovina->m_txtStrankaImovinaId->clear();
    if(!itemImovina->text(1).isEmpty())
    {
        m_iImovinaId = itemImovina->text(1).toUInt();
        m_wgDonatImovina->m_txtStrankaImovinaId->setText(itemImovina->text(1));
        popuniImovinaStatus();
    }
    setCursor(Qt::ArrowCursor);
}

void FrmDonatMenu2::on_btnStrankaPregledZahtjeva_clicked()
{
    if(m_iKupacId == 0)
        return;

    // Show Donat about form
    Sporazumi::FrmPregledZahtjeva *frmPregledZahtjeva = new Sporazumi::FrmPregledZahtjeva(1, m_iKupacId, this);
    frmPregledZahtjeva->show();
//    delete frmPregledZahtjeva;
}
void FrmDonatMenu2::on_btnStrankaPregledUgovora_clicked()
{
    if(m_iKupacId == 0)
        return;

    // Show Donat about form
    Kontakt::FrmUgovorneObveze *frmUgovorneObveze = new Kontakt::FrmUgovorneObveze(m_iKupacId, m_iGrupaImovineId, this);
    frmUgovorneObveze->exec();
    delete frmUgovorneObveze;
}
void FrmDonatMenu2::on_btnStrankaUgovorneObveze_clicked()
{
    if(m_iKupacId == 0)
        return;

    // Show Donat about form
    Sporazumi::FrmPregledZahtjeva *frmPregledZahtjeva = new Sporazumi::FrmPregledZahtjeva(3, m_iKupacId, this);
    frmPregledZahtjeva->show();
//    delete frmPregledZahtjeva;
}


// [Dokumenti Donat menu - event handlers]
void FrmDonatMenu2::on_actionDokumentiZahtjevMax23_clicked()
{
    if(m_iStrankaId == 0)
    {
        // Show OCV web
        Kontakt::FrmDonatZahtjevAll *frmDonatZahtjevAll = new Kontakt::FrmDonatZahtjevAll(this);
        frmDonatZahtjevAll->exec();
        delete frmDonatZahtjevAll;
    }
    else
    {
        // Show OCV web
        Kontakt::FrmDonatZahtjevAll *frmDonatZahtjevAll = new Kontakt::FrmDonatZahtjevAll(
                    m_iStrankaId,
                    m_iGrupaImovineId,
                    this);
        frmDonatZahtjevAll->exec();
        delete frmDonatZahtjevAll;
    }
}
void FrmDonatMenu2::on_actionDokumentiCpeOprema_clicked()
{
    if(m_iStrankaId == 0)
    {
        // Show OCV web
        Kontakt::FrmCpeOprema *frmCpeOprema = new Kontakt::FrmCpeOprema(this);
        frmCpeOprema->exec();
        delete frmCpeOprema;
    }
    else
    {
        // Show OCV web
        Kontakt::FrmCpeOprema *frmCpeOprema = new Kontakt::FrmCpeOprema(m_iKupacId, this);
        frmCpeOprema->exec();
        delete frmCpeOprema;
    }
}
void FrmDonatMenu2::on_actionPregledSporazumaDetaljno_clicked()
{
    // Show Donat detaljan pregled zahtjeva
    Sporazumi::FrmPregledSporazuma *frmPregled = new Sporazumi::FrmPregledSporazuma(this);
    frmPregled->exec();
    delete frmPregled;
}


// [Stranke Donat menu - event handlers]
void FrmDonatMenu2::on_actionFizickaOsoba_clicked()
{
    if(m_iStrankaId != 0)
    {
        // Show Fizicka stranka
        Stranka::FrmStrankaFiz *frmStrankaFizicka = new Stranka::FrmStrankaFiz(m_iStrankaId, this);
        frmStrankaFizicka->exec();
        delete frmStrankaFizicka;
    }
    else
    {
        // Show new Fizicka stranka
        Stranka::FrmStrankaFiz *frmStrankaFizicka = new Stranka::FrmStrankaFiz(this);
        frmStrankaFizicka->exec();
        delete frmStrankaFizicka;
    }
}
void FrmDonatMenu2::on_actionPravnaOsoba_clicked()
{
    if(m_iStrankaId != 0)
    {
        // Show Fizicka stranka
        Stranka::FrmStrankaPrav *frmStrankaPravna = new Stranka::FrmStrankaPrav(m_iStrankaId, this);
        frmStrankaPravna->exec();
        delete frmStrankaPravna;
    }
    else
    {
        // Show new Fizicka stranka
        Stranka::FrmStrankaPrav *frmStrankaPravna = new Stranka::FrmStrankaPrav(this);
        frmStrankaPravna->exec();
        delete frmStrankaPravna;
    }
}
void FrmDonatMenu2::on_actionStrankaOcv_clicked()
{
    if(m_iStrankaId == 0)
    {
        return;
    }

    string strOib;

    string strSqlStatement;
    strSqlStatement.append("SELECT MBR, BROJ_ISPRAVE FROM STRANKE WHERE STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));

	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strOib = rs->getString(2);
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

    if(strOib.empty())
    {
        QMessageBox::critical(this, tr("DONAT - Stranka - OIB"),
                                    tr("Stranka nema OIB unesen."),
                                       QMessageBox::Close);
        return;
    }

    // Show OCV web
    Stranka::FrmStrankaOcv *frmOcv = new Stranka::FrmStrankaOcv(strOib, m_strTelefonskiBroj);
    frmOcv->exec();
    delete frmOcv;
}

FrmDonatMenu2::~FrmDonatMenu2()
{
    CloseDonatConnection();
}

}   // namespace log
