//
//  frmdonatuserrole.cpp
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
