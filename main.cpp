/************************************* Module Header **************************************\
* Module Name:  main.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementation of DONAT application main
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
