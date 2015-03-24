/************************************* Module Header **************************************\
* Module Name:  frmstavkesporazuma.cpp
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

#ifndef FRMSTAVKESPORAZUMA_H
#define FRMSTAVKESPORAZUMA_H

#include <QtWidgets>
#include <QDialog>
#include <QTableWidget>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QFormLayout;
class QFrame;
class QPushButton;
class QHBoxLayout;
class QWidget;
class QTableWidget;
QT_END_NAMESPACE

namespace Sporazumi {

class FrmStavkeSporazuma : public QDialog
{
    Q_OBJECT
public:
    explicit FrmStavkeSporazuma(unsigned int iSporazumId, QWidget *parent = 0);
    ~FrmStavkeSporazuma();

private :
    QTableWidget *m_grdStavkeSporazuma;

    unsigned int m_iSporazumId;

    void popuniStavkeSporazuma();

private slots:

signals:

public slots:

};

}   // namespace sporazumi

#endif // FRMSTAVKESPORAZUMA_H
