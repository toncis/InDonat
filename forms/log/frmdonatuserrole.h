//
//  frmdonatuserrole.h
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
