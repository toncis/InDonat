//
//  frmstrankaocv.cpp
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

#include "frmstrankaocv.h"
#include "qwebpage.h"

namespace Stranka {

// [Class Constructors]
FrmStrankaOcv::FrmStrankaOcv(string strOib, string strBrojTelefona)
{
    m_strOib = strOib;
    m_strBrojTelefona = strBrojTelefona;

    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT - Stranka - One Customer View"));

    QVBoxLayout *mainLayout = new QVBoxLayout();

    m_btnBox = new QDialogButtonBox();
    m_btnBox->setObjectName(QString::fromUtf8("buttonBox"));
//    m_btnBox->setGeometry(QRect(230, 530, 341, 32));
    m_btnBox->setOrientation(Qt::Horizontal);
    m_btnBox->setStandardButtons(QDialogButtonBox::Close);

//    m_webOsf = new QWebView();
//    m_webOsf->setObjectName(QString::fromUtf8("webView"));
//    m_webOsf->setGeometry(QRect(10, 10, 1024, 764));
//    m_webOsf->setUrl(QUrl("about:blank"));

//    mainLayout->addWidget(m_webOsf);
    mainLayout->addWidget(m_btnBox);
    setLayout(mainLayout);

    QObject::connect(m_btnBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_btnBox, SIGNAL(rejected()), this, SLOT(reject()));

//    QObject::connect(m_webOcv->page()->networkAccessManager(),
//                SIGNAL(sslErrors(QNetworkReply* , const QList<QSslError> & )),
//                this,
//                SLOT(sslErrorHandler(QNetworkReply* , const QList<QSslError> & )));

    startOsfWebView();
}

// [Private Member Functions]
void FrmStrankaOcv::getOsfUrl()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT MAX(DEF_VRIJEDNOST) OCV FROM VRSTE_PARAMETARA WHERE NAZIV='OCV_URL' ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_strOsfUrl = rs->getString(1);
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

void FrmStrankaOcv::startOsfWebView()
{
    getOsfUrl();
    getSso();
    // m_strOsfUrl = "https://webpos.hr.t-mobile.local:7009/OCV/ocv.jsf?";
    m_strOsfUrl.append("OTP=");
    m_strOsfUrl.append(m_strSessionId);
    m_strOsfUrl.append("&MODULE_CODE=OCV");
    m_strOsfUrl.append("&USER=DONAT");
    m_strOsfUrl.append("&OIB=");
    m_strOsfUrl.append(m_strOib);
    m_strOsfUrl.append("&MODE=FULL");
    if(m_strBrojTelefona.length() > 0)
    {
        m_strOsfUrl.append("&MAIN_NUMBER=");
        m_strOsfUrl.append(m_strBrojTelefona);
    }

    // Open OSF portal in WebView control.
    // Not working HTTPS certificates problem.
//    m_webOsf->load(QUrl(QString::fromStdString(m_strOsfUrl)));
//    m_webOsf->show();

    // Open OSF portal in OS default web browser.
//    m_webOsf->setUrl(QUrl(QString::fromStdString(m_strOsfUrl)));
    QDesktopServices::openUrl(QUrl(QString::fromStdString(m_strOsfUrl)));
    this->close();
}

void FrmStrankaOcv::getSso()
{
        string strSqlStatement;
        strSqlStatement.append("BEGIN :nSessionId := dnt_sso_lite.set_agent_sso_session(:i_module_partner_code, :i_agent_username, :i_agent_ip_address, :i_oib); END;");
        Statement *sqlStatement = g_DonatConn->createStatement();
        sqlStatement->setSQL(strSqlStatement);
        sqlStatement->setAutoCommit(TRUE);

        try
        {
            sqlStatement->registerOutParam(1, OCCISTRING, 250);
            sqlStatement->setString(2, "OCV");
            // sqlStatement->setString(3, g_DonatUser);
            sqlStatement->setString(3, "DKRALJ");
            sqlStatement->setString(4, "127.0.0.1");
            sqlStatement->setString(5, m_strOib);
            sqlStatement->executeUpdate();
            m_strSessionId = sqlStatement->getString(1);
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
/*
void FrmStrankaOcv::sslErrorHandler(QNetworkReply* reply, const QList<QSslError> &errors)
{

  #if DEBUG_BUYIT
  qDebug() << "---FrmStrankaOcv::sslErrorHandler: ";
  // show list of all ssl errors
  foreach (QSslError err, errlist)
    qDebug() << "ssl error: " << err;
  #endif

}
*/


FrmStrankaOcv::~FrmStrankaOcv()
{
//    m_webOsf->close();
}

}   // namespace log
