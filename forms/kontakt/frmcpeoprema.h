#ifndef FRMCPEOPREMA_H
#define FRMCPEOPREMA_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"
#include "cpe/nodetag_cpe_2.h"

namespace Ui {
    class FrmCpeOprema;
}

namespace Kontakt {

class FrmCpeOprema : public QDialog
{
    Q_OBJECT

public:
    explicit FrmCpeOprema(QWidget *parent = 0);
    explicit FrmCpeOprema(unsigned int iKupacId, QWidget *parent = 0);
    ~FrmCpeOprema();

private slots:
    void on_btnTrazi_clicked();
    void on_btnTelefon_clicked();
    void on_btnKupacId_clicked();
    void on_btnAsset_clicked();
    void on_btnTicket_clicked();
    void on_btnSerijskiBroj_clicked();
    void on_btnPotvrdaNovogStanja_clicked();
    void on_btnZatvori_clicked();

    void on_treeOprema_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmCpeOprema *ui;

    // Donat main search mode
    enum DonatSearchMode
    {
        TraziPoNazivKorisnika = 1,
        TraziPoBrojTelefona = 2,
        TraziPoJmbg = 3,
        TraziPoOib = 4,
        TraziPoUlogaStrankeId = 5,
        TraziPoTicketId = 6,
        TraziPoAssetId = 7,
        TraziPoGrupna = 8,
        TraziPoHijerahija = 9,
        TraziPoSerijskiBroj = 10
    };
    // Used for storing CPE data
    struct gim_struktura_t {
      unsigned int KupacId;
      unsigned int IsporukaId;
      unsigned int NapalataId;
      int Status;
      string Tip;
      unsigned int Asset;
      unsigned int GrupaImovineId;
      string TelefonskiBroj;
      string Klasa;
    };
    struct gim_cpe_promjena_struktura_t {
        unsigned int CpePromjenaId;
        unsigned int CpeId;
        unsigned int ImovinaId;
        unsigned int AktInd;
        string Datum;
    };

    list<NodeTag_Cpe_2> m_lstTree2;

    DonatSearchMode m_SearchMode;

    unsigned int m_iKupacId;
    unsigned int m_iInstalacijaId;
    unsigned int m_iImovinaId;
    unsigned int m_iCpePromjenaId;

    void clearFormData();
    void popuniCpeStanja();
    void popuniGrupuImovine(unsigned int iGrupaImovineId);
    void popuniCpeOpremu(gim_struktura_t gim);
    void popuniKupca(const unsigned int iKupacId);
    void popuniInstalaciju(const unsigned int iInstalacijaId);
    void popuniCpe(const unsigned int iCpePromjenaId);
    void popuniImovinu(const unsigned int iImovinaId);
    void traziPoBrojTelefona();
    void traziPoKupcu();
    void traziPoAssetId();
    void traziPoTicketId();
    void traziPoSerijskiBroj();

};

}

#endif // FRMCPEOPREMA_H

