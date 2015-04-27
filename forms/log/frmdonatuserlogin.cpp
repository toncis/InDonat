//
//  frmdonatuserlogin.cpp
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


#include "frmdonatuserlogin.h"

using namespace oracle::occi;
using namespace std;

namespace Log {

// [Class Constructors]
FrmDonatUserLogin::FrmDonatUserLogin()
{
    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT - Prijava korisnika"));

    // [0]
    m_hlayDonatImage = new QHBoxLayout();
    m_hlayDonatImage->setObjectName(QString::fromUtf8("imghorizontalLayout"));
    m_imgDonat = new QLabel();
    m_imgDonat->setPixmap(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ImgDonatLogIn.png")));
    QSizePolicy imgDonatSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    imgDonatSizePolicy.setHorizontalStretch(0);
    imgDonatSizePolicy.setVerticalStretch(0);
    imgDonatSizePolicy.setHeightForWidth(m_imgDonat->sizePolicy().hasHeightForWidth());
    m_imgDonat->setSizePolicy(imgDonatSizePolicy);
    m_hlayDonatImage->addWidget(m_imgDonat);
    setLayout(m_hlayDonatImage);

    QWidget *wgTcom = new QWidget(this);
    wgTcom->setGeometry(QRect(410, 16, 181, 48));
    m_imgTcom = new QLabel(wgTcom);
    m_imgTcom->setPixmap(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/T_zivjeti_zajedno.jpg")));
    QSizePolicy imgTcomSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    imgTcomSizePolicy.setHorizontalStretch(0);
    imgTcomSizePolicy.setVerticalStretch(0);
    imgTcomSizePolicy.setHeightForWidth(m_imgTcom->sizePolicy().hasHeightForWidth());
    m_imgTcom->setSizePolicy(imgTcomSizePolicy);
    m_imgTcom->setVisible(false);

    // [1]
    CreateFormUserLogin();

    // Make dialog fixed size
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}
FrmDonatUserLogin::~FrmDonatUserLogin()
{
    m_imgDonat->clear();
    m_imgTcom->clear();
}

// [Private Member Functions]
void FrmDonatUserLogin::CreateFormUserLogin()
{
    m_wgUserLogin = new QWidget(this);
    m_flayUserPasswd = new QFormLayout(m_wgUserLogin);
    m_lblDonatUserNameTitle = new QLabel(tr("Korisnik : "));
    m_lblDonatUserPasswdTitle = new QLabel(tr("Zaporka : "));
    m_lblDonatDabaseTitle = new QLabel(tr("Server : "));
    // m_txtDonatUserName = new QLineEdit();
//    m_txtDonatUserName = new QLineEdit(tr("DONAT"));
//    m_txtDonatUserName = new QLineEdit(tr("DEV_TSVILICIC"));
    m_txtDonatUserName = new QLineEdit(tr("DEV_MJELIC"));
    // m_txtDonatUserPasswd = new QLineEdit();
//    m_txtDonatUserPasswd = new QLineEdit(tr("donat"));
//    m_txtDonatUserPasswd = new QLineEdit(tr("ZXhiCO4x"));
    m_txtDonatUserPasswd = new QLineEdit(tr("asdf444$"));
    m_txtDonatUserPasswd->setEchoMode(QLineEdit::Password);
    m_cboDonatDatabase = new QComboBox();
    m_cboDonatDatabase->setEditable(TRUE);
    m_cboDonatDatabase->addItem("SDONAT_PROD", QVariant::String);
    m_cboDonatDatabase->addItem("DONAT_COMPASS", QVariant::String);
    m_cboDonatDatabase->addItem("DONAT_RAZVOJ", QVariant::String);
    m_cboDonatDatabase->addItem("DONAT_TRENING", QVariant::String);
    m_btnLogin = new QPushButton(tr("OK"));

    QSizePolicy grdSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grdSizePolicy.setHorizontalStretch(0);
    grdSizePolicy.setVerticalStretch(0);
    // m_wgUserLogin->setSizePolicy(grdSizePolicy);
    m_wgUserLogin->setGeometry(QRect(340, 180, 251, 148));

    m_flayUserPasswd->addRow(m_lblDonatUserNameTitle, m_txtDonatUserName);
    m_flayUserPasswd->addRow(m_lblDonatUserPasswdTitle, m_txtDonatUserPasswd);
    m_flayUserPasswd->addRow(m_lblDonatDabaseTitle, m_cboDonatDatabase);
    m_flayUserPasswd->addRow(NULL, m_btnLogin);

    // m_txtDonatUserName->setFocus();
    m_btnLogin->setFocus();

    // OK button
    connect(m_btnLogin, SIGNAL(clicked()), this, SLOT(on_btnLogin_clicked()));

    // Donat Database ComboBox
    connect(m_cboDonatDatabase, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_cboDatabase_currentIndexChanged(QString)));

}
void FrmDonatUserLogin::getDonatUserData()
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
void FrmDonatUserLogin::on_btnLogin_clicked()
{
    setCursor(Qt::BusyCursor);
    try
    {
        CreateDonatConnection(
                    m_txtDonatUserName->text().toStdString(),
                    m_txtDonatUserPasswd->text().toStdString(),
                    m_cboDonatDatabase->currentText().toStdString());
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
void FrmDonatUserLogin::on_cboDatabase_currentIndexChanged(const QString &strDonatDatabase)
{
    if(strDonatDatabase == tr("DONAT_RAZVOJ"))
    {
        m_txtDonatUserName->setText(tr("DONAT"));
        m_txtDonatUserPasswd->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("DONAT_COMPASS"))
    {
        m_txtDonatUserName->setText(tr("DONAT"));
        m_txtDonatUserPasswd->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("DONAT_TRENING"))
    {
        m_txtDonatUserName->setText(tr("DONAT"));
        m_txtDonatUserPasswd->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("DONAT_ACC1"))
    {
        m_txtDonatUserName->setText(tr("DONAT"));
        m_txtDonatUserPasswd->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("DONAT_ACC2"))
    {
        m_txtDonatUserName->setText(tr("DONAT"));
        m_txtDonatUserPasswd->setText(tr("donat"));
    }
    else if(strDonatDatabase == tr("SDONAT_PROD"))
    {
        m_txtDonatUserName->setText(tr("DEV_MJELIC"));
        m_txtDonatUserPasswd->setText(tr("asdf444$"));
    }
    else
    {
        m_txtDonatUserName->clear();
        m_txtDonatUserPasswd->clear();
    }
}

}   // namespace log
