#ifndef FRMUGOVORIPREGLED_H
#define FRMUGOVORIPREGLED_H

#include <QDialog>
#include <QTableWidgetItem>

#include "donat.h"

namespace Ui {
class FrmUgovoriPregled;
}

namespace Sporazumi {

class FrmUgovoriPregled : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmUgovoriPregled(QWidget *parent = 0);
    explicit FrmUgovoriPregled(unsigned int iKupacId, QWidget *parent = 0);
    ~FrmUgovoriPregled();
    
private slots:
    void on_btnPrivatniKupci_clicked();
    void on_btnKlucniKupci_clicked();
    void on_btnPoslovniKupci_clicked();
    void on_btnDanas_clicked();
    void on_btnOvajTjedan_clicked();
    void on_btnOvajMjesec_clicked();
    void on_btnStatusSvi_clicked();
    void on_btnStatusUtijeku_clicked();
    void on_btnStatusRezerviran_clicked();
    void on_btnStatusStorniran_clicked();
    void on_btnStorno_clicked();
    void on_btnStornoDonat_clicked();
    void on_btnNastavakRealizacije_clicked();
    void on_btnPretvoriU1Kunu_clicked();
    void on_btnKanalProdaje_clicked();
    void on_btnMojiDokumenti_clicked();
    void on_btnOznaciSve_clicked();
    void on_btnOznaciNista_clicked();
    void on_btnPregledSporazuma_clicked();
    void on_btnPregledStanjaDonat_clicked();
    void on_btnPregledStanjaWwms_clicked();
    void on_btnPregledDetaljno_clicked();
    void on_btnPregledProcesi_clicked();
    void on_btnPregledDisKarta_clicked();
    void on_btn_Napomena_clicked();
    void on_btnDatoteka_clicked();
    void on_btnSpis_clicked();
    void on_btnJop_clicked();
    void on_btnDodijeliJop_clicked();
    void on_btnOpisZaduzenja_clicked();
    void on_btnUlaznePoruke_clicked();
    void on_btnPromjenaKPro_clicked();
    void on_btnDatumZahtjeva_clicked();
    void on_btnIsipisDokumenta_clicked();

    void on_lstvZahtjevi_itemPressed(QTableWidgetItem *item);

    void on_cboKlase_currentIndexChanged(const QString &arg1);

private:
    Ui::FrmUgovoriPregled *ui;


    // [Private Class Members]
    unsigned int m_iStrankaId;
    unsigned int m_iKupacId;
    long long m_iUlogaStrankeId;
    int m_iTipUlogaStrankeId;

    int m_iTipKanalaProdaje;
    string m_strKanalProdaje;
    int m_iFltLinijaProduktaId;

    int m_iTipDokumenta;

    unsigned int m_iSporazumId;

    // Zahtjev search mode
    enum TipKupcaSearchMode
    {
        SearchModePrivatni = 1,
        SearchModePoslovni = 2,
        SearchModeKljucni = 3
    };
    TipKupcaSearchMode m_TipKupcaSearchMode;
    enum PeriodSearchMode
    {
        SearchModeTipNone = 0,
        SearchModeDanas = 1,
        SearchModeOvajTjedan = 2,
        SearchModeOvajMjesec = 3
    };
    PeriodSearchMode m_PeriodSearchMode;
    enum StatusSearchMode
    {
        SearchModeSvi = -1,
        SearchModeUTijeku = 1,
        SearchModeRezerviran = 8,
        SearchModeRealiziran = 4,
        SearchModeStorniran = 5,
        SearchModeValidacija = 9
    };
    StatusSearchMode m_StatusSearchMode;

    QIcon m_iconCickled;

    // [Private Member Functions]
    void initFormView();
    void popuniSveKlase();
    void popuniKanalProdaje();
    void popuniZahtjeve();
};

}

#endif // FRMUGOVORIPREGLED_H
