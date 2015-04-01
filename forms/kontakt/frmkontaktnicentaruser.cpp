//
//  frmkontaktnicentaruser.cpp
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

#include "frmkontaktnicentaruser.h"
#include "ui_frmkontaktnicentaruser.h"
#include "itos.h"

namespace Kontakt {

// [Class Constructors]
FrmKontaktniCentarUser::FrmKontaktniCentarUser(QWidget *parent, int iTipRole) :
    QDialog(parent),
    ui(new Ui::FrmKontaktniCentarUser)
{
    ui->setupUi(this);

    ui->grdKorisnickeGrupe->setColumnWidth(0, 3);
    ui->grdKorisnickeGrupe->setColumnWidth(1, 3);
    ui->grdKorisnickeGrupe->setColumnWidth(2, 200);
//    ui->grdKorisnickeGrupe->hideColumn(0);
//    ui->grdKorisnickeGrupe->hideColumn(1);
//    ui->grdKorisnickeGrupe->verticalHeader()->hide();
//    ui->grdKorisnickeGrupe->horizontalHeader()->hide();
    ui->grdKorisnickeGrupe->setAlternatingRowColors(true);
//    ui->grdKorisnickeGrupe->setShowGrid(true);
    ui->grdKorisnickeGrupe->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->grdKorisnickeGrupe->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_iTipRole = iTipRole;

    popuniGrupe();
}

FrmKontaktniCentarUser::~FrmKontaktniCentarUser()
{
    delete ui;
}

// [Private Member Functions]
void FrmKontaktniCentarUser::popuniGrupe()
{

    ui->lblKorisnikNaziv->setText(QString::fromStdString(g_KORISNIK_NAZ));

    string strSqlStatement;

    strSqlStatement.append("SELECT ROLA_TIP, GRUPA_ID, GRUPA_NAZ FROM KONTAKT_GRUPA_KOR WHERE KOR_TIP = 1 ");
    strSqlStatement.append(" AND KOR_ID = '");
    strSqlStatement.append(g_DonatUser);
    strSqlStatement.append("' ");
    if (m_iTipRole == 0)
    {
        strSqlStatement.append(" AND ROLA_TIP IN (1,2) ");
    }
    else
    {
        strSqlStatement.append(" AND ROLA_TIP = 3 ");
    }
    strSqlStatement.append(" ORDER BY GRUPA_NAZ ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = ui->grdKorisnickeGrupe->rowCount();
            ui->grdKorisnickeGrupe->insertRow(row);
            ui->grdKorisnickeGrupe->setItem(row, 0, new QTableWidgetItem(QString::number(rs->getInt(1))));
            ui->grdKorisnickeGrupe->setItem(row, 1, new QTableWidgetItem(QString::number(rs->getInt(2))));
            ui->grdKorisnickeGrupe->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
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
void FrmKontaktniCentarUser::on_btnPotvrda_clicked()
{

    if(m_iGrupaId == 0)
    {
        return;
    }

    g_GRP_NO = m_iGrupaId;
    g_GRP_TIP = m_iRolaTip;
    g_GRP_NAZ = m_strGrupaNaziv;

    this->close();
}

void FrmKontaktniCentarUser::on_grdKorisnickeGrupe_itemClicked(QTableWidgetItem *item)
{
    m_strGrupaNaziv = ui->grdKorisnickeGrupe->item(item->row(), 2)->text().toStdString();
    m_iGrupaId = ui->grdKorisnickeGrupe->item(item->row(), 1)->text().toInt();
    m_iRolaTip = ui->grdKorisnickeGrupe->item(item->row(), 0)->text().toInt();
    ui->lblKorisnickaGrupa->setText(ui->grdKorisnickeGrupe->item(item->row(), 2)->text());
}

}


