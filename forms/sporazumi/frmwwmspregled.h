/************************************* Module Header **************************************\
* Module Name:  frmwwmspregled.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT WWMS pregled ticket-a za sporazum form.
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

#ifndef FRMWWMSPREGLED_H
#define FRMWWMSPREGLED_H

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

class FrmWwmsPregled : public QDialog
{
    Q_OBJECT
public:
    explicit FrmWwmsPregled(unsigned int iSporazumId, int iTipSporazumaId = 1, QWidget *parent = 0);
    ~FrmWwmsPregled();

private :
    QFrame *m_fraTicket;
    QLineEdit *m_txtDatumOd;
    QLineEdit *m_txtDatumDo;
    QLineEdit *m_txtTicketId;

    QLineEdit *m_txtZadatak;
    QLineEdit *m_txtStatus;
    QLineEdit *m_txtPodrucje;
    QLineEdit *m_txtIzvrsitelj;

    QTableWidget *m_grdTicket;

    unsigned int m_iSporazumId;
    int m_iTipSporazumaId;

    void createTicketFrame();
    void createGridFrame();

    void popuniWwmsPregled();
    void popuniWwmsTicket(string strTicketId);

private slots:
    void on_grdTicket_itemPressed(QTableWidgetItem* itemTicket);

signals:

public slots:

};

}   // namespace sporazumi

#endif // FRMWWMSPREGLED_H
