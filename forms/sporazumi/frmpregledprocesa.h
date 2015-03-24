/************************************* Module Header **************************************\
* Module Name:  frmpregledprocesa.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT pregled procesa za sporazum form.
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

#ifndef FRMPREGLEDPROCESA_H
#define FRMPREGLEDPROCESA_H

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

class FrmPregledProcesa : public QDialog
{
    Q_OBJECT
public:
    explicit FrmPregledProcesa(unsigned int iSporazumId, QWidget *parent = 0);
    ~FrmPregledProcesa();

private :
    QTableWidget *m_grdPoslovniProcesi;

    unsigned int m_iSporazumId;

    void popuniPoslovneProcese();

private slots:

signals:

public slots:

};

}   // namespace sporazumi

#endif // FRMPREGLEDPROCESA_H
