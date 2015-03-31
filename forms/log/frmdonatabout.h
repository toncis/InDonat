//
//  frmdonatabout.h
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
