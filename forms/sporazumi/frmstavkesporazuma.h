//
//  frmstavkesporazuma.h
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
