//
//  frmdonatlogin.cpp
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


#include "frmdonatlogin.h"
#include "ui_frmdonatlogin.h"

using namespace oracle::occi;
using namespace std;

namespace Log {
FrmDonatLogin::FrmDonatLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmDonatLogin)
{
    ui->setupUi(this);

    // set initial DONAT user info
    ui->cboDatabase->addItem("SDONAT_PROD", QVariant::String);
    ui->cboDatabase->addItem("DONAT_COMPASS", QVariant::String);
    ui->cboDatabase->addItem("DONAT_RAZVOJ", QVariant::String);
    ui->cboDatabase->addItem("DONAT_TRENING", QVariant::String);
    ui->txtUserName->setText("DEV_MJELIC");
    ui->txtUserPassword->setText("asdf333$");
    ui->btnLogin->setFocus();
    ui->imgDonatTht->setVisible(false);
}

FrmDonatLogin::~FrmDonatLogin()
{
    delete ui;
}

// [Private Member Functions]
void FrmDonatLogin::getDonatUserData()
{
    string strSqlStatement;

    strSqlStatement.append("SELECT /*+ RULE */ O.ORGJED_ID,O.NAZIV ORGJED_NAZIV,K.KORISNIK_ID,K.NAZIV KORISNIK_NAZIV,NVL(K.KANAL_ID,0) KANAL_ID, ");
    strSqlStatement.append(" NVL(O.REGIJA_ID,0) REGIJA_ID,NVL(O.LOKACIJA_ID,0) ZUPANIJA_ID,NVL(KP.NAZIV,' ') KANAL_NAZIV, " );
    strSqlStatement.append(" G1.NAZIV REGIJA,G2.NAZIV ZUPANIJA,K.UPDATE_PATH,K.VER_PATH,K.KP ");
    strSqlStatement.append(" FROM ORG_JEDINICE O,KORISNICI K,KANALI_PRODAJE KP,GEO_STRUKTURE G1,GEO_STRUKTURE G2 ");
    strSqlStatement.append(" WHERE K.ODJEL_ID = O.ORGJED_ID AND KP.KANAL_ID(+)=K.KANAL_ID AND O.REGIJA_ID=G1.GEO_ID(+) ");
    strSqlStatement.append(" AND O.LOKACIJA_ID=G2.GEO_ID(+) AND K.KORISNIK_ID = USER ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            g_ORGJED_ID = rs->getInt(1);
            g_ORGJED_NAZ = rs->getString(2);
            g_KORISNIK_ID = rs->getString(3);
            g_KORISNIK_NAZ = rs->getString(4);
            g_KANAL_ID = rs->getInt(5);
            g_KANAL_NAZ = rs->getString(8);
            g_REGIJA_ID = rs->getInt(6);
            g_REGIJA_NAZ = rs->getString(9);
            g_ZUPANIJA_ID = rs->getInt(7);
            g_ZUPANIJA_NAZ = rs->getString(10);
            g_CROS = rs->getInt(13);
            // DONAT KORISNIK FILTER
            g_FILTER_ORGJED_ID = rs->getInt(1);
            g_FILTER_ORGJED_NAZ = rs->getString(2);
            g_FILTER_KORISNIK_ID = rs->getString(3);
            g_FILTER_KORISNIK_NAZ = rs->getString(4);
            g_FILTER_KANAL_ID = rs->getInt(5);
            g_FILTER_KANAL_NAZ = rs->getString(8);
            g_FILTER_REGIJA_ID = rs->getInt(6);
            g_FILTER_REGIJA_NAZ = rs->getString(9);
            g_FILTER_ZUPANIJA_ID = rs->getInt(7);
            g_FILTER_ZUPANIJA_NAZ = rs->getString(10);
            g_FILTER_CROS = rs->getInt(13);
            // DONAT KORISNIK UNIO
            g_UNIO_ORGJED_ID = rs->getInt(1);
            g_UNIO_ORGJED_NAZ = rs->getString(2);
            g_UNIO_KORISNIK_ID = rs->getString(3);
            g_UNIO_KORISNIK_NAZ = rs->getString(4);
            g_UNIO_KANAL_ID = rs->getInt(5);
            g_UNIO_KANAL_NAZ = rs->getString(8);
            g_UNIO_REGIJA_ID = rs->getInt(6);
            g_UNIO_REGIJA_NAZ = rs->getString(9);
            g_UNIO_ZUPANIJA_ID = rs->getInt(7);
            g_UNIO_ZUPANIJA_NAZ = rs->getString(10);
            g_UNIO_CROS = rs->getInt(13);
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
void FrmDonatLogin::on_btnLogin_clicked()
{
    setCursor(Qt::BusyCursor);
    try
    {
        CreateDonatConnection(
                    ui->txtUserName->text().toStdString(),
                    ui->txtUserPassword->text().toStdString(),
                    ui->cboDatabase->currentText().toStdString());
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);

        g_DonatConnected = false;
        this->setResult(QDialog::Rejected);
    }

    setCursor(Qt::ArrowCursor);
    if(g_DonatConnected == false)
    {
        return;
    }

    getDonatUserData();

    this->done(QDialog::Accepted);
}
void FrmDonatLogin::on_cboDatabase_currentIndexChanged(const QString &strDonatDatabase)
{
    if(strDonatDatabase == tr("DONAT_RAZVOJ"))
    {
        ui->txtUserName->setText(tr("DONAT"));
        ui->txtUserPassword->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("DONAT_COMPASS"))
    {
        ui->txtUserName->setText(tr("DONAT"));
        ui->txtUserPassword->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("DONAT_TRENING"))
    {
        ui->txtUserName->setText(tr("DONAT"));
        ui->txtUserPassword->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("DONAT_ACC1"))
    {
        ui->txtUserName->setText(tr("DONAT"));
        ui->txtUserPassword->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("DONAT_ACC2"))
    {
        ui->txtUserName->setText(tr("DONAT"));
        ui->txtUserPassword->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("SDONAT_PROD"))
    {
        ui->txtUserName->setText(tr("MJELIC"));
        ui->txtUserPassword->setText(tr("mjelic23$"));
    }
    else
    {
        ui->txtUserName->clear();
        ui->txtUserPassword->clear();
    }
}

}   // namespace log
