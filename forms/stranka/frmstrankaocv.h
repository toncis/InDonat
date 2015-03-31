//
//  frmstrankaocv.h
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

#ifndef FRMSTRANKAOCV_H
#define FRMSTRANKAOCV_H

#include <QtWidgets>
#include <QDialog>
#include <QDialogButtonBox>
//#include <QtWebKit/QWebView>
//#include <QtWebKit/QWebPage>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QWebView;
class QLabel;
class QPushButton;
class QFrame;
class QDialogButtonBox;
QT_END_NAMESPACE

namespace Stranka {

class FrmStrankaOcv : public QDialog
{
    Q_OBJECT

private:
    // [0]
    QWebView *m_webOsf;
    QDialogButtonBox *m_btnBox;

    string m_strOib;
    string m_strBrojTelefona;
    string m_strSessionId;
    string m_strOsfUrl;

    void startOsfWebView();
    void getOsfUrl();
    void getSso();

public:
    explicit FrmStrankaOcv(string strOib, string strBrojTelefona = "");
    ~FrmStrankaOcv();

signals:

public slots:
    //void sslErrorHandler(QNetworkReply* reply, const QList<QSslError> &errors);


};

}   // namespace log

#endif // FRMSTRANKAOCV_H
