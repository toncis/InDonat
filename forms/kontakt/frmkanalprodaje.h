#ifndef FRMKANALPRODAJE_H
#define FRMKANALPRODAJE_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmKanalProdaje;
}

namespace Kontakt {
class FrmKanalProdaje : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmKanalProdaje(QWidget *parent = 0);
    explicit FrmKanalProdaje(int iFormActivity, QWidget *parent = 0);
    ~FrmKanalProdaje();
    
private slots:
    void on_btnPotvrda_clicked();

    void on_btnKanalProdaje_clicked();

    void on_btnFilter_clicked();

    void on_btnKorisnik_clicked();

    void on_btnSviKorisnici_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_treeSifre_itemPressed(QTreeWidgetItem *item, int column);

    void on_txtRegija_textEdited(const QString &arg1);

    void on_txtZupanija_textEdited(const QString &arg1);

    void on_txtKanalProdaje_textEdited(const QString &arg1);

    void on_txtOrganizacijskaJedinica_textEdited(const QString &arg1);

private:
    Ui::FrmKanalProdaje *ui;

    // Tip Stranke sifarnik
    enum TipStrankeSifarnikMode
    {
        SifarnikModeNone   = 0,
        SifarnikModeRegija = 1,
        SifarnikModeZupanija = 2,
        SifarnikModeKanalProdaje = 3,
        SifarnikModeOrganizacijskaJedinica = 4,
        SifarnikModeKorisnik = 5,
        SifarnikModeSviKorisnici = 6
    };

    TipStrankeSifarnikMode m_SifranikMode;

    // Mode kanal prodaje
    enum KanalProdajeMode
    {
        KanalProdajeFilter = 0,
        KanalProdajeKorisnik = 1
    };

    KanalProdajeMode m_KanalProdajeMode;

    int m_iFormActivity;
    int m_iZupanijaId;
    int m_iRegijaId;
    int m_iKanalId;
    int m_iOrganizacijskaJedinicaId;
    string m_strKorisdikId;


    void popuniZaPregledzahtjeva();
    void popuniZaKanalProdaje();
    void popuniZaPromjenuNaZahtjevu();
    void popuniRegiju();
    void popuniZupaniju();
    void popuniKanalProdaje();
    void popuniOrganizacijskuJedinicu();
    void popuniKorisnika();
    void popuniSveKorisnike();
    void popuniKorisnika(string strKorisnikId);

};

}
#endif // FRMKANALPRODAJE_H
