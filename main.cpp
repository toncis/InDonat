//
//  main.cpp
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

//#include <QtGui/QApplication>
#include <QtNetwork/QNetworkProxyFactory>
#include <QtNetwork/QSslConfiguration>
#include "forms/log/frmdonatlogin.h"
#include "forms/log/frmdonatuserlogin.h"
#include "forms/log/frmdonatmenu.h"
#include "forms/log/frmdonatmenu2.h"
#include "donat.h"

#define QUOTE_(x) #x
#define QUOTE(x) QUOTE_(x)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // Setting the Application version
    QString strApplicationName = QUOTE(APP_NAME);
    QString strApplicationVersion = QUOTE(APP_VERSION);
    app.setApplicationVersion(strApplicationVersion);
    app.setApplicationName(strApplicationName);

    // Set tr() global conversions based on UTF-8, not required for Qt v5.x
    // QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    // Set global conversions based on charsets used in Oracle environment
    // Set in CreateDonatConnection in global.cpp
    // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    // Set croatian envirorment
    // QLocale::setDefault(QLocale(QLocale::Croatian, QLocale::Croatia));

    // Set OS system proxy settings
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    // Set Certificates to use for SSL
    QSslConfiguration sslCfg = QSslConfiguration::defaultConfiguration();
    QList<QSslCertificate> ca_list = sslCfg.caCertificates();
    QList<QSslCertificate> ca_new = QSslCertificate::fromData("CaCertificates");
    ca_list += ca_new;
    sslCfg.setCaCertificates(ca_list);
    sslCfg.setProtocol(QSsl::AnyProtocol);
    QSslConfiguration::setDefaultConfiguration(sslCfg);

    using Log::FrmDonatMenu2;
    using Log::FrmDonatUserLogin;

    // Donat Login form as a splashscreen
    Log::FrmDonatLogin frmLogIn;
    if (frmLogIn.exec() == QDialog::Accepted)
    {
        // On valid login start Donat main form
        Log::FrmDonatMenu frmDonat;
//        FrmDonatMenu2 frmDonat;
        frmDonat.show();
        return app.exec();
    }
    else
    {
        app.quit();
        return 0;
    }
}
