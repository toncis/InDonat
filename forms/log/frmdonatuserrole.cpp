/************************************* Module Header **************************************\
* Module Name:  frmdonatuserrole.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT user roles form.
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

#include "frmdonatuserrole.h"

namespace Log {

FrmDonatUserRole::FrmDonatUserRole()
{
    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT - Moje Role"));

    m_lblUserRoleTitle = new QLabel(tr("Role korisnika %1 : ").arg(QString::fromStdString(g_DonatUser).toUpper()));

    m_lstvUserRoles = new QListWidget();
    const bool bSortingEnabled = m_lstvUserRoles->isSortingEnabled();
    m_lstvUserRoles->setSortingEnabled(false);
    GetDonatUserRoles();
    m_lstvUserRoles->setSortingEnabled(bSortingEnabled);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_lblUserRoleTitle);
    mainLayout->addWidget(m_lstvUserRoles);
    setLayout(mainLayout);
}

void FrmDonatUserRole::GetDonatUserRoles()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT KORISNIK_ID_2 FROM VEZE_KORISNIKA WHERE KORISNIK_ID = '");
    strSqlStatement.append(g_DonatUser);
    strSqlStatement.append("' GROUP BY KORISNIK_ID_2 ORDER BY 1");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QListWidgetItem *listWidgetItem = new QListWidgetItem();
            listWidgetItem->setText(QString::fromStdString(rs->getString(1)));
            m_lstvUserRoles->addItem(listWidgetItem);
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

FrmDonatUserRole::~FrmDonatUserRole()
{
    m_lstvUserRoles->clear();
}

}   // namespace log
