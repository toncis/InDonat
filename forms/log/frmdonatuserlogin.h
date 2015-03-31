//
//  frmdonatuserlogin.h
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


#ifndef FRMDONATUSERLOGIN_H
#define FRMDONATUSERLOGIN_H

#include <QtWidgets>
#include <QDialog>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QFormLayout;
class QPushButton;
class QWidget;
class QComboBox;
QT_END_NAMESPACE

namespace Log {

class FrmDonatUserLogin : public QDialog
{
    Q_OBJECT

private :
    // [0]
    QHBoxLayout *m_hlayDonatImage;
    QLabel *m_imgDonat;

    // [1]
    QWidget *m_wgUserLogin;
    QFormLayout *m_flayUserPasswd;
    QLabel *m_lblDonatUserNameTitle;
    QLabel *m_lblDonatUserPasswdTitle;
    QLabel *m_lblDonatDabaseTitle;
    QLineEdit *m_txtDonatUserName;
    QLineEdit *m_txtDonatUserPasswd;
    QComboBox *m_cboDonatDatabase;
    QPushButton *m_btnLogin;

    // [2]
    QLabel *m_imgTcom;

    void CreateFormUserLogin();
    void getDonatUserData();

public:
    explicit FrmDonatUserLogin();
    ~FrmDonatUserLogin();

signals:

private slots:
    void on_btnLogin_clicked();
    void on_cboDatabase_currentIndexChanged(const QString &strDonatDatabase);

};

}   // namespace log

#endif // FRMDONATUSERLOGIN_H
