//
//  frmzlonamernipregled.cpp
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


#include "frmzlonamjernipregled.h"
#include "ui_frmzlonamjernipregled.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {
FrmZlonamjerniPregled::FrmZlonamjerniPregled(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmZlonamjerniPregled)
{
    ui->setupUi(this);

    initForm();
}

FrmZlonamjerniPregled::~FrmZlonamjerniPregled()
{
    delete ui;
}

// [Private Member Functions]
void FrmZlonamjerniPregled::initForm()
{
    m_iZlonamjerniStatusId = 0;

    ui->dateEditOd->setDateTime(QDateTime::currentDateTime().addMonths(-1));
    ui->dateEditDo->setDateTime(QDateTime::currentDateTime());

    ui->grdPrigovori->setColumnWidth(0, 34);  // RB
    ui->grdPrigovori->setColumnWidth(1, 120);  // DATUM_DOK
    ui->grdPrigovori->setColumnWidth(2, 110);  // BROJ
    ui->grdPrigovori->setColumnWidth(3, 450); // PRETPLATNIK
    ui->grdPrigovori->setColumnWidth(4, 90);  // TELEFON
    ui->grdPrigovori->setColumnWidth(5, 70);  // JOP
    ui->grdPrigovori->setColumnWidth(6, 30);   // ID
    ui->grdPrigovori->setColumnWidth(7, 30);   // ST_ID
//    ui->grdPrigovori->hideColumn(0);
//    ui->grdPrigovori->hideColumn(1);
    ui->grdPrigovori->verticalHeader()->hide();
//    ui->grdPrigovori->horizontalHeader()->hide();
    ui->grdPrigovori->setAlternatingRowColors(true);
//    ui->grdPrigovori->setShowGrid(true);
    ui->grdPrigovori->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->grdPrigovori->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void FrmZlonamjerniPregled::clearFormData()
{
    ui->lblKorinsikNaziv->clear();
    ui->lblKorisnikAdresa->clear();
    ui->lblJMBG->clear();
    ui->lblSpis->clear();
    ui->lblJop->clear();
    ui->lblPeriod->clear();
    ui->lblTelefon->clear();
    ui->lblOstalo->clear();
    ui->lblDokumenti->clear();
    ui->txtNapomena->clear();
    ui->lblKontaktOsoba->clear();
    ui->lblKontaktTelefon->clear();
    ui->lblKontaktMobitel->clear();
    ui->lblKontaktFax->clear();
    ui->lblKontaktEmail->clear();
    ui->lblOtvoren->clear();
    ui->lblOtvorenDatum->clear();
    ui->lblAnaliza->clear();
    ui->lblAnalizaDatum->clear();
    ui->lblPUprava->clear();
    ui->lblPUpravaDatum->clear();
    ui->lblObavijest->clear();
    ui->lblObavijestDatum->clear();
    ui->lblOdustao->clear();
    ui->lblOdustaoDatum->clear();
    ui->chkPrijetnjaSmrcu->setChecked(false);
    ui->chkPrijetnja2->setChecked(false);
    ui->chkSpolnoUznemiravanje->setChecked(false);
    ui->chkVrijedjanje->setChecked(false);
    ui->chkNejavljanje->setChecked(false);
}

void FrmZlonamjerniPregled::popuniZlonamjernePozive()
{
    clearFormData();

    ui->grdPrigovori->clearContents();
    ui->grdPrigovori->setRowCount(0);

    string strSqlStatement;

    strSqlStatement.append("SELECT ID, ST_ID, ST_STATUS, KUPAC_NAZIV, DOK_BROJ, NVL(JOP, '-'), TEL_BROJ, NVL(TO_CHAR(DATUM, 'DD.MM.YYYY HH24:MI'), '0') ");
    strSqlStatement.append("FROM KONTAKT_ST31_ZLP WHERE ID > 0 AND DATUM BETWEEN TO_DATE('");
    strSqlStatement.append(ui->dateEditOd->text().toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') AND TO_DATE('");
    strSqlStatement.append(ui->dateEditDo->text().toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') + 1 ");
    if (m_iZlonamjerniStatusId > 0)
    {
        strSqlStatement.append(" AND ST_STATUS = ");
        strSqlStatement.append(cttl::itos(m_iZlonamjerniStatusId));
    }
    strSqlStatement.append(" ORDER BY ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = ui->grdPrigovori->rowCount();
            ui->grdPrigovori->insertRow(row);
            ui->grdPrigovori->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
            ui->grdPrigovori->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(8))));
            ui->grdPrigovori->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            ui->grdPrigovori->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(rs->getString(4))));
            ui->grdPrigovori->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(7))));
            ui->grdPrigovori->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(rs->getString(6))));
            ui->grdPrigovori->setItem(row, 6, new QTableWidgetItem(QString::number(rs->getUInt(1))));
            ui->grdPrigovori->setItem(row, 7, new QTableWidgetItem(QString::number(rs->getUInt(2))));
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

void FrmZlonamjerniPregled::popuniZlonamjerniPoziv(unsigned int iZlonamjerniPozivId)
{
    clearFormData();

    if (iZlonamjerniPozivId == 0)
    {
        return;
    }

    string strSqlStatement;

    strSqlStatement.append("SELECT KUPAC_NAZIV, KUP_ADR1, KUP_ADR2, KUP_MB, SPIS, JOP, KUP_OIB, NVL(TO_CHAR(POZ_DATUM_OD, 'DD.MM.YYYY HH24:MI'), '0'), ");
    strSqlStatement.append("NVL(TO_CHAR(POZ_DATUM_DO, 'DD.MM.YYYY HH24:MI'), '0'), TEL_BROJ, KON_OSOBA, KON_TEL1, KON_MOB1, KON_FAX1, ");
    strSqlStatement.append("KON_EMAIL, NVL(TO_CHAR(DATUM, 'DD.MM.YYYY HH24:MI'), '0'), KORISNIK_NAZ, AN_DATUM, AN_KOR_NAZ, PU_DATUM, ");
    strSqlStatement.append("PU_KOR_NAZ, OB_DATUM, OB_KOR_NAZ, OD_DATUM, OD_KOR_NAZ, POZ_G1, POZ_G2, POZ_G3, POZ_G4, POZ_G5, POZ_G6, ");
    strSqlStatement.append("NVL(MJESTO_NAZ, 'xxxxx'), DOKUMENTI, NAPOMENA ");
    strSqlStatement.append("FROM KONTAKT_ST31_ZLP WHERE ID = ");
    strSqlStatement.append(cttl::itos(iZlonamjerniPozivId));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->lblKorinsikNaziv->setText(QString::fromStdString(rs->getString(1)));
            ui->lblKorisnikAdresa->setText(QString::fromStdString(rs->getString(2)) + tr(" ") + QString::fromStdString(rs->getString(3)));
            ui->lblJMBG->setText(QString::fromStdString(rs->getString(4)));
            ui->lblSpis->setText(QString::fromStdString(rs->getString(5)));
            ui->lblJop->setText(QString::fromStdString(rs->getString(6)));
            ui->lblPeriod->setText(QString::fromStdString(rs->getString(8)) + tr(" - ") + QString::fromStdString(rs->getString(9)));
            ui->lblTelefon->setText(QString::fromStdString(rs->getString(10)));
            ui->lblKontaktOsoba->setText(QString::fromStdString(rs->getString(11)));
            ui->lblKontaktTelefon->setText(QString::fromStdString(rs->getString(12)));
            ui->lblKontaktMobitel->setText(QString::fromStdString(rs->getString(13)));
            ui->lblKontaktFax->setText(QString::fromStdString(rs->getString(14)));
            ui->lblKontaktEmail->setText(QString::fromStdString(rs->getString(15)));
            ui->lblOtvoren->setText(QString::fromStdString(rs->getString(17)));
            ui->lblOtvorenDatum->setText(QString::fromStdString(rs->getString(16)));
            ui->lblAnaliza->setText(QString::fromStdString(rs->getString(19)));
            ui->lblAnalizaDatum->setText(QString::fromStdString(rs->getString(18)));
            ui->lblPUprava->setText(QString::fromStdString(rs->getString(21)));
            ui->lblPUpravaDatum->setText(QString::fromStdString(rs->getString(20)));
            ui->lblObavijest->setText(QString::fromStdString(rs->getString(23)));
            ui->lblObavijestDatum->setText(QString::fromStdString(rs->getString(22)));
            ui->lblOdustao->setText(QString::fromStdString(rs->getString(25)));
            ui->lblOdustaoDatum->setText(QString::fromStdString(rs->getString(24)));
            ui->lblOstalo->setText(QString::fromStdString(rs->getString(31)));
            ui->lblDokumenti->setText(QString::fromStdString(rs->getString(33)));
            ui->txtNapomena->setText(QString::fromStdString(rs->getString(34)));
            if(rs->getInt(26) == 1)
            {
                ui->chkPrijetnjaSmrcu->setChecked(true);
            }
            if(rs->getInt(27) == 1)
            {
                ui->chkPrijetnja2->setChecked(true);
            }
            if(rs->getInt(28) == 1)
            {
                ui->chkSpolnoUznemiravanje->setChecked(true);
            }
            if(rs->getInt(29) == 1)
            {
                ui->chkVrijedjanje->setChecked(true);
            }
            if(rs->getInt(29) == 1)
            {
                ui->chkNejavljanje->setChecked(true);
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

// [Event Handlers]
void FrmZlonamjerniPregled::on_btnSvi_clicked()
{
    m_iZlonamjerniStatusId = 0;
    popuniZlonamjernePozive();
}

void FrmZlonamjerniPregled::on_btnOtvoreni_clicked()
{
    m_iZlonamjerniStatusId = 1;
    popuniZlonamjernePozive();
}

void FrmZlonamjerniPregled::on_btnAnaliza_clicked()
{
    m_iZlonamjerniStatusId = 2;
    popuniZlonamjernePozive();
}

void FrmZlonamjerniPregled::on_btnPoslanoPoliciji_clicked()
{
    m_iZlonamjerniStatusId = 3;
    popuniZlonamjernePozive();
}

void FrmZlonamjerniPregled::on_btnObavijest_2_clicked()
{
    m_iZlonamjerniStatusId = 4;
    popuniZlonamjernePozive();
}

void FrmZlonamjerniPregled::on_btnOdustao_clicked()
{
    m_iZlonamjerniStatusId = 5;
    popuniZlonamjernePozive();
}

void FrmZlonamjerniPregled::on_btnPodnesak_clicked()
{

}

void FrmZlonamjerniPregled::on_btnObavijest_clicked()
{

}

void FrmZlonamjerniPregled::on_btnExcel_clicked()
{

}

void FrmZlonamjerniPregled::on_btnOtvorenDatumOK_clicked()
{

}

void FrmZlonamjerniPregled::on_btnAnalizaDatumOK_clicked()
{

}

void FrmZlonamjerniPregled::on_btnPUpravaDatumOK_clicked()
{

}

void FrmZlonamjerniPregled::on_btnObavijestDatumOK_clicked()
{

}

void FrmZlonamjerniPregled::on_btnOdustaoDatumOK_clicked()
{

}

void FrmZlonamjerniPregled::on_btnDokumentiOK_clicked()
{

}

void FrmZlonamjerniPregled::on_btnNapomenaOK_clicked()
{

}

void FrmZlonamjerniPregled::on_grdPrigovori_itemPressed(QTableWidgetItem *item)
{
    m_iZlonamjerniPozivId = ui->grdPrigovori->item(item->row(), 6)->text().toUInt();
    popuniZlonamjerniPoziv(m_iZlonamjerniPozivId);
}


}



