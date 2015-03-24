/************************************* Module Header **************************************\
* Module Name:  frmdonatuserlogin.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of DONAT user login form
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

#ifndef FRMDONATUSERLOGIN_H
#define FRMDONATUSERLOGIN_H

#include <QtWidgets>
#include <QDialog>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QFormLayout;
class QPushButton;
class QWidget;
class QComboBox;
QT_END_NAMESPACE

namespace Log {

class FrmDonatUserLogin : public QDialog
{
    Q_OBJECT

private :
    // [0]
    QHBoxLayout *m_hlayDonatImage;
    QLabel *m_imgDonat;

    // [1]
    QWidget *m_wgUserLogin;
    QFormLayout *m_flayUserPasswd;
    QLabel *m_lblDonatUserNameTitle;
    QLabel *m_lblDonatUserPasswdTitle;
    QLabel *m_lblDonatDabaseTitle;
    QLineEdit *m_txtDonatUserName;
    QLineEdit *m_txtDonatUserPasswd;
    QComboBox *m_cboDonatDatabase;
    QPushButton *m_btnLogin;

    // [2]
    QLabel *m_imgTcom;

    void CreateFormUserLogin();
    void getDonatUserData();

public:
    explicit FrmDonatUserLogin();
    ~FrmDonatUserLogin();

signals:

private slots:
    void on_btnLogin_clicked();
    void on_cboDatabase_currentIndexChanged(const QString &strDonatDatabase);

};

}   // namespace log

#endif // FRMDONATUSERLOGIN_H
