#ifndef FRMMDM1_H
#define FRMMDM1_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmMdm1;
}

namespace Stranka {

class FrmMdm1 : public QDialog
{
    Q_OBJECT

public:
    explicit FrmMdm1(const string strOib, const unsigned int iKupacId = 0, const unsigned int iMdmId = 0, QWidget *parent = 0);
    explicit FrmMdm1(const string strOib, QWidget *parent = 0);
    explicit FrmMdm1(const unsigned int iKupacId, QWidget *parent = 0);
    ~FrmMdm1();

private slots:
    void on_btnTrazi_clicked();

    void on_btnOib_clicked();

    void on_btnKupacId_clicked();

    void on_btnMdmId_clicked();

    void on_btnValidirajMdm_clicked();

    void on_btnBillingAccountPovezivanje_clicked();

    void on_treeMdmStranke_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::FrmMdm1 *ui;

    QIcon m_iconAdressValid;
    QIcon m_iconZuti;
    QIcon m_iconZeleni;
    QIcon m_iconCrveni;
    QIcon m_iconTransparent;

    // Stranka sifarnik
    enum MdmSearchMode
    {
        TraziOib   = 0,
        TraziKupacId = 1,
        TraziMdmId = 2
    };

    MdmSearchMode m_MdmMode;

    unsigned int m_iKupacId;
    string m_strOib;
    unsigned int m_iMdmId;


    void initForm();
    void clearFormData();

    void popuniMdmOib();
    void popuniMdmKupacId();
    void popuniMdmMdmId();
    void popuniMdmUloge(const unsigned int iMdmId);

};

} // Stranka Namespace

#endif // FRMMDM1_H
