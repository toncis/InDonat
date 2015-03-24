/************************************* Module Header **************************************\
* Module Name:  frmdonatabout.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of DONAT about form
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

#ifndef FRMDONATABOUT_H
#define FRMDONATABOUT_H

#include <QtWidgets>
#include <QDialog>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QAction;
class QDialogButtonBox;
class QLabel;
class QFrame;
QT_END_NAMESPACE

namespace Log {

class FrmDonatAbout : public QDialog
{
    Q_OBJECT

public:
    explicit FrmDonatAbout();
    ~FrmDonatAbout();

private:
    // [0]
    QLabel *m_imgDonat;
    QFrame *m_frame1;

    // [2]
    QFrame *m_frame2;
    QLabel *m_lblApplicationTitle;
    QLabel *m_lblApplicationVersion;
    QLabel *m_lblApplicationCopyright;
    QLabel *m_lblApplicationDesc;
    QLabel *m_lblApplicationFolder;

    // [3]
    QFrame *m_frame3;
    QDialogButtonBox *m_dboxButton;

    void createFrame1();
    void createFrame2();
    void createFrame3();

signals:

public slots:

};

}   // namespace log

#endif // FRMDONATABOUT_H
