//
//  frmdonatpasswordchange.cpp
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

#include "frmdonatpasswordchange.h"

namespace Log {

FrmDonatPasswordChange::FrmDonatPasswordChange()
{
    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT - Promjena zaporke"));

    // [0]
    m_hlayDonatImage = new QHBoxLayout(this);
    m_hlayDonatImage->setObjectName(QString::fromUtf8("horizontalLayout"));
    m_imgDonat = new QLabel(this);
    QSizePolicy imgSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    imgSizePolicy.setHorizontalStretch(0);
    imgSizePolicy.setVerticalStretch(0);
    imgSizePolicy.setHeightForWidth(m_imgDonat->sizePolicy().hasHeightForWidth());
    m_imgDonat->setSizePolicy(imgSizePolicy);
    m_imgDonat->setPixmap(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ImgDonatLogIn.png")));
    m_hlayDonatImage->addWidget(m_imgDonat);

    // [1]
    CreateFormUserPasswd();

    // Make dialog fixed size
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void FrmDonatPasswordChange::CreateFormUserPasswd()
{
    m_wgUserPasswd = new QWidget(this);
    m_wgUserPasswd->setGeometry(QRect(340, 180, 261, 131));
    m_flayUserPasswd = new QFormLayout(m_wgUserPasswd);
    m_lblUserOldPasswdTitle = new QLabel(tr("Stara zaporka : "));
    m_lblUserNewPasswdTitle = new QLabel(tr("Nova zaporka : "));
    m_lblUserNewPasswdConfimationTitle = new QLabel(tr("Provjera : "));
    m_txtUserOldPasswd = new QLineEdit(QString::fromStdString(g_DonatUserPasswd));
    m_txtUserOldPasswd->setEchoMode(QLineEdit::Password);
    m_txtUserNewPasswd = new QLineEdit();
    m_txtUserNewPasswd->setEchoMode(QLineEdit::Password);
    m_txtUserNewPasswdConfimation = new QLineEdit();
    m_txtUserNewPasswdConfimation->setEchoMode(QLineEdit::Password);
    m_btnPotvrda = new QPushButton(tr("POTVRDA"));
    m_flayUserPasswd->addRow(m_lblUserOldPasswdTitle, m_txtUserOldPasswd);
    m_flayUserPasswd->addRow(m_lblUserNewPasswdTitle, m_txtUserNewPasswd);
    m_flayUserPasswd->addRow(m_lblUserNewPasswdConfimationTitle, m_txtUserNewPasswdConfimation);
    m_flayUserPasswd->addRow(NULL, m_btnPotvrda);

    m_txtUserNewPasswd->setFocus();

    // OK button
    connect(m_btnPotvrda, SIGNAL(clicked()), this, SLOT(on_btnPotvrda_clicked()));
}

void FrmDonatPasswordChange::ChangeDonatUserPasswd(string strUserName, string strNewPasswd)
{
    try
    {
        g_DonatConn->changePassword(strUserName, g_DonatUserPasswd, strNewPasswd);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->commit();


//    string strSqlStatement;
//    strSqlStatement.append("BEGIN DNT_SECURITY.PROMIJENI_SIFRU(:p_username, :p_password, :rezultat); END;");
//    Statement *sqlStatement = g_DonatConn->createStatement();
//    sqlStatement->setSQL(strSqlStatement);
//    sqlStatement->setAutoCommit(TRUE);

//    try
//    {
//        sqlStatement->setString(1, strUserName);
//        sqlStatement->setString(2, strNewPasswd);
//        sqlStatement->registerOutParam(3, OCCISTRING, 250);
//        sqlStatement->executeUpdate();
//        string strDBMessage = sqlStatement->getString(3);
//        if(strDBMessage == "OK")
//        {
//            QMessageBox::information(this,
//                                     tr("DONAT - Promjena zaporke"),
//                                     tr("Vaša zaporka je pormijenjena. Ponovo pokrenite DONAT sa novom zaporkom."),
//                                     QMessageBox::Ok);
//        }
//        else
//        {
//            QMessageBox::critical(this,
//                                  tr("DONAT - Promjena zaporke"),
//                                  QString::fromStdString(strDBMessage),
//                                  QMessageBox::Close);
//        }
//    }
//    catch(SQLException &ex)
//    {
//        QMessageBox::critical(this, tr("DONAT - Database Error"),
//                                       QString::fromStdString(ex.getMessage()),
//                                       QMessageBox::Close);
//    }

//    g_DonatConn->terminateStatement(sqlStatement);
//    strSqlStatement.erase();
}

void FrmDonatPasswordChange::on_btnPotvrda_clicked()
{
    if(m_txtUserOldPasswd->text() != QString::fromStdString(g_DonatUserPasswd))
    {
        QMessageBox::critical(this,
                              tr("DONAT - Promjena zaporke"),
                              tr("Molimo unesite ispravno staru zaporuku!"),
                              QMessageBox::Close);
        m_txtUserOldPasswd->setFocus();
        return;
    }

    if(m_txtUserNewPasswd->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("DONAT - Promjena zaporke"),
                              tr("Molimo unesite novu zaporuku!"),
                              QMessageBox::Close);
        m_txtUserNewPasswd->setFocus();
        return;
    }

    if(m_txtUserNewPasswdConfimation->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("DONAT - Promjena zaporke"),
                              tr("Molimo unesite potvrdu nove zaporuke!"),
                              QMessageBox::Close);
        m_txtUserNewPasswdConfimation->setFocus();
        return;
    }

    if(m_txtUserNewPasswd->text() != m_txtUserNewPasswdConfimation->text())
    {
        QMessageBox::critical(this,
                              tr("DONAT - Promjena zaporke"),
                              tr("Molimo ponovo potvrdite novu zaporuku!"),
                              QMessageBox::Close);
        m_txtUserNewPasswdConfimation->setFocus();
        return;
    }

    ChangeDonatUserPasswd(g_DonatUser, m_txtUserNewPasswd->text().toStdString());
}

FrmDonatPasswordChange::~FrmDonatPasswordChange()
{
    m_imgDonat->clear();
}

}   // namespace log
