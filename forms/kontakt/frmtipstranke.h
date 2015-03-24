#ifndef FRMTIPSTRANKE_H
#define FRMTIPSTRANKE_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
    class FrmTipStranke;
}

namespace Kontakt {

class FrmTipStranke : public QDialog
{
    Q_OBJECT

public:
    explicit FrmTipStranke(QWidget *parent = 0);
    explicit FrmTipStranke(unsigned int iStrankaId, QWidget *parent = 0);
    explicit FrmTipStranke(unsigned int iStrankaId, unsigned int iKupacId, QWidget *parent = 0);
    ~FrmTipStranke();

private slots:

    void on_btnPotvrda_clicked();

    void on_txtTip1_textEdited(const QString &arg1);

    void on_txtTip2_textEdited(const QString &arg1);

    void on_txtTip3_textEdited(const QString &arg1);

    void on_txtSegment_textEdited(const QString &arg1);

    void on_txtOpomena_textEdited(const QString &arg1);

    void on_txtProfil_textEdited(const QString &arg1);

    void on_treeSifre_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmTipStranke *ui;

    // Tip Stranke sifarnik
    enum TipStrankeSifarnikMode
    {
        SifarnikModeTipStrankeNone   = 0,
        SifarnikModeTipStranke1 = 1,
        SifarnikModeTipStranke2 = 2,
        SifarnikModeTipStranke3 = 3,
        SifarnikModeMarketinskiSegment = 4,
        SifarnikModeTipoviOpominjanja = 5,
        SifarnikModeKreditniProfili = 6
    };

    TipStrankeSifarnikMode m_SifranikMode;

    unsigned int m_iStrankaId;
    unsigned int m_iKupacId;
    int m_iTipStranke1Id;
    int m_iTipStranke2Id;
    int m_iTipStranke3Id;
    int m_iMarketinskiSegmentId;
    int m_iTipOpominjanjaId;
    int m_iKreditniProfilId;

    bool provjeriSmijeLiMatPromjena(const unsigned int iKupacId);
    void popuniStranku(const unsigned int iStrankaId);

    void popuniTipStranke1();
    void popuniTipStranke2();
    void popuniTipStranke3();
    void popuniMarketSegmente();
    void popuniTipoveOpomena();
    void popuniKreditneProfile();

    void promjeniTipStranke();
};

}  // Kontakt

#endif // FRMTIPSTRANKE_H
