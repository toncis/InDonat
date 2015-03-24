/************************************* Module Header **************************************\
* Module Name:  frmdonatuserrole.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of DONAT user role form
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

#ifndef FRMDONATUSERROLE_H
#define FRMDONATUSERROLE_H

#include <QtWidgets>
#include <QDialog>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QLabel;
class QFrame;
QT_END_NAMESPACE

namespace Log {

class FrmDonatUserRole : public QDialog
{
    Q_OBJECT

private:
    // [0]
    QLabel *m_lblUserRoleTitle;
    QListWidget *m_lstvUserRoles;

    void GetDonatUserRoles();

public:
    explicit FrmDonatUserRole();
    ~FrmDonatUserRole();

signals:

public slots:

};

}   // namespace log

#endif // FRMDONATUSERROLE_H
