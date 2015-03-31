//
//  frmwwmspregled.h
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
