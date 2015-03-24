#ifndef FRMDONATZAHTJEVALL_H
#define FRMDONATZAHTJEVALL_H

#include <QDialog>
#include <QDateTime>
#include <QTreeWidget>
#include "donat.h"
#include "zahtjev/nodetag22.h"

namespace Ui {
    class FrmDonatZahtjevAll;
}

namespace Kontakt {

class FrmDonatZahtjevAll : public QDialog
{
    Q_OBJECT

public:
    explicit FrmDonatZahtjevAll(QWidget *parent = 0);
    explicit FrmDonatZahtjevAll(unsigned int iStrankaId, unsigned int iGrupaImovineId, QWidget *parent = 0);
    ~FrmDonatZahtjevAll();

private slots:
    void on_btnOdustani_clicked();
    void on_btnPotvrda_clicked();
    void on_btnTipZahtjeva_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_btnObvezePodmirene_clicked();
    void on_btnObvezeNisuPodmirene_clicked();
    void on_btnVaznostNiska_clicked();
    void on_btnVaznostSrednja_clicked();
    void on_btnVaznostVisoka_clicked();
    void on_btnDokumenti_clicked();
    void on_btnDatoteke_clicked();
    void on_btnKontakt_clicked();
    void on_btnPrivole_clicked();
    void on_btnAktivnostLista_clicked();
    void on_btnAktivnostDodljeli_clicked();
    void on_btnAktivnostNova_clicked();
    void on_btnAktivnostImfPodaci_clicked();
    void on_btnAktivnostNumeracija_clicked();
    void on_btnProduktiSveKlase_clicked();
    void on_btnProduktiAdsl_clicked();
    void on_btnProduktiSme_clicked();
    void on_btnProduktiUsluge_clicked();
    void on_btnProduktiOpcije_clicked();
    void on_btnProduktiMax23_clicked();
    void on_btnUslugaIskljuci_clicked();
    void on_btnUslugaAtributi_clicked();
    void on_btnUslugaUkloni_clicked();
    void on_btnPorez_clicked();
    void on_btnPrikaziImovinu_clicked();
    void on_btnPrikaziAtribute_clicked();

    void on_treeZahtjevSifarnik_itemPressed(QTreeWidgetItem *item, int column);
    void on_treeUlogaStranke_itemPressed(QTreeWidgetItem *item, int column);
    void on_treeStrankaImovina_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmDonatZahtjevAll *ui;

    int m_iAktivnostNo;
    QDateTime m_dateDatumOtvaranja;
    int m_iTipZahtjeva;

    unsigned int m_iStrankaId;
    int m_iTipStrankeId;
    unsigned int m_iKupacId;
    string m_strKupacNaziv;
    unsigned int m_iKontaktId;
    unsigned int m_iAdresaId;
    unsigned int m_iAdresaIdInstalacijeAktivna;

    string m_strKupacUloga1;
    string m_strKupacUloga2;
    string m_strKupacUloga3;
    string m_strKupacUloga4;

    unsigned int m_iSporazumId;
    unsigned int m_iNadSporazumId;
    string m_strBrojDokumenta;
    int m_iTipDokumenta;

    unsigned int m_iGrupaImovineId;
    unsigned int m_iAktivnaGrupaImovineId;


    list<NodeTag22> m_lstTree22;
    int m_iPaketTel;
    int m_iPaketAkt;

    void init();
    void setDatum();
    void setDokumentNo();
    void popunaStranka();
    void popunaTelGim();
    void popunaRi();
    void popunaMo();

    void popunaKlasa();
    void popunaKlasaAdsl();
    void popunaKlasaSme();
    void popuniKupacTel();
    void popuniTelGim();

    void setButtonsForKlasaAdd();
    void setButtonsClose();
    unsigned int vratiAdslAsset(unsigned int iGrupaImovineId);

    int jeLiMax3(unsigned int iGrupaImovineId);

};

}
#endif // FRMDONATZAHTJEVALL_H
