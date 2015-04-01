//
//  frmpregledprocesa.cpp
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


#include "frmpregledprocesa.h"

#include "itos.h"

namespace Sporazumi {

FrmPregledProcesa::FrmPregledProcesa(unsigned int iSporazumId, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    m_grdPoslovniProcesi = new QTableWidget();
    m_grdPoslovniProcesi->setContentsMargins(4, 4, 0, 0);
    m_grdPoslovniProcesi->setFrameShape(QFrame::StyledPanel);
    m_grdPoslovniProcesi->setMinimumWidth(964);
    m_grdPoslovniProcesi->setMinimumHeight(400);

    // Create headers
    QStringList labels;
    labels << "RB" << "Opis" << "Datum" << "Operater" << "Akcija"
           << "Storno razlog" << "PoslovniProcesId" << "AssetId";
    m_grdPoslovniProcesi->setColumnCount(8);
    m_grdPoslovniProcesi->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_grdPoslovniProcesi->setHorizontalHeaderLabels(labels);
    m_grdPoslovniProcesi->horizontalHeader()->setStretchLastSection(false);
    m_grdPoslovniProcesi->setColumnWidth(0, 30);
    m_grdPoslovniProcesi->setColumnWidth(1, 278);
    m_grdPoslovniProcesi->setColumnWidth(2, 144);
    m_grdPoslovniProcesi->setColumnWidth(3, 155);
    m_grdPoslovniProcesi->setColumnWidth(4, 145);
    m_grdPoslovniProcesi->setColumnWidth(5, 206);
    m_grdPoslovniProcesi->setColumnWidth(6, 5);
    m_grdPoslovniProcesi->setColumnWidth(7, 5);
//    m_grdPoslovniProcesi->hideColumn(0);
    m_grdPoslovniProcesi->verticalHeader()->hide();
//    m_grdPoslovniProcesi->horizontalHeader()->hide();
    m_grdPoslovniProcesi->setAlternatingRowColors(TRUE);
    m_grdPoslovniProcesi->setShowGrid(true);
    m_grdPoslovniProcesi->setSelectionMode(QAbstractItemView::SingleSelection);
    m_grdPoslovniProcesi->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainLayout->addWidget(m_grdPoslovniProcesi);
    setLayout(mainLayout);

    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT - Procesi unutar sporazuma"));

    m_iSporazumId = iSporazumId;
    const bool bSortingEnabled = m_grdPoslovniProcesi->isSortingEnabled();
    m_grdPoslovniProcesi->setSortingEnabled(false);
    popuniPoslovneProcese();
    m_grdPoslovniProcesi->setSortingEnabled(bSortingEnabled);
}

void FrmPregledProcesa::popuniPoslovneProcese()
{
	string strSqlStatement;
	strSqlStatement.append("SELECT ASSET_ID, NAZIV, DATUM, OPERATER, AKCIJA, STORNO_RAZLOG, ");
	strSqlStatement.append("DNEPROC_ID ");
	strSqlStatement.append("FROM V_PREGLED_PROCESA ");
	strSqlStatement.append("WHERE SPORAZUM_ID = ");
	strSqlStatement.append(cttl::itos(m_iSporazumId));
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_grdPoslovniProcesi->rowCount();
            m_grdPoslovniProcesi->insertRow(row);
            m_grdPoslovniProcesi->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));
            m_grdPoslovniProcesi->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_grdPoslovniProcesi->setItem(
                        row,
                        2,
                        new QTableWidgetItem(
                            QString::fromStdString(
                                rs->getDate(3).toText("DD.MM.YYYY HH24:MI:SS")))
                        );
            m_grdPoslovniProcesi->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(rs->getString(4))));
            m_grdPoslovniProcesi->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_grdPoslovniProcesi->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(rs->getString(6))));
            m_grdPoslovniProcesi->setItem(row, 6, new QTableWidgetItem(QString::number(rs->getUInt(7))));
            m_grdPoslovniProcesi->setItem(row, 7, new QTableWidgetItem(QString::number(rs->getUInt(1))));
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

FrmPregledProcesa::~FrmPregledProcesa()
{
    m_grdPoslovniProcesi->clear();
}

}   // namespace sporazumi
