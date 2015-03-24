/************************************* Module Header **************************************\
* Module Name:  frmdonatpasswordchange.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT user password change form.
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

#ifndef FRMDONATPASSWORDCHANGE_H
#define FRMDONATPASSWORDCHANGE_H

#include <QtWidgets>
#include <QDialog>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QFormLayout;
class QFrame;
class QPushButton;
class QHBoxLayout;
class QWidget;
class QSpacerItem;
QT_END_NAMESPACE

namespace Log {

class FrmDonatPasswordChange : public QDialog
{
    Q_OBJECT

private :
    // [0]
    QHBoxLayout *m_hlayDonatImage;
    QLabel *m_imgDonat;

    // [1]
    QWidget *m_wgUserPasswd;
    QFormLayout *m_flayUserPasswd;
    QLabel *m_lblUserOldPasswdTitle;
    QLabel *m_lblUserNewPasswdTitle;
    QLabel *m_lblUserNewPasswdConfimationTitle;
    QLineEdit *m_txtUserOldPasswd;
    QLineEdit *m_txtUserNewPasswd;
    QLineEdit *m_txtUserNewPasswdConfimation;
    QPushButton *m_btnPotvrda;

    // Create Donat user passwd form
    void CreateFormUserPasswd();
    // Changes the password for user in Donat
    void ChangeDonatUserPasswd(string strUserName, string strNewPasswd);

public:
    explicit FrmDonatPasswordChange();
    ~FrmDonatPasswordChange();

signals:

private slots:
    void on_btnPotvrda_clicked();

};

}   // namespace log

#endif // FRMDONATPASSWORDCHANGE_H
