//
//  frmzahtjevipregled.cpp
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


#include "frmzahtjevipregled.h"
#include "ui_frmzahtjevipregled.h"

#include "frmstavkesporazuma.h"
#include "frmpregledprocesa.h"
#include "frmwwmspregled.h"
#include "frmdonatpregled.h"
#include "frmpregledsporazuma.h"
#include "frmpregledimovine.h"
#include "forms/kontakt/frmkanalprodaje.h"

#include "itos.h"

namespace Sporazumi {

// [ Class Constructor ]
FrmZahtjeviPregled::FrmZahtjeviPregled(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmZahtjeviPregled)
{
    ui->setupUi(this);

    m_iKupacId = 0;
    initFormView();

}

FrmZahtjeviPregled::FrmZahtjeviPregled(unsigned int iKupacId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmZahtjeviPregled)
{
    ui->setupUi(this);

    m_iKupacId = iKupacId;
    initFormView();
}

FrmZahtjeviPregled::~FrmZahtjeviPregled()
{
    delete ui;
}

// [ Private member Functions ]
void FrmZahtjeviPregled::initFormView()
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

    ui->lstvZahtjevi->setColumnHidden(0, true);

    m_iStrankaId = 0;
    m_iUlogaStrankeId = 0;
    m_iTipUlogaStrankeId = 0;
    m_iTipDokumenta = 1;

    m_TipKupcaSearchMode = SearchModeKljucni;
    m_PeriodSearchMode = SearchModeTipNone;
    m_StatusSearchMode = SearchModeSvi;

    m_iconCickled.addFile(QString::fromUtf8(":/InDonat/Forms/images/OK.gif"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);

    m_iSporazumId = 0;

    popuniSveKlase();
    popuniKanalProdaje();
    popuniZahtjeve();
}

void FrmZahtjeviPregled::popuniSveKlase()
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

void FrmZahtjeviPregled::popuniKanalProdaje()
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

void FrmZahtjeviPregled::popuniZahtjeve()
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
            ui->lstvZahtjevi->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(rs->getString(8))));
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
void FrmZahtjeviPregled::on_btnPrivatniKupci_clicked()
{
    m_TipKupcaSearchMode = SearchModePrivatni;

    ui->btnPrivatniKupci->setIcon(m_iconCickled);
    ui->btnKlucniKupci->setIcon(QIcon());
    ui->btnPoslovniKupci->setIcon(QIcon());
}

void FrmZahtjeviPregled::on_btnKlucniKupci_clicked()
{
    m_TipKupcaSearchMode = SearchModeKljucni;

    ui->btnPrivatniKupci->setIcon(QIcon());
    ui->btnKlucniKupci->setIcon(m_iconCickled);
    ui->btnPoslovniKupci->setIcon(QIcon());
}

void FrmZahtjeviPregled::on_btnPoslovniKupci_clicked()
{
    m_TipKupcaSearchMode = SearchModePoslovni;

    ui->btnPrivatniKupci->setIcon(QIcon());
    ui->btnKlucniKupci->setIcon(QIcon());
    ui->btnPoslovniKupci->setIcon(m_iconCickled);
}

void FrmZahtjeviPregled::on_btnDanas_clicked()
{
    m_PeriodSearchMode = SearchModeDanas;
}

void FrmZahtjeviPregled::on_btnOvajTjedan_clicked()
{
    m_PeriodSearchMode = SearchModeOvajTjedan;
}

void FrmZahtjeviPregled::on_btnOvajMjesec_clicked()
{
    m_PeriodSearchMode = SearchModeOvajMjesec;
}

void FrmZahtjeviPregled::on_btnStatusSvi_clicked()
{
    m_StatusSearchMode = SearchModeSvi;
    popuniZahtjeve();
}

void FrmZahtjeviPregled::on_btnStatusUtijeku_clicked()
{
    m_StatusSearchMode = SearchModeUTijeku;
    popuniZahtjeve();
}

void FrmZahtjeviPregled::on_btnStatusRezerviran_clicked()
{
    m_StatusSearchMode = SearchModeRezerviran;
    popuniZahtjeve();
}

void FrmZahtjeviPregled::on_btnStatusStorniran_clicked()
{
    m_StatusSearchMode = SearchModeStorniran;
    popuniZahtjeve();
}

void FrmZahtjeviPregled::on_btnStorno_clicked()
{
}

void FrmZahtjeviPregled::on_btnStornoDonat_clicked()
{

}

void FrmZahtjeviPregled::on_btnNastavakRealizacije_clicked()
{

}

void FrmZahtjeviPregled::on_btnPretvoriU1Kunu_clicked()
{

}

void FrmZahtjeviPregled::on_btnKlasa_clicked()
{

}

void FrmZahtjeviPregled::on_btnKanalProdaje_clicked()
{
    ui->btnKanalProdaje->setIcon(m_iconCickled);
    ui->btnMojiDokumenti->setIcon(QIcon());


    // Show Donat user kanal prodaje
    Kontakt::FrmKanalProdaje *frmKanalProdaje = new Kontakt::FrmKanalProdaje(1, this);
    frmKanalProdaje->exec();
    delete frmKanalProdaje;

}

void FrmZahtjeviPregled::on_btnMojiDokumenti_clicked()
{
    ui->btnKanalProdaje->setIcon(QIcon());
    ui->btnMojiDokumenti->setIcon(m_iconCickled);
}

void FrmZahtjeviPregled::on_btnOznaciSve_clicked()
{
    if(ui->lstvZahtjevi->rowCount() == 0)
        return;

    ui->lstvZahtjevi->selectAll();

//    ui->btnOznaciSve->setIcon(m_iconCickled);
//    ui->btnOznaciNista->setIcon(QIcon());
}

void FrmZahtjeviPregled::on_btnOznaciNista_clicked()
{
    if(ui->lstvZahtjevi->rowCount() == 0)
        return;

    ui->lstvZahtjevi->clearSelection();

//    ui->btnOznaciSve->setIcon(QIcon());
//    ui->btnOznaciNista->setIcon(m_iconCickled);
}

void FrmZahtjeviPregled::on_btnPregledSporazuma_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat user password change
    FrmStavkeSporazuma *frmStavkeSporazuma = new FrmStavkeSporazuma(m_iSporazumId, this);
    frmStavkeSporazuma->exec();
    delete frmStavkeSporazuma;
}

void FrmZahtjeviPregled::on_btnPregledStanjaDonat_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat - status
    FrmDonatPregled *frmDonatTicketPregled = new FrmDonatPregled(m_iSporazumId, this);
    frmDonatTicketPregled->exec();
    delete frmDonatTicketPregled;
}

void FrmZahtjeviPregled::on_btnPregledStanjaWwms_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat - WWMS Ticket status
    FrmWwmsPregled *frmWwmsTicketPregled = new FrmWwmsPregled(m_iSporazumId, m_iTipDokumenta, this);
    frmWwmsTicketPregled->exec();
    delete frmWwmsTicketPregled;
}

void FrmZahtjeviPregled::on_btnPregledDetaljno_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat detaljan pregled sporazuma
    FrmPregledSporazuma *frmDetaljanPregledSporazuma = new FrmPregledSporazuma(m_iSporazumId, this);
    frmDetaljanPregledSporazuma->exec();
    delete frmDetaljanPregledSporazuma;
}

void FrmZahtjeviPregled::on_btnPregledProcesi_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat order management processes
    FrmPregledProcesa *frmPregledProcesa = new FrmPregledProcesa(m_iSporazumId, this);
    frmPregledProcesa->exec();
    delete frmPregledProcesa;
}

void FrmZahtjeviPregled::on_btnPregledDisKarta_clicked()
{

}

void FrmZahtjeviPregled::on_btn_Napomena_clicked()
{

}

void FrmZahtjeviPregled::on_btnDatoteka_clicked()
{

}

void FrmZahtjeviPregled::on_btnSpis_clicked()
{

}

void FrmZahtjeviPregled::on_btnJop_clicked()
{

}

void FrmZahtjeviPregled::on_btnDodijeliJop_clicked()
{

}

void FrmZahtjeviPregled::on_btnOpisZaduzenja_clicked()
{

}

void FrmZahtjeviPregled::on_btnUlaznePoruke_clicked()
{

}

void FrmZahtjeviPregled::on_btnPromjenaKPro_clicked()
{

}

void FrmZahtjeviPregled::on_btnDatumZahtjeva_clicked()
{

}

void FrmZahtjeviPregled::on_btnIsipisDokumenta_clicked()
{

}

void FrmZahtjeviPregled::on_lstvZahtjevi_itemPressed(QTableWidgetItem *itemZahtjev)
{
    m_iSporazumId = ui->lstvZahtjevi->item(itemZahtjev->row(), 6)->text().toUInt();
}

void FrmZahtjeviPregled::on_cboKlase_currentIndexChanged(const QString &UNUSED(arg1))
{
    popuniZahtjeve();
}

}



