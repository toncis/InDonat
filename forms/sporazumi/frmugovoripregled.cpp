/************************************* Module Header **************************************\
* Module Name:  frmugovoripregled.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT pregled ugovora form
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

#include "frmugovoripregled.h"
#include "ui_frmugovoripregled.h"

#include "frmstavkesporazuma.h"
#include "frmpregledprocesa.h"
#include "frmwwmspregled.h"
#include "frmdonatpregled.h"
#include "frmpregledsporazuma.h"
#include "frmpregledimovine.h"
#include "forms/kontakt/frmkanalprodaje.h"

#include "itos.h"

namespace Sporazumi {

// [ Form Constructors ]
FrmUgovoriPregled::FrmUgovoriPregled(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmUgovoriPregled)
{
    ui->setupUi(this);

    initFormView();
}
FrmUgovoriPregled::FrmUgovoriPregled(unsigned int iKupacId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmUgovoriPregled)
{
    ui->setupUi(this);

    m_iKupacId = iKupacId;

    initFormView();
}

FrmUgovoriPregled::~FrmUgovoriPregled()
{
    delete ui;
}

// [ Private member Functions ]
void FrmUgovoriPregled::initFormView()
{
    ui->lstvZahtjevi->setColumnWidth(0, 20);
    ui->lstvZahtjevi->setColumnWidth(1, 90);
    ui->lstvZahtjevi->setColumnWidth(2, 100);
    ui->lstvZahtjevi->setColumnWidth(3, 400);
    ui->lstvZahtjevi->setColumnWidth(4, 70);
    ui->lstvZahtjevi->setColumnWidth(5, 0);
    ui->lstvZahtjevi->setColumnWidth(6, 5);
    ui->lstvZahtjevi->setColumnWidth(7, 0);
    ui->lstvZahtjevi->setColumnWidth(8, 0);
    ui->lstvZahtjevi->setColumnWidth(9, 0);

    m_iStrankaId = 0;
    m_iUlogaStrankeId = 0;
    m_iTipUlogaStrankeId = 0;
    m_iTipDokumenta = 3;

    m_iSporazumId = 0;

    m_TipKupcaSearchMode = SearchModeKljucni;
    m_PeriodSearchMode = SearchModeTipNone;
    m_StatusSearchMode = SearchModeSvi;

    m_iconCickled.addFile(QString::fromUtf8(":/InDonat/Forms/images/OK.gif"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);

    popuniSveKlase();
    popuniKanalProdaje();
    popuniZahtjeve();
}

void FrmUgovoriPregled::popuniSveKlase()
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
            ui->cboKlase->addItem(
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

void FrmUgovoriPregled::popuniKanalProdaje()
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

void FrmUgovoriPregled::popuniZahtjeve()
{
    ui->lstvZahtjevi->clearContents();
    ui->lstvZahtjevi->setRowCount(0);
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
    strSqlStatement.append(cttl::itos(m_iKupacId));
    strSqlStatement.append(" AND VSPORAZUMA_ID!=0 AND TSPORAZUMA_ID IN (");
    strSqlStatement.append(strTipSporazumaId);
    strSqlStatement.append(") ");
    if(m_StatusSearchMode > 0)
    {
        strSqlStatement.append(" AND STATUS_ID = ");
        strSqlStatement.append(cttl::itos(m_StatusSearchMode));
    }
    if(ui->cboKlase->currentIndex() != 0)
    {
        strSqlStatement.append(" AND KLASA ='");
        strSqlStatement.append(ui->cboKlase->currentText().toStdString());
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
            int row = ui->lstvZahtjevi->rowCount();
            ui->lstvZahtjevi->insertRow(row);
            ui->lstvZahtjevi->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
            ui->lstvZahtjevi->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(1))));
            ui->lstvZahtjevi->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            ui->lstvZahtjevi->setItem(row, 3, new QTableWidgetItem(
                                       QString::fromStdString(rs->getString(3))
                                       + tr(" , ")
                                       + QString::fromStdString(rs->getString(4))));
            ui->lstvZahtjevi->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(8))));
            ui->lstvZahtjevi->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getInt(5))));
            ui->lstvZahtjevi->setItem(row, 6, new QTableWidgetItem(QString::number(rs->getUInt(6))));
            ui->lstvZahtjevi->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(rs->getString(7))));
            ui->lstvZahtjevi->setItem(row, 8, new QTableWidgetItem(QString::number(rs->getInt(8))));
            ui->lstvZahtjevi->setItem(row, 9, new QTableWidgetItem(QString::number(rs->getUInt(9))));
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
void FrmUgovoriPregled::on_btnPrivatniKupci_clicked()
{
    m_TipKupcaSearchMode = SearchModePrivatni;

    ui->btnPrivatniKupci->setIcon(m_iconCickled);
    ui->btnKlucniKupci->setIcon(QIcon());
    ui->btnPoslovniKupci->setIcon(QIcon());
}

void FrmUgovoriPregled::on_btnKlucniKupci_clicked()
{
    m_TipKupcaSearchMode = SearchModeKljucni;

    ui->btnPrivatniKupci->setIcon(QIcon());
    ui->btnKlucniKupci->setIcon(m_iconCickled);
    ui->btnPoslovniKupci->setIcon(QIcon());
}

void FrmUgovoriPregled::on_btnPoslovniKupci_clicked()
{
    m_TipKupcaSearchMode = SearchModePoslovni;

    ui->btnPrivatniKupci->setIcon(QIcon());
    ui->btnKlucniKupci->setIcon(QIcon());
    ui->btnPoslovniKupci->setIcon(m_iconCickled);
}

void FrmUgovoriPregled::on_btnDanas_clicked()
{
    m_PeriodSearchMode = SearchModeDanas;
}

void FrmUgovoriPregled::on_btnOvajTjedan_clicked()
{
    m_PeriodSearchMode = SearchModeOvajTjedan;
}

void FrmUgovoriPregled::on_btnOvajMjesec_clicked()
{
    m_PeriodSearchMode = SearchModeOvajMjesec;
}

void FrmUgovoriPregled::on_btnStatusSvi_clicked()
{
    m_StatusSearchMode = SearchModeSvi;
    popuniZahtjeve();
}

void FrmUgovoriPregled::on_btnStatusUtijeku_clicked()
{
    m_StatusSearchMode = SearchModeUTijeku;
    popuniZahtjeve();
}

void FrmUgovoriPregled::on_btnStatusRezerviran_clicked()
{
    m_StatusSearchMode = SearchModeRezerviran;
    popuniZahtjeve();
}

void FrmUgovoriPregled::on_btnStatusStorniran_clicked()
{
    m_StatusSearchMode = SearchModeStorniran;
    popuniZahtjeve();
}

void FrmUgovoriPregled::on_btnStorno_clicked()
{

}

void FrmUgovoriPregled::on_btnStornoDonat_clicked()
{

}

void FrmUgovoriPregled::on_btnNastavakRealizacije_clicked()
{

}

void FrmUgovoriPregled::on_btnPretvoriU1Kunu_clicked()
{

}

void FrmUgovoriPregled::on_btnKanalProdaje_clicked()
{
    ui->btnKanalProdaje->setIcon(m_iconCickled);
    ui->btnMojiDokumenti->setIcon(QIcon());


    // Show Donat user kanal prodaje
    Kontakt::FrmKanalProdaje *frmKanalProdaje = new Kontakt::FrmKanalProdaje(1, this);
    frmKanalProdaje->exec();
    delete frmKanalProdaje;
}

void FrmUgovoriPregled::on_btnMojiDokumenti_clicked()
{
    ui->btnKanalProdaje->setIcon(QIcon());
    ui->btnMojiDokumenti->setIcon(m_iconCickled);
}

void FrmUgovoriPregled::on_btnOznaciSve_clicked()
{
    if(ui->lstvZahtjevi->rowCount() == 0)
        return;

    ui->lstvZahtjevi->selectAll();

//    ui->btnOznaciSve->setIcon(m_iconCickled);
//    ui->btnOznaciNista->setIcon(QIcon());
}

void FrmUgovoriPregled::on_btnOznaciNista_clicked()
{
    if(ui->lstvZahtjevi->rowCount() == 0)
        return;

    ui->lstvZahtjevi->clearSelection();

//    ui->btnOznaciSve->setIcon(QIcon());
//    ui->btnOznaciNista->setIcon(m_iconCickled);
}

void FrmUgovoriPregled::on_btnPregledSporazuma_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat user password change
    FrmStavkeSporazuma *frmStavkeSporazuma = new FrmStavkeSporazuma(m_iSporazumId, this);
    frmStavkeSporazuma->exec();
    delete frmStavkeSporazuma;
}

void FrmUgovoriPregled::on_btnPregledStanjaDonat_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat - status
    FrmDonatPregled *frmDonatTicketPregled = new FrmDonatPregled(m_iSporazumId, this);
    frmDonatTicketPregled->exec();
    delete frmDonatTicketPregled;
}

void FrmUgovoriPregled::on_btnPregledStanjaWwms_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat - WWMS Ticket status
    FrmWwmsPregled *frmWwmsTicketPregled = new FrmWwmsPregled(m_iSporazumId, m_iTipDokumenta, this);
    frmWwmsTicketPregled->exec();
    delete frmWwmsTicketPregled;
}

void FrmUgovoriPregled::on_btnPregledDetaljno_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat detaljan pregled sporazuma
    FrmPregledSporazuma *frmDetaljanPregledSporazuma = new FrmPregledSporazuma(m_iSporazumId, this);
    frmDetaljanPregledSporazuma->exec();
    delete frmDetaljanPregledSporazuma;
}

void FrmUgovoriPregled::on_btnPregledProcesi_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat order management processes
    FrmPregledProcesa *frmPregledProcesa = new FrmPregledProcesa(m_iSporazumId, this);
    frmPregledProcesa->exec();
    delete frmPregledProcesa;
}

void FrmUgovoriPregled::on_btnPregledDisKarta_clicked()
{

}

void FrmUgovoriPregled::on_btn_Napomena_clicked()
{

}

void FrmUgovoriPregled::on_btnDatoteka_clicked()
{

}

void FrmUgovoriPregled::on_btnSpis_clicked()
{

}

void FrmUgovoriPregled::on_btnJop_clicked()
{

}

void FrmUgovoriPregled::on_btnDodijeliJop_clicked()
{

}

void FrmUgovoriPregled::on_btnOpisZaduzenja_clicked()
{

}

void FrmUgovoriPregled::on_btnUlaznePoruke_clicked()
{

}

void FrmUgovoriPregled::on_btnPromjenaKPro_clicked()
{

}

void FrmUgovoriPregled::on_btnDatumZahtjeva_clicked()
{

}

void FrmUgovoriPregled::on_btnIsipisDokumenta_clicked()
{

}


void FrmUgovoriPregled::on_lstvZahtjevi_itemPressed(QTableWidgetItem *itemZahtjev)
{
    m_iSporazumId = ui->lstvZahtjevi->item(itemZahtjev->row(), 6)->text().toUInt();
}

void FrmUgovoriPregled::on_cboKlase_currentIndexChanged(const QString &UNUSED(arg1))
{
    popuniZahtjeve();
}

}




