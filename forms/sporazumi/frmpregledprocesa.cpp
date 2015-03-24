/************************************* Module Header **************************************\
* Module Name:  frmpregledprocesa.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT pregled procesa za sporazum form
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
