/************************************* Module Header **************************************\
* Module Name:  frmstavkesporazuma.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT stavke sporazuma form
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

#include "frmstavkesporazuma.h"

#include "itos.h"
#include "ocinumber.h"

namespace Sporazumi {

FrmStavkeSporazuma::FrmStavkeSporazuma(unsigned int iSporazumId, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    m_grdStavkeSporazuma = new QTableWidget();
    m_grdStavkeSporazuma->setContentsMargins(4, 4, 0, 0);
    m_grdStavkeSporazuma->setFrameShape(QFrame::StyledPanel);
    m_grdStavkeSporazuma->setMinimumWidth(685);
    // Create headers
    QStringList labels;
    labels << "RB" << "PRODUKT" << "KOL" << "CIJ_FIX" << "CIJ_MJ"
           << "StavkaSporazumaId";
    m_grdStavkeSporazuma->setColumnCount(6);
    m_grdStavkeSporazuma->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_grdStavkeSporazuma->setHorizontalHeaderLabels(labels);
    m_grdStavkeSporazuma->horizontalHeader()->setStretchLastSection(false);
    m_grdStavkeSporazuma->setColumnWidth(0, 30);
    m_grdStavkeSporazuma->setColumnWidth(1, 400);
    m_grdStavkeSporazuma->setColumnWidth(2, 35);
    m_grdStavkeSporazuma->setColumnWidth(3, 100);
    m_grdStavkeSporazuma->setColumnWidth(4, 100);
    m_grdStavkeSporazuma->setColumnWidth(5, 5);
//    m_grdStavkeSporazuma->hideColumn(0);
    m_grdStavkeSporazuma->verticalHeader()->hide();
//    m_grdStavkeSporazuma->horizontalHeader()->hide();
    m_grdStavkeSporazuma->setAlternatingRowColors(TRUE);
    m_grdStavkeSporazuma->setShowGrid(true);
    m_grdStavkeSporazuma->setSelectionMode(QAbstractItemView::SingleSelection);
    m_grdStavkeSporazuma->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainLayout->addWidget(m_grdStavkeSporazuma);
    setLayout(mainLayout);

    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT - Stavke sporazuma"));

    m_iSporazumId = iSporazumId;
    const bool bSortingEnabled = m_grdStavkeSporazuma->isSortingEnabled();
    m_grdStavkeSporazuma->setSortingEnabled(false);
    popuniStavkeSporazuma();
    m_grdStavkeSporazuma->setSortingEnabled(bSortingEnabled);
}

void FrmStavkeSporazuma::popuniStavkeSporazuma()
{
	string strSqlStatement;
	strSqlStatement.append("SELECT DECODE(P.PRODUKT_ID, 11261, P.NAZIV ||' - '|| VRATI_NAZIV_PRODUKTA(OSN_IMOVINA_ID), P.NAZIV) NAZIV_PRODUKTA, ");
	strSqlStatement.append(" S.KOLICINA, S.IZNOS1, S.IZNOS2, S.SRZSTAVKA_ID ");
	strSqlStatement.append("FROM STAVKE_SPORAZUMA S, PRODUKTI P ");
	strSqlStatement.append("WHERE S.PRODUKT_ID = P.PRODUKT_ID AND  ");
	strSqlStatement.append(cttl::itos(m_iSporazumId));
	strSqlStatement.append(" IN (S.SRZ_UGOVOR_ID, S.SPORAZUM_ID) ");
	strSqlStatement.append("ORDER BY RBR ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int iKolicina = rs->getInt(2);
            if(iKolicina == 0)
            {
                continue;
            }
            int row = m_grdStavkeSporazuma->rowCount();
            m_grdStavkeSporazuma->insertRow(row);
            m_grdStavkeSporazuma->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));
            m_grdStavkeSporazuma->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(1))));
            QTableWidgetItem *itemKolicina = new QTableWidgetItem(QString::number(iKolicina));
            itemKolicina->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);
            m_grdStavkeSporazuma->setItem(row, 2, itemKolicina);
            QString strIznos1;
            strIznos1.setNum(rs->getDouble(3), 'f', 2);
            strIznos1.replace(tr("."), tr(","));
            QTableWidgetItem *itemIznos1 = new QTableWidgetItem(strIznos1);
            itemIznos1->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
            m_grdStavkeSporazuma->setItem(row, 3, itemIznos1);
            QString strIznos2;
            strIznos2.setNum(rs->getDouble(4), 'f', 2);
            strIznos2.replace(tr("."), tr(","));
            QTableWidgetItem *itemIznos2 = new QTableWidgetItem(strIznos2);
            itemIznos2->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
            m_grdStavkeSporazuma->setItem(row, 4, itemIznos2);
            m_grdStavkeSporazuma->setItem(row, 5, new QTableWidgetItem(QString::number(rs->getUInt(5))));
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

FrmStavkeSporazuma::~FrmStavkeSporazuma()
{
    m_grdStavkeSporazuma->clear();
}

} // Namespace sporazumi
