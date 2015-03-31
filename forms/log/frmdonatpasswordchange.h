//
//  frmdonatpasswordchange.h
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


#ifndef FRMDONATPASSWORDCHANGE_H
#define FRMDONATPASSWORDCHANGE_H

#include <QtWidgets>
#include <QDialog>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QFormLayout;
class QFrame;
class QPushButton;
class QHBoxLayout;
class QWidget;
class QSpacerItem;
QT_END_NAMESPACE

namespace Log {

class FrmDonatPasswordChange : public QDialog
{
    Q_OBJECT

private :
    // [0]
    QHBoxLayout *m_hlayDonatImage;
    QLabel *m_imgDonat;

    // [1]
    QWidget *m_wgUserPasswd;
    QFormLayout *m_flayUserPasswd;
    QLabel *m_lblUserOldPasswdTitle;
    QLabel *m_lblUserNewPasswdTitle;
    QLabel *m_lblUserNewPasswdConfimationTitle;
    QLineEdit *m_txtUserOldPasswd;
    QLineEdit *m_txtUserNewPasswd;
    QLineEdit *m_txtUserNewPasswdConfimation;
    QPushButton *m_btnPotvrda;

    // Create Donat user passwd form
    void CreateFormUserPasswd();
    // Changes the password for user in Donat
    void ChangeDonatUserPasswd(string strUserName, string strNewPasswd);

public:
    explicit FrmDonatPasswordChange();
    ~FrmDonatPasswordChange();

signals:

private slots:
    void on_btnPotvrda_clicked();

};

}   // namespace log

#endif // FRMDONATPASSWORDCHANGE_H
