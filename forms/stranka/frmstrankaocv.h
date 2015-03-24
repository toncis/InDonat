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
