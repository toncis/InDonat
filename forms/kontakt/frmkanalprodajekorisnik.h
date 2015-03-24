#ifndef FRMKANALPRODAJEKORISNIK_H
#define FRMKANALPRODAJEKORISNIK_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmKanalProdajeKorisnik;
}

namespace Kontakt {
class FrmKanalProdajeKorisnik : public QDialog
{
    Q_OBJECT

public:
    explicit FrmKanalProdajeKorisnik(QWidget *parent = 0);
    ~FrmKanalProdajeKorisnik();

private slots:

    void on_btnPotvrda_clicked();

    void on_btnSetLoggedInDonatUser_clicked();

    void on_treeKorisnik_itemPressed(QTreeWidgetItem *item, int UNUSED(column));

    void on_txtFltDonatUser_textEdited(const QString &arg1);

private:
    Ui::FrmKanalProdajeKorisnik *ui;

    string m_strKORISNIK_ID;
    string m_strKORISNIK_NAZ;
    string m_strKORISNIK_IME;
    int m_iORGJED_ID;
    string m_strORGJED_NAZ;
    int m_iKANAL_ID;
    string m_strKANAL_NAZ;
    int m_iREGIJA_ID;
    string m_strREGIJA_NAZ;
    int m_iZUPANIJA_ID;
    string m_strZUPANIJA_NAZ;
    int m_iUNIO_CROS;



    void initForm();
    void popunaKorisnik();
    void dohvatiKorisnika(string strKorisnikId);
};

}
#endif // FRMKANALPRODAJEKORISNIK_H
