//
//  frmdonatmenu.cpp
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

#include "frmdonatmenu.h"
#include "ui_frmdonatmenu.h"

#include "itos.h"
#include "ocinumber.h"

#include "frmdonatabout.h"
#include "frmdonatuserrole.h"
#include "frmdonatpasswordchange.h"

#include "forms/log/frmdonatlogin.h"

#include "forms/sporazumi/frmpregledzahtjeva.h"
#include "forms/sporazumi/frmpregledsporazuma.h"
#include "forms/sporazumi/frmpregledprocesa.h"
#include "forms/sporazumi/frmdonatpregled.h"
#include "forms/sporazumi/frmwwmspregled.h"
#include "forms/sporazumi/frmobavijestiposlane.h"
#include "forms/sporazumi/frmobavijestislanje.h"
#include "forms/sporazumi/frmugovoripregled.h"
#include "forms/sporazumi/frmugovoriugovaranje.h"
#include "forms/sporazumi/frmzahtjevipregled.h"
#include "forms/sporazumi/frmzahtjevinemoguci.h"
#include "forms/sporazumi/frmgrupaimovineatributi.h"
#include "forms/sporazumi/frmbundleinfo.h"
#include "forms/sporazumi/frmsuspenzija.h"
#include "forms/sporazumi/frmpregledn.h"

#include "forms/stranka/frmstrankaocv.h"
#include "forms/stranka/frmstrankafiz.h"
#include "forms/stranka/frmstrankaprav.h"
#include "forms/stranka/frmstrankagrupeimovine.h"
#include "forms/stranka/frmstrankazurnal.h"
#include "forms/stranka/frmmdm1.h"

#include "forms/kontakt/frmugovorneobveze.h"
#include "forms/kontakt/frmcpeoprema.h"
#include "forms/kontakt/frmdonatzahtjevall.h"
#include "forms/kontakt/frmkontaktnicentar.h"
#include "forms/kontakt/frmtipstranke.h"
#include "forms/kontakt/frmkanalprodaje.h"
#include "forms/kontakt/frmkanalprodajekorisnik.h"
#include "forms/kontakt/frmkontaktnicentaruser.h"
#include "forms/kontakt/prigovor/frmprigovoradd.h"
#include "forms/kontakt/prigovor/frmprigovorpregled.h"
#include "forms/kontakt/prigovor/frmprigovorodobrenje.h"
#include "forms/kontakt/prigovor/frmprigovorpismopotvrde.h"
#include "forms/kontakt/zlonamjerni/frmzlonamjernimobadd.h"
#include "forms/kontakt/zlonamjerni/frmzlonamjernipregled.h"


namespace Log {
// [ Forms Constructors ]
FrmDonatMenu::FrmDonatMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmDonatMenu)
{
    ui->setupUi(this);

    //ui->lblStatusBarDatum->setText(QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")));
    //ui->lblStatusBarTime->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));
    ui->btnStatusBarDonatUser->setText(QString::fromStdString(g_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_KORISNIK_NAZ));
    ui->btnStatusBarDonatDabase->setToolTip(QString::fromStdString(g_DonatDatebase) + tr(" - ") + QString::fromStdString(g_DonatUser));

    ui->treeStranke->setColumnWidth(0, 1);
    ui->treeStranke->setColumnWidth(1, 430);
    ui->treeStranke->setColumnWidth(2, 20);
    ui->treeStranke->setColumnWidth(3, 14);
    ui->treeStranke->setColumnWidth(4, 14);
    ui->treeStranke->setColumnWidth(5, 25);
    ui->treeStranke->hideColumn(0);
    ui->treeStranke->hideColumn(2);
    ui->treeStranke->hideColumn(3);
    ui->treeStranke->hideColumn(4);
//    ui->treeStranke->verticalHeader()->hide();
//    ui->treeStranke->horizontalHeader()->hide();
    ui->treeStranke->setAlternatingRowColors(true);
//    ui->treeStranke->setShowGrid(true);
    ui->treeStranke->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeStranke->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->treeInfoItems->setColumnWidth(0, 320);
    ui->treeInfoItems->setColumnWidth(1, 20);
    ui->treeInfoItems->setColumnWidth(2, 30);
    ui->treeInfoItems->setColumnWidth(3, 30);
//    ui->treeInfoItems->hideColumn(0);
//    ui->treeInfoItems->hideColumn(1);
    ui->treeInfoItems->hideColumn(2);
    ui->treeInfoItems->hideColumn(3);
//    ui->treeInfoItems->horizontalHeader()->hide();
//    ui->treeInfoItems->setAlternatingRowColors(true);
//    ui->treeInfoItems->setShowGrid(false);
    ui->treeInfoItems->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeInfoItems->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->treeGrupeImovine->setColumnWidth(0, 300);
    ui->treeGrupeImovine->setColumnWidth(1, 10);
    ui->treeGrupeImovine->hideColumn(2);
    ui->treeGrupeImovine->hideColumn(3);
    ui->treeGrupeImovine->hideColumn(4);
    ui->treeGrupeImovine->hideColumn(5);
    ui->treeGrupeImovine->hideColumn(6);
    ui->treeGrupeImovine->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeGrupeImovine->setSelectionBehavior(QAbstractItemView::SelectRows);


    ui->treeAsset->setColumnWidth(0, 300);
    ui->treeAsset->setColumnWidth(1, 18);
    ui->treeAsset->setColumnWidth(2, 18);
    ui->treeAsset->setColumnWidth(3, 18);
    ui->treeAsset->hideColumn(4);
    ui->treeAsset->hideColumn(5);
    ui->treeAsset->hideColumn(6);
    ui->treeAsset->hideColumn(7);
    ui->treeAsset->hideColumn(8);
    ui->treeAsset->hideColumn(9);
    ui->treeAsset->hideColumn(10);
    ui->treeAsset->hideColumn(11);
    ui->treeAsset->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeAsset->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->treeImovina->hideColumn(1);
    ui->treeImovina->hideColumn(2);
    ui->treeImovina->hideColumn(3);
    ui->treeImovina->hideColumn(4);
    ui->treeImovina->hideColumn(5);
    ui->treeImovina->hideColumn(6);
    ui->treeImovina->hideColumn(7);
    ui->treeImovina->hideColumn(8);
    ui->treeImovina->hideColumn(9);
    ui->treeImovina->hideColumn(10);
    ui->treeImovina->hideColumn(11);
    ui->treeImovina->setHeaderHidden(true);
    ui->treeImovina->setAlternatingRowColors(false);
    ui->treeImovina->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeImovina->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeImovina->setItemsExpandable(true); //QTreeWidgetItem::DontShowIndicatorWhenChildless
    ui->treeImovina->setRootIsDecorated(true);

    ui->fraGrupaImovineDetaljno->setVisible(false);

    ui->txtFltNaziv->setFocus();

    m_iconAdressValid.addFile(QString::fromUtf8(":/InDonat/Forms/images/NODE_7_10x10.png"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconZuti.addFile(QString::fromUtf8(":/InDonat/Forms/images/zuti.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconZeleni.addFile(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconCrveni.addFile(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconTransparent.addFile(QString::fromUtf8(":/InDonat/Forms/images/transparet_10x10.png"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);

    m_SearchMode = TraziPoNazivKorisnika;
    m_bSearchAktivneKupce = false;
    m_InfoMode = PrikaziInfo;
    m_bAktivnaGrupaImovine = true;
    m_bAktivnaImovina = true;
    m_bPunoGrupaImovine = false;
    m_iGrupaImovineId = 0;
    m_iStrankaId = 0;
    m_iKupacId = 0;

    //////////////////////////////////////////////////////////
    // Center Main Form on Screen
    //////////////////////////////////////////////////////////

//    window->setGeometry(
//        QStyle::alignedRect(
//            Qt::LeftToRight,
//            Qt::AlignCenter,
//            window->size(),
//            qApp->desktop()->availableGeometry()
//        ));


    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    windowSize = size();
    width = windowSize.width();
    height = windowSize.height();

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;

    move ( x, y );

    //setFixedSize(windowSize.width(), windowSize.height());

    //////////////////////////////////////////////////////////

}

FrmDonatMenu::~FrmDonatMenu()
{
    CloseDonatConnection();
    delete ui;
}

// [ Private Member Functions ]
void FrmDonatMenu::toUpper(const QString &text)
{
    QLineEdit *le = qobject_cast<QLineEdit *>(sender());
    if(!le) return;
    le->setText(text.toUpper());
}

// Clearform data
void FrmDonatMenu::clearDonatSearchResults()
{
    ui->treeStranke->clear();
    ui->treeInfoItems->clear();

    clearDonatStranka();
}
void FrmDonatMenu::clearDonatStranka()
{
    ui->fraGrupaImovineDetaljno->setVisible(false);
    ui->fraGrupeImovine->setVisible(true);

    m_iGrupaImovineId = 0;
    m_iGrupaImovineIsStatus = 0;
    m_iGrupaImovineIsTip = 0;

    m_bAktivnaGrupaImovine = true;
    m_bAktivnaImovina = true;

    ui->treeInfoItems->clear();
    ui->treeGrupeImovine->clear();

    clearDonatStrankaAsset();

//	m_wgDonatStranke->m_txtStrankaLoyaltyId->clear();
//	m_wgDonatStranke->m_txtStrankaLoyaltyValidniBodovi->clear();
//	m_wgDonatStranke->m_txtStrankaLoyaltyPotencijalniBodovi->clear();

//    m_wgDonatStranke->m_txtStrankaZastupnik->clear();
//    m_wgDonatStranke->m_btnStrankaZatupnik2->setEnabled(false);

//    m_wgDonatStranke->m_txtStrankaAdslStatus->clear();
//    m_wgDonatStranke->m_txtStrankaMaxtvStatus->clear();

//    m_wgDonatStranke->m_lblDonatStrankaMessages->clear();

//    m_wgDonatImovina->m_lblStrankaKlaseTitle->setText(tr("Klasa"));
//    m_wgDonatImovina->m_cboStrankaImovinaKlase->clear();
//    m_wgDonatImovina->m_treeStrankaGrupaImovine->clear();
//    m_wgDonatImovina->m_txtStrankaGrupaImovineId->clear();
//    m_wgDonatImovina->m_txtStrankaUgovorneObveze->clear();
//    m_wgDonatImovina->m_imgStrankaUgovorneObveze->clear();
//    m_wgDonatImovina->m_cboStrankaImovinaKlase->disconnect(SIGNAL(currentIndexChanged(int)));

//    m_wgDonatImovina->m_txtStrankaImovinaId->clear();
//    m_wgDonatImovina->ui->treeImovina->clear();
//    m_wgDonatImovina->m_txtStrankaImovinaStatus->clear();
//    m_wgDonatImovina->m_lstStrankaImovinaStatus->clear();

//    m_iGrupaImovineId = 0;
//    m_iGrupaImovineIsStatus = 0;

//    m_iImovinaId = 0;
//    m_iImovinaIdStatus = 0;
}
void FrmDonatMenu::clearDonatStrankaAsset()
{
    ui->treeAsset->clear();
    ui->treeImovina->clear();

    ui->txtUloge->clear();
    ui->txtGrupaImovineId->clear();

    ui->txtImovinaStatus->clear();
    ui->txtImovinaAktivnaOd->clear();
    ui->txtImovinaAktivnaDo->clear();
    ui->txtImovinaSuspendiranaOd->clear();
    ui->txtImovinaSuspendiranaDo->clear();
    ui->txtAdslStatus->clear();
    ui->txtMaxTvStatus->clear();
    ui->txtZastupnik->clear();
}

// [ Donat Search ]
void FrmDonatMenu::traziDonatKorisnikaPoNazivu()
{
    int iBrojac = 0;

    string strSqlStatement;
    strSqlStatement.append("BEGIN P_VRATI_PREGLED_STRANKE_NOVI(:naziv, :mjesto_id_par, :mjesto, :ulica_id_par, :ulica, :akt, :brojac); END;");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setString(1, ui->txtFltNaziv->text().toStdString());
        sqlStatement->setNull(2, OCCISTRING);
        sqlStatement->setNull(3, OCCISTRING);
        sqlStatement->setNull(4, OCCISTRING);
        sqlStatement->setNull(5, OCCISTRING);
        if(m_bSearchAktivneKupce == true)
        {
            sqlStatement->setInt(6, 1);
        }
        else
        {
            sqlStatement->setInt(6, 0);
        }
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

//    if(iBrojac == 0)
//    {
//        g_DonatConn->terminateStatement(sqlStatement);
//        strSqlStatement.erase();
//        return;
//    }

    strSqlStatement.erase();
    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append(" FROM TEMP_STRANKE_FILTER WHERE BROJAC < ");
    if(iBrojac < 100)
    {
        strSqlStatement.append(cttl::itos(iBrojac + 1));
    }
    else
    {
        strSqlStatement.append("100");
    }
    strSqlStatement.append(" ORDER BY BROJAC");
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listStranke;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
            itemStranka->setText(0, QString::number(rs->getUInt(1)));
            itemStranka->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(3)));
            itemStranka->setText(2, QString::number(rs->getUInt(4)));
            itemStranka->setText(3, QString::fromStdString(rs->getString(5)));
            itemStranka->setText(4, QString::number(rs->getUInt(6)));
            if("Y" == rs->getString(5))
            {
                itemStranka->setIcon(5, m_iconAdressValid);
            }
            listStranke.append(itemStranka);
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

    if(!listStranke.empty())
    {
        ui->treeStranke->insertTopLevelItems(0, listStranke);
//        ui->treeStranke->setCurrentItem(listStranke.first());
        ui->treeStranke->expandAll();
//        ui->treeStranke->collapseAll();
    }

}
void FrmDonatMenu::traziDonatKorisnikaPoBrojuTelefona()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT DISTINCT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append("FROM   V_PREGLED_STRANKE_TELBR ");
    strSqlStatement.append("WHERE TEL_BROJ = '");
    strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
    strSqlStatement.append("'");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listStranke;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
            itemStranka->setText(0, QString::number(rs->getUInt(1)));
            itemStranka->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(3)));
            itemStranka->setText(2, QString::number(rs->getUInt(4)));
            itemStranka->setText(3, QString::fromStdString(rs->getString(5)));
            itemStranka->setText(4, QString::number(rs->getUInt(6)));
            if("Y" == rs->getString(5))
            {
                itemStranka->setIcon(5, m_iconAdressValid);
            }
            listStranke.append(itemStranka);
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

    if(!listStranke.empty())
    {
        ui->treeStranke->insertTopLevelItems(0, listStranke);
//        ui->treeStranke->setCurrentItem(listStranke.first());
        ui->treeStranke->expandAll();
//        ui->treeStranke->collapseAll();
    }

}
void FrmDonatMenu::traziDonatKorisnikaPoJmbg()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append("FROM   V_PREGLED_STRANKE_MBR ");
    strSqlStatement.append("WHERE LPAD(MBR, 13, '0') = LPAD('");
    strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
    strSqlStatement.append("', 13, '0')");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listStranke;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
            itemStranka->setText(0, QString::number(rs->getUInt(1)));
            itemStranka->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(3)));
            itemStranka->setText(2, QString::number(rs->getUInt(4)));
            itemStranka->setText(3, QString::fromStdString(rs->getString(5)));
            itemStranka->setText(4, QString::number(rs->getUInt(6)));
            if("Y" == rs->getString(5))
            {
                itemStranka->setIcon(5, m_iconAdressValid);
            }
            listStranke.append(itemStranka);
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

    if(!listStranke.empty())
    {
        ui->treeStranke->insertTopLevelItems(0, listStranke);
//        ui->treeStranke->setCurrentItem(listStranke.first());
        ui->treeStranke->expandAll();
//        ui->treeStranke->collapseAll();
    }
}
void FrmDonatMenu::traziDonatKorisnikaPoOib()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append("FROM   V_PREGLED_STRANKE_OIB ");
    strSqlStatement.append("WHERE LPAD(BROJ_ISPRAVE, 13, '0') = LPAD('");
    strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
    strSqlStatement.append("', 13, '0')");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listStranke;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
            itemStranka->setText(0, QString::number(rs->getUInt(1)));
            itemStranka->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(3)));
            itemStranka->setText(2, QString::number(rs->getUInt(4)));
            itemStranka->setText(3, QString::fromStdString(rs->getString(5)));
            itemStranka->setText(4, QString::number(rs->getUInt(6)));
            if("Y" == rs->getString(5))
            {
                itemStranka->setIcon(5, m_iconAdressValid);
            }
            listStranke.append(itemStranka);
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

    if(!listStranke.empty())
    {
        ui->treeStranke->insertTopLevelItems(0, listStranke);
//        ui->treeStranke->setCurrentItem(listStranke.first());
        ui->treeStranke->expandAll();
//        ui->treeStranke->collapseAll();
    }
}
void FrmDonatMenu::traziDonatKorisnikaPoUlogaStrankeId()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT ROOT_STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, DECODE(TIP_STRANKE1,'Privatni',1,2) TSTRANKE1_ID ");
    strSqlStatement.append("FROM   KONTAKTI WHERE ACCOUNT_ID = ");
    strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listStranke;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
            itemStranka->setText(0, QString::number(rs->getUInt(1)));
            itemStranka->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(3)));
            itemStranka->setText(2, QString::number(rs->getUInt(4)));
            itemStranka->setText(3, QString::fromStdString(rs->getString(5)));
            itemStranka->setText(4, QString::number(rs->getUInt(6)));
            if("Y" == rs->getString(5))
            {
                itemStranka->setIcon(5, m_iconAdressValid);
            }
            listStranke.append(itemStranka);
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

    if(!listStranke.empty())
    {
        ui->treeStranke->insertTopLevelItems(0, listStranke);
//        ui->treeStranke->setCurrentItem(listStranke.first());
        ui->treeStranke->expandAll();
//        ui->treeStranke->collapseAll();
    }
}
void FrmDonatMenu::traziDonatKorisnikaPoTicketId()
{
    std::list<unsigned int> lstGupaImovineId;

    string strSqlStatement;
    strSqlStatement.append("SELECT /*+ rule*/ P.ID ");
    strSqlStatement.append("FROM  ORDER_2 O, POSLOVNI_PROCESI P ");
    strSqlStatement.append("WHERE \"TicketId\" = '");
    strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
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

    QList<QTreeWidgetItem *> listStranke;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
            itemStranka->setText(0, QString::number(rs->getUInt(1)));
            itemStranka->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(3)));
            itemStranka->setText(2, QString::number(rs->getUInt(4)));
            itemStranka->setText(3, QString::fromStdString(rs->getString(5)));
            itemStranka->setText(4, QString::number(rs->getUInt(6)));
            if("Y" == rs->getString(5))
            {
                itemStranka->setIcon(5, m_iconAdressValid);
            }
            listStranke.append(itemStranka);
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

    if(!listStranke.empty())
    {
        ui->treeStranke->insertTopLevelItems(0, listStranke);
//        ui->treeStranke->setCurrentItem(listStranke.first());
        ui->treeStranke->expandAll();
//        ui->treeStranke->collapseAll();
    }
}
void FrmDonatMenu::traziDonatKorisnikaPoAssetId()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT DISTINCT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, ");
    strSqlStatement.append(" 	   ADRESA_ID, VALIDIRANA_ADRESA, TSTRANKE1_ID ");
    strSqlStatement.append("FROM   V_PREGLED_STRANKE_TELBR ");
    strSqlStatement.append("WHERE GIMOVINE_ID = ");
    strSqlStatement.append(ui->txtFltNaziv->text().toStdString());

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listStranke;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
            itemStranka->setText(0, QString::number(rs->getUInt(1)));
            itemStranka->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(3)));
            itemStranka->setText(2, QString::number(rs->getUInt(4)));
            itemStranka->setText(3, QString::fromStdString(rs->getString(5)));
            itemStranka->setText(4, QString::number(rs->getUInt(6)));
            if("Y" == rs->getString(5))
            {
                itemStranka->setIcon(5, m_iconAdressValid);
            }
            listStranke.append(itemStranka);
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

    if(!listStranke.empty())
    {
        ui->treeStranke->insertTopLevelItems(0, listStranke);
//        ui->treeStranke->setCurrentItem(listStranke.first());
        ui->treeStranke->expandAll();
//        ui->treeStranke->collapseAll();
    }
}

// [ Customer data ]
void FrmDonatMenu::popuniStrankaUlogeStranaka()
{
    ui->lstvUlogeStranaka->clear();

    if(m_iStrankaId == 0)
    {
        return;
    }

    ui->txtUloge->setText(tr("OSNOVNE ULOGE"));

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
    strSqlStatement.append("AND h2.TULSTRANKE_ID NOT IN (1, 11, 15) ");
    strSqlStatement.append("ORDER BY ");
    strSqlStatement.append("  5");

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
            ui->lstvUlogeStranaka->addItem(listWidgetItem);
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
void FrmDonatMenu::popuniStrankaZastupnika()
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

    ui->txtZastupnik->setPlainText(QString::fromStdString(strZastupnik));
}
void FrmDonatMenu::provjeriOib()
{
    if(m_iStrankaId == 0)
    {
        return;
    }

    m_strOib.clear();
    string strSqlStatement;
    strSqlStatement.append("SELECT BROJ_ISPRAVE FROM STRANKE WHERE STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(rs->isNull(1))
            {
                ui->lblStrankaInfo1->setText(tr("STRANKA NEMA UPISAN OIB"));
            }
            else
            {
                if("" == rs->getString(1))
                {
                    ui->lblStrankaInfo1->setText(tr("STRANKA NEMA UPISAN OIB"));
                }
                else
                {
                    ui->lblStrankaInfo1->setText(tr("STRANKA OIB ... ") + QString::fromStdString(rs->getString(1)));
                    m_strOib = rs->getString(1);
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

void FrmDonatMenu::popuniStrankaSveKlase()
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

        strSqlStatement.clear();
        strSqlStatement.append("SELECT GIMOVINE_ID, SLOG_STATUS, TEL_LIN_ID FROM B_HIJERARHIJA WHERE TEL_BROJ = '");
        strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
        strSqlStatement.append("'  AND KUPAC_ID = ");
        strSqlStatement.append(cttl::itos(m_iKupacId));
        strSqlStatement.append(" AND SLOG_STATUS >= 0 AND SLOG_STATUS < 11 ");
        strSqlStatement.append(" ORDER BY SLOG_STATUS DESC, B1, TEL_LIN_ID DESC ");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            if(rs->next())
            {
                m_iGrupaImovineId = rs->getUInt(1);
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

        ui->treeGrupeImovine->clear();
        ui->fraGrupaImovineDetaljno->setVisible(true);
        ui->fraGrupeImovine->setVisible(false);

        popuniZaGrupuImovine();
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
            ui->fraGrupaImovineDetaljno->setVisible(false);
            ui->fraGrupeImovine->setVisible(true);
            g_DonatConn->terminateStatement(sqlStatement);
            strSqlStatement.erase();
            return;
        }

        ui->txtGrupaImovineId->setText(QString::number(iBrojac) + tr(" grupa imovine."));
        ui->treeGrupeImovine->clear();

        QList<QTreeWidgetItem *> listLinijeGrupeImovine;
        QList<QTreeWidgetItem *> listGrupeImovine;

        strSqlStatement.erase();
        strSqlStatement.append("SELECT TEL_LIN_ID, COUNT(TEL_LIN_ID) BROJ ");
        strSqlStatement.append("FROM TEMP_ASSET_FILTER ");
        strSqlStatement.append("WHERE TEL_LIN_ID NOT IN ('HTnet', 'HT net', 'ISP - davatelj Internet usluga') ");
        if(m_bAktivnaGrupaImovine == true)
        {
            strSqlStatement.append("AND STATUS_ID > 0 ");
        }
        else
        {
            strSqlStatement.append("AND STATUS_ID < 1 ");
        }
        strSqlStatement.append("GROUP BY TEL_LIN_ID ORDER BY TEL_LIN_ID DESC ");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                QTreeWidgetItem *itemLinijaGrupeImovine = new QTreeWidgetItem();
                itemLinijaGrupeImovine->setText(0, QString::fromStdString(rs->getString(1) + " ... " + rs->getString(2)));
                itemLinijaGrupeImovine->setText(2, QString::fromStdString(rs->getString(1)));
                listLinijeGrupeImovine.append(itemLinijaGrupeImovine);
            }
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }

        strSqlStatement.erase();
        strSqlStatement.append("SELECT BROJAC, GIMOVINE_ID, TEL_BROJ, TEL_LIN_ID, STATUS_ID, SLOG_STATUS ");
        strSqlStatement.append("FROM TEMP_ASSET_FILTER ");
        strSqlStatement.append("WHERE TEL_LIN_ID NOT IN ('HTnet', 'HT net', 'ISP - davatelj Internet usluga') ");
        if(m_bAktivnaGrupaImovine == true)
        {
            strSqlStatement.append("AND STATUS_ID > 0 ");
        }
        else
        {
            strSqlStatement.append("AND STATUS_ID < 1 ");
        }
        strSqlStatement.append("ORDER BY BROJAC ");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                QTreeWidgetItem *itemGrupaImovine = new QTreeWidgetItem();
                itemGrupaImovine->setText(0, QString::fromStdString(rs->getString(3)));
                int iStatus;
                iStatus = rs->getInt(5);
                if(iStatus == 0)
                {
                    itemGrupaImovine->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                }
                else if(iStatus == 2)
                {
                    itemGrupaImovine->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.GIF")));
                }
                else if(iStatus > 2)
                {
                    itemGrupaImovine->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.GIF")));
                }
                itemGrupaImovine->setText(2, QString::fromStdString(rs->getString(4)));
                itemGrupaImovine->setText(3, QString::fromStdString(rs->getString(2)));
                itemGrupaImovine->setText(4, QString::fromStdString(rs->getString(3)));
                itemGrupaImovine->setText(5, QString::fromStdString(rs->getString(5)));
                itemGrupaImovine->setText(6, QString::fromStdString(rs->getString(6)));
                listGrupeImovine.append(itemGrupaImovine);
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

        for(int i = 0; i < listGrupeImovine.size(); ++i)
        {
            for(int j = 0; j < listLinijeGrupeImovine.size(); ++j)
            {
                if(listLinijeGrupeImovine.at(j)->text(2) == listGrupeImovine.at(i)->text(2))
                {
                    listLinijeGrupeImovine.at(j)->addChild(listGrupeImovine.at(i));
                    break;
                }
            }
        }

        if(!listLinijeGrupeImovine.empty())
        {
            listLinijeGrupeImovine.first()->setSelected(true);
            ui->treeGrupeImovine->insertTopLevelItems(0, listLinijeGrupeImovine);
            ui->treeGrupeImovine->setCurrentItem(listLinijeGrupeImovine.first());
            ui->treeGrupeImovine->expandAll();
    //      ui->treeGrupeImovine->collapseAll();
        }

        if(iBrojac > 20)
        {
//			m_wgDonatImovina->m_fraStrankaImovinaKlasaTitle->setVisible(true);
//			m_wgDonatImovina->m_fraStrankaGrupaImovineTitle->setVisible(false);
            m_bPunoGrupaImovine = true;
//			connect(m_wgDonatImovina->m_cboStrankaImovinaKlase,
//					SIGNAL(currentIndexChanged(int)),
//					this,
//					SLOT(on_cboStrankaImovinaKlase_currentIndexChanged(int)));
        }
        else
        {
//			m_wgDonatImovina->m_fraStrankaImovinaKlasaTitle->setVisible(false);
//			m_wgDonatImovina->m_fraStrankaGrupaImovineTitle->setVisible(true);
            m_bPunoGrupaImovine = false;
//			m_wgDonatImovina->m_cboStrankaImovinaKlase->disconnect(SIGNAL(currentIndexChanged(int)));
        }

        popuniStrankaGrupeImovine();
    }
}
void FrmDonatMenu::popuniStrankaGrupeImovine()
{
    bool bTelBrojIsNumber;
    int UNUSED(iTelBroj) = ui->txtFltNaziv->text().toInt(&bTelBrojIsNumber);

    m_iGrupaImovineId = 0;
    m_iGrupaImovineIsStatus = 0;

    switch(m_SearchMode)
    {
        case TraziPoNazivKorisnika:
        {
            if(bTelBrojIsNumber == true)
            {
                string strSqlStatement;
                strSqlStatement.append("SELECT GIMOVINE_ID, SLOG_STATUS FROM B_HIJERARHIJA WHERE TEL_BROJ = '");
                strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
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
                    m_strTelefonskiBroj = ui->txtFltNaziv->text().toStdString();
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
            }
            break;
        }
        case TraziPoBrojTelefona:
        {
            string strSqlStatement;
            strSqlStatement.append("SELECT GIMOVINE_ID, SLOG_STATUS FROM B_HIJERARHIJA WHERE TEL_BROJ = '");
            strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
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
                m_strTelefonskiBroj = ui->txtFltNaziv->text().toStdString();
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
            break;
        }
        case TraziPoJmbg:
        {
//            popuniSveGrupeImovine();
            break;
        }
        case TraziPoOib:
        {
//            popuniSveGrupeImovine();
            break;
        }
        case TraziPoUlogaStrankeId:
        {
//            popuniSveGrupeImovine();
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
            strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
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
            strSqlStatement.append(ui->txtFltNaziv->text().toStdString());
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
            break;
        }
        case TraziPoGrupna:
        {
//			popuniSveGrupeImovine();
            break;
        }
        case TraziPoHijerahija:
        {
//			popuniSveGrupeImovine();
            break;
        }
        default :
        {
//			popuniSveGrupeImovine();
            break;
        }

    }

    if(m_iGrupaImovineId != 0)
    {
        ui->fraGrupaImovineDetaljno->setVisible(true);
        ui->fraGrupeImovine->setVisible(false);
        // To Do clear Grupa imovine
        clearDonatStrankaAsset();

        popuniZaGrupuImovine();
    }
}
void FrmDonatMenu::popuniZaGrupuImovine()
{
    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT TIP, ASSET, GIMOVINE_ID, NVL(TEL_BROJ,'-') TEL_BROJ, NVL(KLASA,'-') KLASA ");
    strSqlStatement.append("FROM V_GIM_STRUKTURA_SVE WHERE GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    strSqlStatement.append(" ORDER BY TIP ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listGrupaImovine;
    std::list<gim_struktura_sve_t> lstGimStruktura;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            unsigned int iAssetId;
            iAssetId = rs->getUInt(2);
            if(iAssetId > 0)
            {
                gim_struktura_sve_t gim;
                gim.Tip = rs->getString(1);
                gim.Asset = rs->getUInt(2);
                gim.GrupaImovineId = rs->getUInt(3);
                gim.TelefonskiBroj = rs->getString(4);
                gim.Klasa = rs->getString(5);
                lstGimStruktura.push_back(gim);
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

    list<gim_struktura_sve_t >::const_iterator itGim;
    for(itGim=lstGimStruktura.begin(); itGim!=lstGimStruktura.end(); ++itGim)
    {
        strSqlStatement.clear();
        strSqlStatement.append("SELECT GIMOVINE_ID, B1, B2, TEL_BROJ, TEL_LIN_ID, IMOVINA_ID, ");
        strSqlStatement.append("SLOG_STATUS, TO_CHAR(DATUM_DO, 'DD.MM.RR') DATUM_DO ");
        strSqlStatement.append("FROM B_HIJERARHIJA WHERE GIMOVINE_ID = ");
        strSqlStatement.append(cttl::itos(itGim->Asset));
        strSqlStatement.append(" AND KUPAC_ID = ");
        strSqlStatement.append(cttl::itos(m_iKupacId));
        strSqlStatement.append(" AND B1>0 AND B2<>9 ");
        if(m_bAktivnaGrupaImovine == true)
        {
            strSqlStatement.append("AND SLOG_STATUS > 0 ");
        }
        else
        {
            strSqlStatement.append("AND SLOG_STATUS = 0 ");
        }
        strSqlStatement.append(" ORDER BY B1, TEL_BROJ ");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                QTreeWidgetItem *itemGrupaImovine = new QTreeWidgetItem();
                itemGrupaImovine->setText(0, QString::fromStdString(rs->getString(4) + "      " + rs->getString(5)));
                itemGrupaImovine->setText(4, QString::fromStdString(rs->getString(1)));
                itemGrupaImovine->setText(5, QString::fromStdString(rs->getString(2)));
                itemGrupaImovine->setText(6, QString::fromStdString(rs->getString(3)));
                itemGrupaImovine->setText(7, QString::fromStdString(rs->getString(4)));
                itemGrupaImovine->setText(8, QString::fromStdString(rs->getString(5)));
                itemGrupaImovine->setText(9, QString::fromStdString(rs->getString(6)));
                itemGrupaImovine->setText(10, QString::fromStdString(rs->getString(7)));
                itemGrupaImovine->setText(11, QString::fromStdString(rs->getString(8)));
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
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    for(int i = 0; i < listGrupaImovine.size(); ++i)
    {
        if(listGrupaImovine.at(i)->text(5).toInt() == 1)
        {
            if(listGrupaImovine.at(i)->text(10).toInt() == 0)
            {
               listGrupaImovine.at(i)->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
            }
            if(listGrupaImovine.at(i)->text(10).toInt() > 1)
            {
                listGrupaImovine.at(i)->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
            }
            if(m_bAktivnaGrupaImovine == true)
            {
                // Zastavica
                int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(4).toUInt());
                if(iZastavica != 0)
                {
                    listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(0) + tr("  (") + QString::number(iZastavica) + tr(")"));
                    if(iZastavica < 30)
                    {
                        listGrupaImovine.at(i)->setIcon(2, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                    }
                    else
                    {
                        if(iZastavica < 120)
                        {
                            listGrupaImovine.at(i)->setIcon(2, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        }
                        else
                        {
                            listGrupaImovine.at(i)->setIcon(3, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        }
                    }
                }
            }
            if(listGrupaImovine.at(i)->text(5) != tr("ADSL"))
            {
                // Churn
                string strRizik = vratiChurnPhoneRizik(listGrupaImovine.at(i)->text(7).toStdString());
                if(strRizik == "L")
                {
                    listGrupaImovine.at(i)->setIcon(3, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/sve_rijeseni.gif")));
                }
                else if (strRizik == "M") {
                    listGrupaImovine.at(i)->setIcon(3, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/rijeseni_nerijeseni.gif")));
                }
                else if (strRizik == "H") {
                    listGrupaImovine.at(i)->setIcon(3, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/sve_nerijeseni.gif")));
                }
            }
        }
        else
        {
            if(listGrupaImovine.at(i)->text(10).toInt() == 0)
            {
               listGrupaImovine.at(i)->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
            }

            if(m_bAktivnaGrupaImovine == true)
            {
                // Zastavica
                int iZastavica = vratiIndikatorZaprikazUgovorneObveze(listGrupaImovine.at(i)->text(4).toUInt());
                if(iZastavica != 0)
                {
                    if(iZastavica < 30)
                    {
                        listGrupaImovine.at(i)->setIcon(2, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                    }
                    else
                    {
                        if(iZastavica < 120)
                        {
                            listGrupaImovine.at(i)->setIcon(2, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        }
                        else
                        {
                            listGrupaImovine.at(i)->setIcon(3, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        }
                    }
                }
            }

            if(i != 0)
            {
                if(listGrupaImovine.at(i)->text(8) != listGrupaImovine.at((i - 1))->text(8))
                {
//                    listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(4));
                }
                listGrupaImovine.at((0))->addChild(listGrupaImovine.at(i));
            }
        }
    }

    if(!listGrupaImovine.empty())
    {
        listGrupaImovine.first()->setSelected(true);
        ui->treeAsset->insertTopLevelItems(0, listGrupaImovine);
        ui->treeAsset->setCurrentItem(listGrupaImovine.first());
        ui->treeAsset->expandAll();
//      ui->treeAsset->collapseAll();

        ui->txtGrupaImovineId->setText(listGrupaImovine.first()->text(4));
        ui->txtUloge->setText(listGrupaImovine.first()->text(0));
        m_strTelefonskiBroj = listGrupaImovine.first()->text(7).toStdString();
        m_strTelefonskiBrojKlasa = listGrupaImovine.first()->text(8).toStdString();

        popuniSveImovine();
        popuniStrankaPoruke();
    }
}

void FrmDonatMenu::popuniStrankaMdm(QTreeWidgetItem *itemDonatStranka)
{

    if(m_iKupacId == 0)
    {
        return;
    }

    if(itemDonatStranka->childCount() > 0)
    {
        // MDM info is already filled.
        return;
    }

    string strMdmStatus;
    m_iMdmId = 0;

    // [ 0. Erase temp tables ]

    string strSqlStatement;
    strSqlStatement.append("DELETE FROM TMP_MDM_CUSTOMER");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        sqlStatement->executeQuery();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STRANKE");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        sqlStatement->executeQuery();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_ULOGE_STRANAKA");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        sqlStatement->executeQuery();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STR_ADRESE");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        sqlStatement->executeQuery();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    // [ 1. Call MDM Web Service for MDM_ID ]

    strSqlStatement.clear();
    strSqlStatement.append("BEGIN PKG_MDM_INTF.GET_CUSTOMER2(:P_CUSTOMER_ID, :P_RESP_CODE, :P_MESSAGE); END; ");
    sqlStatement->setSQL(strSqlStatement);
    // sqlStatement->setAutoCommit(TRUE);

    string strResponseCode;
    try
    {
        Number nProva = cttl::getONumber(m_iKupacId);
        sqlStatement->setNumber(1, nProva);
        sqlStatement->registerOutParam(2, OCCISTRING, 2000);
        sqlStatement->registerOutParam(3, OCCISTRING, 2000);
        sqlStatement->executeUpdate();
        if(sqlStatement->isNull(2) == true)
        {
            strResponseCode = "0";
        }
        else
        {
            strResponseCode = sqlStatement->getString(2);
        }
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(strResponseCode == "0")
    {
        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
        return;
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT ULSTRANKE_ID, MDM_STATUS FROM MDM_STR_ADRESE WHERE TULSTRANKE_ID = 0 ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_iMdmId = rs->getUInt(1);
            if(rs->isNull(2) == true)
            {
                strMdmStatus = "NIJE ODREĐEN";
            }
            else
            {
                strMdmStatus = rs->getString(2);
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

    if(m_iMdmId == 0)
    {
        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();

        // Add Master Data Management information on selected customer QTreeListItem
        QTreeWidgetItem *itemNoMdmData = new QTreeWidgetItem();
        itemNoMdmData->setText(0, tr(""));
        itemNoMdmData->setText(1, tr("   MDM ... nema podataka"));
        itemNoMdmData->setText(2, tr(""));
        itemNoMdmData->setText(3, tr(""));
        itemNoMdmData->setText(4, tr(""));
        itemNoMdmData->setIcon(5, m_iconTransparent);
        itemDonatStranka->addChild(itemNoMdmData);

        return;
    }
    else
    {
        // Add Master Data Management information on selected customer QTreeListItem
        QString strMdmInfo = QString(tr("   MDM ... MdmId - "));
        strMdmInfo.append(QString::number(m_iMdmId));
        strMdmInfo.append(tr(" ... Status - "));
        strMdmInfo.append(QString::fromStdString(strMdmStatus));
        QTreeWidgetItem *itemNoMdmData = new QTreeWidgetItem();
        itemNoMdmData->setText(0, tr(""));
        itemNoMdmData->setText(1, strMdmInfo);
        itemNoMdmData->setText(2, tr(""));
        itemNoMdmData->setText(3, tr(""));
        itemNoMdmData->setText(4, tr(""));
        if(strMdmStatus == "NIJE ODREĐEN")
        {
            itemNoMdmData->setIcon(5, m_iconZuti);
        }
        else if(strMdmStatus == "OK")
        {
            itemNoMdmData->setIcon(5, m_iconZeleni);
        }
        else if(strMdmStatus == "DIRTY")
        {
            itemNoMdmData->setIcon(5, m_iconCrveni);
        }
        else if(strMdmStatus == "INVALID")
        {
            itemNoMdmData->setIcon(5, m_iconAdressValid);
        }
        else
        {
            itemNoMdmData->setIcon(5, m_iconTransparent);
        }
        itemDonatStranka->addChild(itemNoMdmData);
    }

    // [ 2. Call MDM Web Service for MDM 1. level data ]

    strSqlStatement.clear();
    strSqlStatement.append("BEGIN PKG_MDM_INTF.GET_SOURCE_CUSTOMERS(:P_SOURCE_CUSTOMER_ID, :P_RESP_CODE, :P_MESSAGE); END; ");
    sqlStatement->setSQL(strSqlStatement);
    // sqlStatement->setAutoCommit(TRUE);

    try
    {
        Number nProva = cttl::getONumber(m_iKupacId);
        sqlStatement->setNumber(1, nProva);
        sqlStatement->registerOutParam(2, OCCISTRING, 2000);
        sqlStatement->registerOutParam(3, OCCISTRING, 2000);
        sqlStatement->executeUpdate();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT MDM_STATUS FROM MDM_STR_ADRESE WHERE ULSTRANKE_ID = '");
    strSqlStatement.append(cttl::itos(m_iKupacId));
    strSqlStatement.append("' ");
    sqlStatement->setSQL(strSqlStatement);

    strMdmStatus = "0";
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(rs->isNull(1) == true)
            {
                strMdmStatus = "NIJE ODREĐEN";
            }
            else
            {
                strMdmStatus = rs->getString(1);
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

    if(strMdmStatus != "0")
    {
        // Add Master Data Management information on selected customer QTreeListItem
        QString strMdmInfo = QString(tr("   MDM ... KupacId - "));
        strMdmInfo.append(QString::number(m_iKupacId));
        strMdmInfo.append(tr(" ... Status - "));
        strMdmInfo.append(QString::fromStdString(strMdmStatus));
        QTreeWidgetItem *itemNoMdmData = new QTreeWidgetItem();
        itemNoMdmData->setText(0, tr(""));
        itemNoMdmData->setText(1, strMdmInfo);
        itemNoMdmData->setText(2, tr(""));
        itemNoMdmData->setText(3, tr(""));
        itemNoMdmData->setText(4, tr(""));
        if(strMdmStatus == "NIJE ODREĐEN")
        {
            itemNoMdmData->setIcon(5, m_iconZuti);
        }
        else if(strMdmStatus == "OK")
        {
            itemNoMdmData->setIcon(5, m_iconZeleni);
        }
        else if(strMdmStatus == "DIRTY")
        {
            itemNoMdmData->setIcon(5, m_iconCrveni);
        }
        else if(strMdmStatus == "INVALID")
        {
            itemNoMdmData->setIcon(5, m_iconAdressValid);
        }
        else
        {
            itemNoMdmData->setIcon(5, m_iconTransparent);
        }
        itemDonatStranka->addChild(itemNoMdmData);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}

// [ Imovina ]
void FrmDonatMenu::popuniSveImovine()
{
    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    string strSqlStatement;

    strSqlStatement.append("SELECT I.IMOVINA_ID, I.NAD_IMOVINA_ID, I.STATUS_ID, I.NIVO, ");
    strSqlStatement.append(" NVL(TO_CHAR(I.DATUM_OD,'DD.MM.YYYY'),'-') DATUM_OD, ");
    strSqlStatement.append(" NVL(TO_CHAR(I.DATUM_DO,'DD.MM.YYYY HH24:MI'),'-') DATUM_DO, P.NAZIV ");
    strSqlStatement.append("FROM IMOVINA I, PRODUKTI P ");
    strSqlStatement.append("WHERE I.PRODUKT_ID = P.PRODUKT_ID ");
    if(m_bAktivnaImovina == true)
    {
        strSqlStatement.append(" AND I.STATUS_ID > 0 ");
    }
    else
    {
        strSqlStatement.append(" AND I.STATUS_ID = 0 ");
    }
    strSqlStatement.append(" AND I.NIVO>0 ");
    strSqlStatement.append(" AND GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    strSqlStatement.append(" AND P.GPRODUKATA_ID NOT IN (4) ");
    strSqlStatement.append(" ORDER BY NIVO, IMOVINA_ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listImovina;
    string strDatumDo;
    string strDatumOd;
    string strNaziv;
    string strImovinaNaziv;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            strDatumDo = rs->getString(6);
            strDatumOd = rs->getString(5);
            strNaziv = rs->getString(7);
            if(strDatumDo == "-")
            {
                if(strDatumOd == "-")
                {
                    strImovinaNaziv = strNaziv;
                }
                else
                {
                    strImovinaNaziv = strDatumOd + " ... " + strNaziv;
                }
            }
            else
            {
                strImovinaNaziv = strDatumDo + " ... " + strNaziv;
            }

            QTreeWidgetItem *itemImovina = new QTreeWidgetItem();
            itemImovina->setText(0, QString::fromStdString(strImovinaNaziv));
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
            else if (listImovina.at(ii)->text(3).toInt() == 2)
            {
                listImovina.at(ii)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OLOVKA.GIF")));
            }
            else if (listImovina.at(ii)->text(3).toInt() > 4)
            {
                listImovina.at(ii)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
            }

            popuniImovinaAtribute(listImovina.at(ii));
        }

        listImovina.first()->setSelected(true);
        ui->txtImovinaId->setText(listImovina.first()->text(1));
        m_iImovinaId = listImovina.first()->text(1).toUInt();
        m_iImovinaIdStatus = listImovina.first()->text(3).toInt();
        ui->treeImovina->insertTopLevelItems(0, listImovina);
        ui->treeImovina->setCurrentItem(listImovina.first());
//        ui->treeImovina->expandAll();
        ui->treeImovina->collapseAll();

        popuniImovinaStatus();
    }
}
void FrmDonatMenu::popuniImovinaAtribute(QTreeWidgetItem *itemImovina)
{
    string strSqlStatement;
    strSqlStatement.append("SELECT /*+ RULE */ ATRIBUT_ID, IMOVATR_ID, SHOWN_VALUE, NAZIV, TVRATR_ID, WWMS_NAZIV ");
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
void FrmDonatMenu::popuniImovinaStatus()
{
    if(m_iImovinaId == 0)
    {
        return;
    }

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
            ui->txtImovinaStatus->setText(QString::fromStdString(rs->getString(6)));
            ui->txtImovinaAktivnaOd->setText(QString::fromStdString(rs->getString(2)));
            string strDatumDo;
            strDatumDo = rs->getString(3);
            if(strDatumDo != "0")
            {
                ui->txtImovinaAktivnaDo->setText(QString::fromStdString(strDatumDo));
            }
            else
            {
                if(rs->getString(4) != "0")
                {
                    ui->txtImovinaSuspendiranaOd->setText(QString::fromStdString(rs->getString(4)));
                }
                if(rs->getString(5) != "0")
                {
                    ui->txtImovinaSuspendiranaDo->setText(QString::fromStdString(rs->getString(5)));
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

void FrmDonatMenu::popuniStrankaAdslStatus()
{
    ui->txtAdslStatus->clear();

    string strTelefonskiBroj;
    strTelefonskiBroj = m_strTelefonskiBroj;
//    try
//    {
//        strTelefonskiBroj = m_strTelefonskiBroj.substr(0, 10);
//    }
//    catch(exception& e)
//    {
//        strTelefonskiBroj.clear();
//    }
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
        ui->txtAdslStatus->setText(tr("Potrebno ažurirati podatke u DIS-u"));
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

        ui->txtAdslStatus->setText(QString::fromStdString(strDescription));
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}
void FrmDonatMenu::popuniStrankaIptvStatus()
{
    ui->txtMaxTvStatus->clear();

    string strTelefonskiBroj;
    strTelefonskiBroj = m_strTelefonskiBroj;
//    try
//    {
//        strTelefonskiBroj = m_strTelefonskiBroj.substr(0, 10);
//    }
//    catch(exception& e)
//    {
//        strTelefonskiBroj.clear();
//    }
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
       ui->txtMaxTvStatus->setText(tr("Potrebno ažurirati podatke u DIS-u"));
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

        ui->txtMaxTvStatus->setText(QString::fromStdString(strDescription));
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}

void FrmDonatMenu::popuniStrankaPoruke()
{
    ui->treeInfoItems->clear();

    QTreeWidgetItem *itemMarketing = new QTreeWidgetItem();
    itemMarketing->setText(0, tr("MARKETING"));
    itemMarketing->setIcon(1, m_iconTransparent);
    itemMarketing->setText(2, tr(""));
    itemMarketing->setText(3, tr(""));

    QTreeWidgetItem *itemTehnika = new QTreeWidgetItem();
    itemTehnika->setText(0, tr("TEHNIKA"));
    itemTehnika->setIcon(1, m_iconTransparent);
    itemTehnika->setText(2, tr(""));
    itemTehnika->setText(3, tr(""));

    QTreeWidgetItem *itemOstalo = new QTreeWidgetItem();
    itemOstalo->setText(0, tr("OSTALO"));
    itemOstalo->setIcon(1, m_iconTransparent);
    itemOstalo->setText(2, tr(""));
    itemOstalo->setText(3, tr(""));

    string strSqlStatement;
    strSqlStatement.append("DELETE FROM TEMP_GET_MESSAGES");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        sqlStatement->executeQuery();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("BEGIN VRATI_INFO_PORUKE(:kupac_id_par, :gimovine_id_par); END; ");
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setUInt(1, m_iKupacId);
        sqlStatement->setUInt(2, m_iGrupaImovineId);
        // sqlStatement->registerOutParam(3, OCCISTRING);
        sqlStatement->executeUpdate();
        // string strBatchPoruka = sqlStatement->getString(3);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }


    strSqlStatement.clear();
    strSqlStatement.append("SELECT ROWNUM, NVL(TEKST,'xxxxx') TEKST, NVL(TIP,3) TIP FROM temp_get_messages order by TIP desc,tekst");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            switch(rs->getInt(3))
            {
                case 1:	 // Tehnicka poruka
                {
                    QTreeWidgetItem *itemInfoTehnika = new QTreeWidgetItem();
                    itemInfoTehnika->setText(0, QString::fromStdString(rs->getString(2)));
                    itemInfoTehnika->setIcon(1, m_iconTransparent);
                    itemInfoTehnika->setText(2, tr(""));
                    itemInfoTehnika->setText(3, tr(""));
                    itemTehnika->addChild(itemInfoTehnika);
                    break;
                }
                case 2:  // Marketinska poruka
                {
                    QTreeWidgetItem *itemInfoMarketing = new QTreeWidgetItem();
                    itemInfoMarketing->setText(0, QString::fromStdString(rs->getString(2)));
                    itemInfoMarketing->setIcon(1, m_iconTransparent);
                    itemInfoMarketing->setText(2, tr(""));
                    itemInfoMarketing->setText(3, tr(""));
                    itemMarketing->addChild(itemInfoMarketing);
                    break;
                }
                default:  // Ostale poruka
                {
                    QTreeWidgetItem *itemInfoOstalo = new QTreeWidgetItem();
                    itemInfoOstalo->setText(0, QString::fromStdString(rs->getString(2)));
                    itemInfoOstalo->setIcon(1, m_iconTransparent);
                    itemInfoOstalo->setText(2, tr(""));
                    itemInfoOstalo->setText(3, tr(""));
                    itemOstalo->addChild(itemInfoOstalo);
                    break;
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

    ui->treeInfoItems->insertTopLevelItem(0, itemOstalo);
    ui->treeInfoItems->insertTopLevelItem(0, itemTehnika);
    ui->treeInfoItems->insertTopLevelItem(0, itemMarketing);
    ui->treeInfoItems->expandAll();
}
void FrmDonatMenu::popuniStrankaPoruku(string strSqlStatement)
{
    if(strSqlStatement.empty() == true)
    {
        return;
    }
    if(strSqlStatement.length() == 0)
    {
        return;
    }

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
    if(strPoruka.empty() == true)
    {
        return;
    }
    if(strPoruka.length() == 0)
    {
        return;
    }
    if(strPoruka == ".")
    {
        return;
    }


    QTreeWidgetItem *itemInfoStatus = new QTreeWidgetItem();
    itemInfoStatus->setText(0, QString::fromStdString(strPoruka));
    itemInfoStatus->setIcon(1, m_iconTransparent);
    itemInfoStatus->setText(2, tr(""));
    itemInfoStatus->setText(3, tr(""));
    ui->treeInfoItems->insertTopLevelItem(0, itemInfoStatus);
}
void FrmDonatMenu::popuniInfoZahtjevi()
{
    ui->treeInfoItems->clear();

    if(m_iKupacId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT /*+ RULE */ SPORAZUM_ID, NVL(TO_CHAR(DATUM_OD, 'DD.MM.YYYY HH24:MI'), 'xx.xx.xxxx') DATUM, ");
    strSqlStatement.append(" BROJ_DOK, STANJE, HEAD_ID, KANAL_PRODAJE ");
    strSqlStatement.append(" FROM TAB_PREGLED_SPORAZUMI ");
    strSqlStatement.append(" WHERE KUPAC_ID = ");
    strSqlStatement.append(cttl::itos(m_iKupacId));
    strSqlStatement.append(" AND TSPORAZUMA_ID IN (1, 4, 8) ");
    strSqlStatement.append(" AND STANJE IS NOT NULL ");
    strSqlStatement.append(" ORDER BY SPORAZUM_ID DESC ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listInfoStatus;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            string strInfo;
            strInfo.append(rs->getString(2));
            strInfo.append("     ");
            strInfo.append(rs->getString(3));
            strInfo.append("      ( ");
            strInfo.append(rs->getString(6));
            strInfo.append(" )");
            string strStanje;
            strStanje = rs->getString(4);
            std::transform(strStanje.begin(), strStanje.end(), strStanje.begin(), ::toupper);

            QTreeWidgetItem *itemInfoStatus = new QTreeWidgetItem();
            itemInfoStatus->setText(0, QString::fromStdString(strInfo));
            if(strStanje == "PROVJERA")
            {
                itemInfoStatus->setIcon(1, m_iconZuti);
            }
            else if (strStanje == "REALIZACIJA")
            {
                itemInfoStatus->setIcon(1, m_iconZuti);
            }
            else if (strStanje == "REALIZIRANO")
            {
                itemInfoStatus->setIcon(1, m_iconZeleni);
            }
            else if (strStanje == "STORNIRAN")
            {
                itemInfoStatus->setIcon(1, m_iconCrveni);
            }
            else
            {
                itemInfoStatus->setIcon(1, m_iconAdressValid);
            }
            itemInfoStatus->setText(2, QString::number(rs->getUInt(1)));
            itemInfoStatus->setText(3, tr(""));
            listInfoStatus.append(itemInfoStatus);
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

    if(!listInfoStatus.empty())
    {
        ui->treeInfoItems->insertTopLevelItems(0, listInfoStatus);
//        ui->treeInfoItems->setCurrentItem(listInfoStatus.first());
        ui->treeImovina->expandAll();
//        ui->treeImovina->collapseAll();
    }

}

// Vrati indikator ugovorne obveze
int FrmDonatMenu::vratiIndikatorZaprikazUgovorneObveze(const unsigned int iGrupaImovineId, string strTip)
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
string FrmDonatMenu::vratiChurnPhoneRizik(const string strPhoneNumber)
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

// [ Public Member Functions ]

// [ Event Handlers ]

// [ 0 Donat fake form menu events ]
void FrmDonatMenu::on_btnPromjenaZaporke_clicked()
{
    // Show Donat user password change
    FrmDonatPasswordChange *frmDonatPasswordChange = new FrmDonatPasswordChange();
    frmDonatPasswordChange->exec();
    delete frmDonatPasswordChange;
}
void FrmDonatMenu::on_btnAbout_clicked()
{
    // Show Donat about form
    Log::FrmDonatAbout *frmAbout = new Log::FrmDonatAbout();
    frmAbout->exec();
    delete frmAbout;
}
void FrmDonatMenu::on_btnOdrzavanje_clicked()
{
    // Show Donat user roles
    FrmDonatUserRole *frmDonatUserRoles = new FrmDonatUserRole();
    frmDonatUserRoles->exec();
    delete frmDonatUserRoles;
}
void FrmDonatMenu::on_btnSifarnik_clicked()
{

}


// [ 1 Buttons events ]
void FrmDonatMenu::on_btnTcom_clicked()
{

}
void FrmDonatMenu::on_btnTmobile_clicked()
{

}

void FrmDonatMenu::on_btnTrazi_clicked()
{
    if(ui->txtFltNaziv->text().isEmpty())
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
            int UNUSED(iDonatSearchNumber) = ui->txtFltNaziv->text().toInt(&bFltDonatSearchIsNumber);
            if(bFltDonatSearchIsNumber == true)
            {
                if(ui->txtFltNaziv->text().startsWith(tr("0")) == true)
                {
                    m_SearchMode = TraziPoBrojTelefona;
                    traziDonatKorisnikaPoBrojuTelefona();
                }
                else
                {
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

    int row = ui->treeStranke->children().count();
    if(row > 0)
    {
        ui->btnResultInfo->setText(QString::fromStdString("1 ... " + cttl::itos(row)));
    }
    else
    {
        ui->btnResultInfo->setText(tr("0 ... (0)"));
    }

    setCursor(Qt::ArrowCursor);
}
void FrmDonatMenu::on_btnDonatKon_clicked()
{
    if(g_GRP_TIP == 0 || g_GRP_TIP == 3)
    {
        int iCount = 0;
        string strSqlStatement;
        strSqlStatement.append("SELECT COUNT(*) BROJ FROM KONTAKT_GRUPA_KOR WHERE KOR_ID = '");
        strSqlStatement.append(g_DonatUser);
        strSqlStatement.append("'  AND ROLA_TIP IN (1, 2) AND KOR_TIP = 1 ");

        Statement *sqlStatement = g_DonatConn->createStatement();
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            if(rs->next())
            {
                iCount = rs->getInt(1);
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

        if(iCount == 0)
        {
            QMessageBox::information(this, tr("DONAT - KON Grupe"),
                                     tr("NE NALAZITE SE U NIJEDNOJ KON GRUPI ... MOLIM JAVITE SE SVOM ADMINISTRATORU UNUTAR PRODAJE"),
                                           QMessageBox::Close);
            return;
        }
        else if(iCount == 1)
        {
            strSqlStatement.append("SELECT ROLA_TIP, GRUPA_ID, GRUPA_NAZ FROM KONTAKT_GRUPA_KOR WHERE KOR_ID = '");
            strSqlStatement.append(g_DonatUser);
            strSqlStatement.append("'  AND ROLA_TIP IN (1, 2) AND KOR_TIP = 1 ");
            sqlStatement = g_DonatConn->createStatement();
            sqlStatement->setSQL(strSqlStatement);

            try
            {
                ResultSet *rs = sqlStatement->executeQuery();
                if(rs->next())
                {
                    g_GRP_TIP = rs->getInt(1);
                    g_GRP_NO  = rs->getInt(2);
                    g_GRP_NAZ = rs->getString(3);
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
        else if(iCount > 1)
        {
            // Show Donat kontact role selection form
            Kontakt::FrmKontaktniCentarUser *frmKontaktniCentarUser = new Kontakt::FrmKontaktniCentarUser(this, 0);
            //frmKontaktniCentarUser->exec();
            frmKontaktniCentarUser->show();
            //delete frmKontaktniCentarUser;
            return;
        }
    }


//    XX = AKT_TEL_NO
//    If XX = "0" Then
//        XX = ""
//    End If

//    Dim FR As New C_KON_CENTAR
//    'FR.F_ROLA_TIP.Text = 0
//    FR.P_UPIT.Text = XX
//    FR.F_KUPAC_ID.Text = 0		  ' P_TIP1.Text
//    FR.F_GIMOVINE_ID.Text = 0		  'GIM_ID
//    If XX <> "" Then
//        'FR.PROVJERA_BOTUNA()
//        FR.POPUNA_UPIT_PR()
//    End If
//    FR.Show()


    Kontakt::FrmKontaktniCentar *frmDonatKontaktCentar = new Kontakt::FrmKontaktniCentar(this, m_strTelefonskiBroj);
    frmDonatKontaktCentar->show();
//    delete frmDonatKontaktCentar;
}
void FrmDonatMenu::on_btnDonatFiz_clicked()
{

}
void FrmDonatMenu::on_btnDonatFir_clicked()
{

}

void FrmDonatMenu::on_btnInfo_clicked()
{
    m_InfoMode = PrikaziInfo;
    popuniStrankaPoruke();
}
void FrmDonatMenu::on_btnZahtjevi_clicked()
{
    m_InfoMode = PrikaziInfoZahtjevi;
    popuniInfoZahtjevi();
}
void FrmDonatMenu::on_btnSmetnje_clicked()
{
    m_InfoMode = PrikaziInfoSmetnje;
    ui->treeInfoItems->clear();
}
void FrmDonatMenu::on_btnKontakti_clicked()
{
    m_InfoMode = PrikaziInfoKontakti;
    ui->treeInfoItems->clear();
}
void FrmDonatMenu::on_btnOsobe_clicked()
{
    m_InfoMode = PrikaziInfoOsobe;
    ui->treeInfoItems->clear();
}

void FrmDonatMenu::on_btnDonatStatus_clicked()
{
    if(m_InfoMode != PrikaziInfoZahtjevi)
    {
        return;
    }

    if(ui->treeInfoItems->selectedItems().isEmpty())
    {
        return;
    }

    QTreeWidgetItem *selectedItem = ui->treeInfoItems->selectedItems().first();
    unsigned int  iSporazumId = selectedItem->text(2).toUInt();

    if(iSporazumId == 0)
    {
        return;
    }

    // Show Donat contract status
    Sporazumi::FrmDonatPregled *frmDonatPregled = new Sporazumi::FrmDonatPregled(iSporazumId, this);
    frmDonatPregled->exec();
    delete frmDonatPregled;
}
void FrmDonatMenu::on_btnWwmsStatus_clicked()
{
    if(m_InfoMode != PrikaziInfoZahtjevi)
    {
        return;
    }

    if(ui->treeInfoItems->selectedItems().isEmpty())
    {
        return;
    }

    QTreeWidgetItem *selectedItem = ui->treeInfoItems->selectedItems().first();
    unsigned int  iSporazumId = selectedItem->text(2).toUInt();

    if(iSporazumId == 0)
    {
        return;
    }

    // Show Donat - WWMS order management processes
    Sporazumi::FrmWwmsPregled *frmWwmsPregled = new Sporazumi::FrmWwmsPregled(iSporazumId, 1, this);
    frmWwmsPregled->exec();
    delete frmWwmsPregled;
}
void FrmDonatMenu::on_btnDonatProcesi_clicked()
{
    if(m_InfoMode != PrikaziInfoZahtjevi)
    {
        return;
    }

    if(ui->treeInfoItems->selectedItems().isEmpty())
    {
        return;
    }

    QTreeWidgetItem *selectedItem = ui->treeInfoItems->selectedItems().first();
    unsigned int  iSporazumId = selectedItem->text(2).toUInt();

    if(iSporazumId == 0)
    {
        return;
    }

    // Show Donat order management processes
    Sporazumi::FrmPregledProcesa *frmPregledProcesa = new Sporazumi::FrmPregledProcesa(iSporazumId, this);
    frmPregledProcesa->exec();
    delete frmPregledProcesa;
}

void FrmDonatMenu::on_btnAdslStatus_clicked()
{

}
void FrmDonatMenu::on_btnMaxTvStatus_clicked()
{

}

void FrmDonatMenu::on_btnStatusBarDonatUser_clicked()
{
}
void FrmDonatMenu::on_btnStatusBarDonatDabase_clicked()
{
    // Change Donat envirorment with new Login form
    Log::FrmDonatLogin frmLogIn;
    if (frmLogIn.exec() == QDialog::Accepted)
    {
        // ui->btnStatusBarDonatUser->setText(QString::fromStdString(g_DonatDatebase) + tr(" - ") + QString::fromStdString(g_DonatUser));
        ui->btnStatusBarDonatDabase->setToolTip(QString::fromStdString(g_DonatDatebase) + tr(" - ") + QString::fromStdString(g_DonatUser));
        ui->btnStatusBarDonatUser->setText(QString::fromStdString(g_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_KORISNIK_NAZ));
    }
    else
    {
        return;
    }
}

void FrmDonatMenu::on_btnPromjenaKanalaProdaje_clicked()
{
    // Show Donat form for user sales channel change
    Kontakt::FrmKanalProdajeKorisnik *frmKanalProdajeKorisnik = new Kontakt::FrmKanalProdajeKorisnik(this);
    frmKanalProdajeKorisnik->exec();
    delete frmKanalProdajeKorisnik;

    ui->btnStatusBarDonatUser->setText(QString::fromStdString(g_UNIO_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_KORISNIK_NAZ));
}

void FrmDonatMenu::on_btnLogiraniKorisnik_clicked()
{
    // Set back login user
    g_UNIO_REGIJA_ID = g_REGIJA_ID;
    g_UNIO_REGIJA_NAZ = g_REGIJA_NAZ;
    g_UNIO_ZUPANIJA_ID = g_ZUPANIJA_ID;
    g_UNIO_ZUPANIJA_NAZ = g_ZUPANIJA_NAZ;
    g_UNIO_KANAL_ID = g_KANAL_ID;
    g_UNIO_KANAL_NAZ = g_KANAL_NAZ;
    g_UNIO_ORGJED_ID = g_ORGJED_ID;
    g_UNIO_ORGJED_NAZ = g_ORGJED_NAZ;
    g_UNIO_KORISNIK_ID = g_KORISNIK_ID;
    g_UNIO_KORISNIK_NAZ = g_KORISNIK_NAZ;

    ui->btnStatusBarDonatUser->setText(QString::fromStdString(g_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_KORISNIK_NAZ));
}

void FrmDonatMenu::on_btnBundleInfo_clicked()
{
    // Show Donat bundle information form
    Sporazumi::FrmBundleInfo *frmBundleInfo = new Sporazumi::FrmBundleInfo(m_iKupacId, this);
    frmBundleInfo->exec();
    delete frmBundleInfo;
}



// [3. Filter buttons events]
void FrmDonatMenu::on_btnFltNaziv_clicked()
{
    ui->lblFltNaziv->setText(tr("NAZIV"));
    m_SearchMode = TraziPoNazivKorisnika;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltTelefon_clicked()
{
    ui->lblFltNaziv->setText(tr("TELEFON"));
    m_SearchMode = TraziPoBrojTelefona;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltMbJmbg_clicked()
{
    ui->lblFltNaziv->setText(tr("MB-JMBG"));
    m_SearchMode = TraziPoJmbg;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltOib_clicked()
{
    ui->lblFltNaziv->setText(tr("OIB"));
    m_SearchMode = TraziPoOib;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltUlogaStrankeId_clicked()
{
    ui->lblFltNaziv->setText(tr("ULOGA ID"));
    m_SearchMode = TraziPoUlogaStrankeId;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltTicketId_clicked()
{
    ui->lblFltNaziv->setText(tr("TICKET"));
    m_SearchMode = TraziPoTicketId;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltAssetId_clicked()
{
    ui->lblFltNaziv->setText(tr("ASSET"));
    m_SearchMode = TraziPoAssetId;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltGrupa_clicked()
{
    ui->lblFltNaziv->setText(tr("GRUPNA"));
    m_SearchMode = TraziPoGrupna;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltHijerahija_clicked()
{
    ui->lblFltNaziv->setText(tr("HIJER."));
    m_SearchMode = TraziPoHijerahija;
    ui->txtFltNaziv->setFocus();
}
void FrmDonatMenu::on_btnFltUlica_clicked()
{
}
void FrmDonatMenu::on_btnFltKolokacija_clicked()
{
    ui->lblFltNaziv->setText(tr("KOLOKAC"));
    m_SearchMode = TraziPoNazivKorisnika;
    ui->txtFltNaziv->setFocus();
}

void FrmDonatMenu::on_btnAktivnaGrupaImovine_clicked()
{
    m_bAktivnaGrupaImovine = true;
    m_bAktivnaImovina = true;
    popuniStrankaSveKlase();
}
void FrmDonatMenu::on_btnNeaktivnaGrupaImovine_clicked()
{
    m_bAktivnaGrupaImovine = false;
    m_bAktivnaImovina = false;
    popuniStrankaSveKlase();
}
void FrmDonatMenu::on_btnAktivnaImovina_clicked()
{
    m_bAktivnaImovina = true;

    if(m_iGrupaImovineId == 0)
    {
        return;
    }
    ui->treeImovina->clear();
    ui->txtImovinaId->clear();
    ui->txtImovinaStatus->clear();
    ui->txtImovinaAktivnaOd->clear();
    ui->txtImovinaAktivnaDo->clear();
    ui->txtImovinaSuspendiranaOd->clear();
    ui->txtImovinaSuspendiranaDo->clear();

    popuniSveImovine();
}
void FrmDonatMenu::on_btnNeaktivnaImovina_clicked()
{
    m_bAktivnaImovina = false;

    if(m_iGrupaImovineId == 0)
    {
        return;
    }
    ui->treeImovina->clear();
    ui->txtImovinaId->clear();
    ui->txtImovinaStatus->clear();
    ui->txtImovinaAktivnaOd->clear();
    ui->txtImovinaAktivnaDo->clear();
    ui->txtImovinaSuspendiranaOd->clear();
    ui->txtImovinaSuspendiranaDo->clear();

    popuniSveImovine();
}
void FrmDonatMenu::on_btnExpandImovina_clicked()
{
    if(m_bImovinaExpand == true)
    {
        ui->treeImovina->expandAll();
        m_bImovinaExpand = false;
    }
    else
    {
        ui->treeImovina->collapseAll();
        m_bImovinaExpand = true;
    }
}
void FrmDonatMenu::on_btnGrupeImovineView_clicked()
{
    if(ui->fraGrupeImovine->isVisible() == true)
    {
        // Show Donat Grupe Imovine form
        Stranka::FrmStrankaGrupeImovine *frmStrankaGrupeImovine = new Stranka::FrmStrankaGrupeImovine(this);
        frmStrankaGrupeImovine->exec();
        delete frmStrankaGrupeImovine;
    }
    else
    {
        ui->fraGrupaImovineDetaljno->setVisible(false);
        ui->fraGrupeImovine->setVisible(true);
    }
}
void FrmDonatMenu::on_btnAssetView_clicked()
{
    ui->fraGrupaImovineDetaljno->setVisible(true);
    ui->fraGrupeImovine->setVisible(false);
}
void FrmDonatMenu::on_btnUgovorneObveze_clicked()
{
    if(m_iKupacId == 0)
        return;

    // Show Donat about form
    Kontakt::FrmUgovorneObveze *frmUgovorneObveze = new Kontakt::FrmUgovorneObveze(m_iKupacId, m_iGrupaImovineId, this);
    frmUgovorneObveze->exec();
    delete frmUgovorneObveze;
}
void FrmDonatMenu::on_btnStrankaZurnal_clicked()
{
    if(m_iKupacId == 0)
        return;

    if(m_iGrupaImovineId == 0)
        return;

    // Show Donat customer jurnal form
    Stranka::FrmStrankaZurnal *frmStrankaZurnal = new Stranka::FrmStrankaZurnal(m_iKupacId, m_iGrupaImovineId, this);
    frmStrankaZurnal->exec();
    delete frmStrankaZurnal;
}
void FrmDonatMenu::on_btnImovinaEdit_clicked()
{
    if(m_iGrupaImovineId == 0)
        return;

    // Show Donat grupa imovine atributi edit form
    Sporazumi::FrmGrupaImovineAtributi *frmGrupaImovineAtributi = new Sporazumi::FrmGrupaImovineAtributi(m_iGrupaImovineId, m_iKupacId, this);
    frmGrupaImovineAtributi->exec();
    delete frmGrupaImovineAtributi;
}

void FrmDonatMenu::on_btnF2x_clicked()
{
    string strSmije = "0";
    string strUrl;

    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT SMIJE_LI_F2X (");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    strSqlStatement.append(") SMIJE FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strSmije = rs->getString(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(strSmije != "0")
    {
        QMessageBox::information(this, tr("DONAT - F2X"),
                                       QString::fromStdString(strSmije),
                                       QMessageBox::Close);
        return;
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT DNT_PARAM.GET('F2X_URL') F2X FROM DUAL");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(!rs->isNull(1))
            {
                strUrl = rs->getString(1);
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

    if(strUrl.length() > 0)
    {
        QString strF2xUrl = QString::fromStdString(strUrl);
        strF2xUrl = strF2xUrl.trimmed();
//        strF2xUrl.replace(tr("http:"), tr("https:"));
//        strF2xUrl.replace(tr(" "), tr(""));
        strF2xUrl.replace(tr("192.168.253.96"), tr("webvas.t.ht.hr"));
        strF2xUrl.append(tr("&phone="));
        strF2xUrl.append(QString::fromStdString(m_strTelefonskiBroj));
        strF2xUrl.append(tr("&agent="));
        strF2xUrl.append(QString::fromStdString(g_KORISNIK_ID));

        QDesktopServices::openUrl(QUrl(strF2xUrl));
    }

}

void FrmDonatMenu::on_btnSviKupci_toggled(bool checked)
{
    if(checked == true)
    {
        if(this->ui->btnAktivniKupci->isChecked() == true)
        {
            this->ui->btnAktivniKupci->toggle();
        }
        m_bSearchAktivneKupce = false;
    }
}
void FrmDonatMenu::on_btnAktivniKupci_toggled(bool checked)
{
    if(checked == true)
    {
        if(this->ui->btnSviKupci->isChecked() == true)
        {
            this->ui->btnSviKupci->toggle();
        }
        m_bSearchAktivneKupce = true;
    }
}

void FrmDonatMenu::on_btnIzmjenaAtributa_clicked()
{
    if(m_iImovinaId == 0)
        return;

    if(m_iGrupaImovineId == 0)
        return;

    // Show Donat about form
    Sporazumi::FrmGrupaImovineAtributi *frmIzmjenaAtributa = new Sporazumi::FrmGrupaImovineAtributi(m_iGrupaImovineId, m_iImovinaId, this);
    frmIzmjenaAtributa->exec();
    delete frmIzmjenaAtributa;
}

void FrmDonatMenu::on_txtFltNaziv_textEdited(const QString &text)
{
    QLineEdit *le = qobject_cast<QLineEdit *>(sender());
    if(!le) return;
    le->setText(text.toUpper());
}


void FrmDonatMenu::on_treeStranke_itemPressed(QTreeWidgetItem *itemDonatStranka, int UNUSED(column))
{
    setCursor(Qt::BusyCursor);

    if(itemDonatStranka->parent())
    {
        return;
    }

//    QVariant strankaId = itemDonatStranka->text(0);
    m_iStrankaId = itemDonatStranka->text(0).toUInt();

    clearDonatStranka();
    popuniStrankaUlogeStranaka();
    popuniStrankaZastupnika();
    provjeriOib();
    popuniStrankaMdm(itemDonatStranka);

//	popuniStrankaLoyalty();
//	popuniStrankaTarifniStatus();
    popuniStrankaSveKlase();

    popuniStrankaAdslStatus();
    popuniStrankaIptvStatus();
//	popuniStrankaPenali();
//	popuniStrankaPoruke();

    switch (m_InfoMode)
    {
        case PrikaziInfo :
        {
            popuniStrankaPoruke();
            break;
        }
        case PrikaziInfoZahtjevi :
        {
            popuniInfoZahtjevi();
            break;
        }
        default :
        {
            break;
        }
    }

    setCursor(Qt::ArrowCursor);
}

void FrmDonatMenu::on_treeAsset_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    m_iGrupaImovineId = item->text(4).toUInt();
    m_strTelefonskiBroj = item->text(7).toStdString();
    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    ui->treeImovina->clear();
    ui->txtImovinaId->clear();
    ui->txtImovinaStatus->clear();
    ui->txtImovinaAktivnaOd->clear();
    ui->txtImovinaAktivnaDo->clear();
    ui->txtImovinaSuspendiranaOd->clear();
    ui->txtImovinaSuspendiranaDo->clear();
    ui->txtGrupaImovineId->setText(item->text(4));
    ui->txtUloge->setText(item->text(0));

    popuniSveImovine();

    popuniStrankaAdslStatus();
    popuniStrankaIptvStatus();
}
void FrmDonatMenu::on_treeGrupeImovine_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    m_iGrupaImovineId = item->text(3).toUInt();
    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    ui->fraGrupaImovineDetaljno->setVisible(true);
    ui->fraGrupeImovine->setVisible(false);

    // To Do clear Grupa imovine
    clearDonatStrankaAsset();

    popuniZaGrupuImovine();
}
void FrmDonatMenu::on_treeImovina_itemPressed(QTreeWidgetItem *itemImovina, int UNUSED(column))
{
    setCursor(Qt::BusyCursor);

    if(!itemImovina->text(1).isEmpty())
    {
        ui->txtImovinaId->clear();
        ui->txtImovinaStatus->clear();
        ui->txtImovinaAktivnaOd->clear();
        ui->txtImovinaAktivnaDo->clear();
        ui->txtImovinaSuspendiranaOd->clear();
        ui->txtImovinaSuspendiranaDo->clear();

        m_iImovinaId = itemImovina->text(1).toUInt();
        ui->txtImovinaId->setText(itemImovina->text(1));
        popuniImovinaStatus();
    }
    setCursor(Qt::ArrowCursor);
}
void FrmDonatMenu::on_treeImovina_itemDoubleClicked(QTreeWidgetItem *itemImovina, int UNUSED(column))
{
    m_iImovinaId = itemImovina->text(1).toUInt();

    if(m_iImovinaId == 0)
        return;

    if(m_iGrupaImovineId == 0)
        return;

    // Show Donat about form
    Sporazumi::FrmGrupaImovineAtributi *frmIzmjenaAtributa = new Sporazumi::FrmGrupaImovineAtributi(m_iGrupaImovineId, m_iImovinaId, this);
    frmIzmjenaAtributa->exec();
    delete frmIzmjenaAtributa;
}

// [ Menu Event Handlers ]
void FrmDonatMenu::on_btnMnuZahtjevPregled_clicked()
{
    if(m_iKupacId == 0)
    {
        return;
    }
    // Show Donat pregled zahtjeva
    Sporazumi::FrmZahtjeviPregled *frmDonatZahtjeviPregled = new Sporazumi::FrmZahtjeviPregled(m_iKupacId, this);
    frmDonatZahtjeviPregled->exec();
    delete frmDonatZahtjeviPregled;

    // Old Form
//    Sporazumi::FrmPregledZahtjeva *frmDonatPregledZahtjeva = new Sporazumi::FrmPregledZahtjeva(1, m_iKupacId, this);
//    frmDonatPregledZahtjeva->show();
////    delete frmDonatPregledZahtjeva;
}
void FrmDonatMenu::on_btnMnuZahtjevNemogucnost_clicked()
{
    if(m_iKupacId == 0)
    {
        return;
    }
    // Show Donat pregled nemogucnosti zahtjeva
    Sporazumi::FrmZahtjeviNemoguci *frmDonatZahtjeviNemoguci = new Sporazumi::FrmZahtjeviNemoguci(this);
    frmDonatZahtjeviNemoguci->exec();
    delete frmDonatZahtjeviNemoguci;
}
void FrmDonatMenu::on_btnMnuUgovorPregled_clicked()
{
    if(m_iKupacId == 0)
    {
        return;
    }
    // Show Donat pregled ugovora
    Sporazumi::FrmUgovoriPregled *frmDonatUgovoriPregled = new Sporazumi::FrmUgovoriPregled(m_iKupacId, this);
    frmDonatUgovoriPregled->exec();
    delete frmDonatUgovoriPregled;
}
void FrmDonatMenu::on_btnMnuUgovorSklapanje_clicked()
{
    if(m_iKupacId == 0)
    {
        return;
    }
    // Show Donat pregled ugovora za ugovaranje
    Sporazumi::FrmUgovoriUgovaranje *frmDonatUgovoriUgovaranje = new Sporazumi::FrmUgovoriUgovaranje(this);
    frmDonatUgovoriUgovaranje->exec();
    delete frmDonatUgovoriUgovaranje;
}
void FrmDonatMenu::on_btnMnuObavijestSlanje_clicked()
{
    if(m_iKupacId == 0)
    {
        return;
    }
    // Show Donat pregled obavijesti za slanje
    Sporazumi::FrmObavijestiSlanje *frmDonatObavijestiSlanje = new Sporazumi::FrmObavijestiSlanje(this);
    frmDonatObavijestiSlanje->exec();
    delete frmDonatObavijestiSlanje;
}
void FrmDonatMenu::on_btnMnuObavijestPoslane_clicked()
{
    if(m_iKupacId == 0)
    {
        return;
    }
    // Show Donat pregled obavijesti koje su poslane
    Sporazumi::FrmObavijestiPoslane *frmDonatObavijestiPoslane = new Sporazumi::FrmObavijestiPoslane(this);
    frmDonatObavijestiPoslane->exec();
    delete frmDonatObavijestiPoslane;
}
void FrmDonatMenu::on_btnMnuPregledPregledN_clicked()
{
    // Show Donat pregled zahtjeva newr
    Sporazumi::FrmPregledN *frmDonatZahtjeviPregledN = new Sporazumi::FrmPregledN(this);
    frmDonatZahtjeviPregledN->show();
//    frmDonatZahtjeviPregledN->exec();
//    delete frmDonatZahtjeviPregledN;
}
void FrmDonatMenu::on_btnMnuPregledPregledKon_clicked()
{

}
void FrmDonatMenu::on_btnMnuZahtjevMax23_clicked()
{
//    if(m_iKupacId == 0)
//    {
//        return;
//    }
    // Show Donat form for new contract
    Kontakt::FrmDonatZahtjevAll *frmDonatZahtjevAll = new Kontakt::FrmDonatZahtjevAll(m_iStrankaId, m_iGrupaImovineId, this);
    frmDonatZahtjevAll->exec();
    delete frmDonatZahtjevAll;
}
void FrmDonatMenu::on_btnMnuZahtjevNovi_clicked()
{

}
void FrmDonatMenu::on_btnMnuPregled_clicked()
{
    // Show Donat form for contract detailed view
    Sporazumi::FrmPregledSporazuma *frmDonatPregledSporazuma = new Sporazumi::FrmPregledSporazuma(this);
    frmDonatPregledSporazuma->exec();
    delete frmDonatPregledSporazuma;
}
void FrmDonatMenu::on_btnMnuCpeOprema_clicked()
{
    // Show Donat form for customer CP view
    Kontakt::FrmCpeOprema *frmDonatCpeOprema = new Kontakt::FrmCpeOprema(m_iKupacId, this);
    frmDonatCpeOprema->exec();
    delete frmDonatCpeOprema;
}
void FrmDonatMenu::on_btnMnuFizickaStranka_clicked()
{
    // Show Donat form for customer view
    Stranka::FrmStrankaFiz *frmDonatStrankaFiz = new Stranka::FrmStrankaFiz(m_iStrankaId, this);
    frmDonatStrankaFiz->exec();
    delete frmDonatStrankaFiz;
}
void FrmDonatMenu::on_btnMnuPravnaOsoba_clicked()
{
    // Show Donat form for customer view
    Stranka::FrmStrankaPrav *frmDonatStrankaPra = new Stranka::FrmStrankaPrav(m_iStrankaId, this);
    frmDonatStrankaPra->exec();
    delete frmDonatStrankaPra;
}
void FrmDonatMenu::on_btnMnuTipStranke_clicked()
{
    // Show Donat form for type view
    Kontakt::FrmTipStranke *frmDonatTipStranke = new Kontakt::FrmTipStranke(m_iStrankaId, this);
    frmDonatTipStranke->exec();
    delete frmDonatTipStranke;
}
void FrmDonatMenu::on_btnMnuNovaUloga_clicked()
{

}
void FrmDonatMenu::on_btnMnuNovaUlogaStranka_clicked()
{

}
void FrmDonatMenu::on_btnMnuPorez_clicked()
{

}
void FrmDonatMenu::on_btnMnuPripadnostPodjeli_clicked()
{

}
void FrmDonatMenu::on_btnMnuAtributi_clicked()
{

}
void FrmDonatMenu::on_btnMnuOsf_clicked()
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
void FrmDonatMenu::on_btnMnuFilterListaN_clicked()
{

}
void FrmDonatMenu::on_btnMnuMdmPodaci_clicked()
{
    // Show Donat form for MDM data view
    Stranka::FrmMdm1 *frmMdm1 = new Stranka::FrmMdm1(m_strOib, m_iKupacId, m_iMdmId, this);
    frmMdm1->exec();
    delete frmMdm1;
}
void FrmDonatMenu::on_btnMnuKanalProdaje_clicked()
{
    // Show Donat form for sales channel viewr
    Kontakt::FrmKanalProdaje *frmKanalProdaje = new Kontakt::FrmKanalProdaje(1, this);
    frmKanalProdaje->exec();
    delete frmKanalProdaje;
}
void FrmDonatMenu::on_btnMnuPrigovorAdd_clicked()
{
    // Show Donat form for kreiranje prigovora
    Kontakt::FrmPrigovorAdd *frmPrigovorAdd = new Kontakt::FrmPrigovorAdd(this);
    frmPrigovorAdd->exec();
    delete frmPrigovorAdd;
}
void FrmDonatMenu::on_btnMnuPrigovorPregled_clicked()
{
    // Show Donat form for pregled prigovora
    Kontakt::FrmPrigovorPregled *frmPrigovorPregled = new Kontakt::FrmPrigovorPregled(this);
//    frmPrigovorPregled->exec();
//    delete frmPrigovorPregled;
    frmPrigovorPregled->show();
}
void FrmDonatMenu::on_btnMnuPrigovorOdobrenje_clicked()
{
    // Show Donat form for odobrenje prigovora
    Kontakt::FrmPrigovorOdobrenje *frmPrigovorodobrenje = new Kontakt::FrmPrigovorOdobrenje(this);
    frmPrigovorodobrenje->exec();
    delete frmPrigovorodobrenje;
//    frmPrigovorodobrenje->show();
}
void FrmDonatMenu::on_btnMnuPrigovorPismo_clicked()
{
    // Show Donat form for pregled prisma potvrde za prigovore
    Kontakt::FrmPrigovorPismoPotvrde *frmPrigovorPismoPotvrde = new Kontakt::FrmPrigovorPismoPotvrde(this);
    frmPrigovorPismoPotvrde->exec();
    delete frmPrigovorPismoPotvrde;
//    frmPrigovorPismoPotvrde->show();
}
void FrmDonatMenu::on_btnMnuSuspenzija_clicked()
{
    // Show Donat form for suspenziju ili resuspenziju usluga
    Sporazumi::FrmSuspenzija *frmSuspenzija = new Sporazumi::FrmSuspenzija(this);
    frmSuspenzija->exec();
    delete frmSuspenzija;
//    frmSuspenzija->show();
}
void FrmDonatMenu::on_btnMnuZlonamjerniUnosMob_clicked()
{
    // Show Donat form for kreiranje mobilnih zlonamjernih poziva
    Kontakt::FrmZlonamjerniMobAdd *frmZlonamjerniAdd = new Kontakt::FrmZlonamjerniMobAdd(this);
    frmZlonamjerniAdd->exec();
    delete frmZlonamjerniAdd;
//    frmZlonamjerniAdd->show();
}
void FrmDonatMenu::on_btnMnuZlonamjerniPregled_clicked()
{
    // Show Donat form for pregled kreiranih zlonamjernih prigovora
    Kontakt::FrmZlonamjerniPregled *frmZlonamjerniPregled = new Kontakt::FrmZlonamjerniPregled(this);
    frmZlonamjerniPregled->exec();
    delete frmZlonamjerniPregled;
//    frmZlonamjerniPregled->show();
}

}

