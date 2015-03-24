/************************************* Module Header **************************************\
* Module Name:  frmdonatlogin.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of DONAT login form
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

#ifndef FRMDONATLOGIN_H
#define FRMDONATLOGIN_H

#include <QDialog>
#include "donat.h"

namespace Ui {
    class FrmDonatLogin;
}

namespace Log {

class FrmDonatLogin : public QDialog
{
    Q_OBJECT

public:
    explicit FrmDonatLogin(QWidget *parent = 0);
    ~FrmDonatLogin();

private slots:
     void on_btnLogin_clicked();

     void on_cboDatabase_currentIndexChanged(const QString &arg1);

private:
    Ui::FrmDonatLogin *ui;

    void getDonatUserData();

};

}   // namespace log

#endif // FRMDONATLOGIN_H
