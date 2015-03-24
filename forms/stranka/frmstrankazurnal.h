#ifndef FRMSTRANKAZURNAL_H
#define FRMSTRANKAZURNAL_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "donat.h"

namespace Ui {
class FrmStrankaZurnal;
}

namespace Stranka {

class FrmStrankaZurnal : public QDialog
{
    Q_OBJECT
    
public:

    explicit FrmStrankaZurnal(
        unsigned int iKupacId,
        unsigned int iGrupaImovineId = 0,
        QWidget *parent = 0);

    ~FrmStrankaZurnal();
    
private slots:
    void on_btnTrazi_clicked();
    void on_btnSearchPhoneNumber_clicked();
    void on_btnSearchUlogaStranke_clicked();

    void on_treeIzmjene_itemPressed(QTreeWidgetItem *item, int column);

    void on_treeGrupeImovine_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmStrankaZurnal *ui;

    unsigned int m_iKupacId;
    unsigned int m_iGrupaImovineId;
    string m_strTelefonskiBroj;
    int m_iTipPromjene;
    int m_iTipPretrage;
    unsigned int m_iMaticnePromjeneId;
    unsigned int m_iMaticnePromjenePrijeId;


    struct gim_struktura_sve_t {
      string Tip;
      unsigned int Asset;
      unsigned int GrupaImovineId;
      string TelefonskiBroj;
      string Klasa;
    };

    struct maticna_promjena_t {
        unsigned int MATPROM_ID;
        unsigned int ULSTRANKE_ID;
        string FORMATIRANI_NAZIV;
        string NAZIV3;
        string TITULA;
        string TIP_ISPRAVE;
        string BROJ_ISPRAVE;
        string TIP_PORB;
        string MBR;
        string TIP_STRANKE;
        string PODTIP_STRANKE;
        string MARKET_SEGMENT;
        string VRSTA_RACUNA;
        string MEDIJ_RACUNA;
        string KRED_KLASA;
        string TIP_OPOMINJANJA;
        string POREZ;
        string NAZIV_KONTAKTA;
        string ADRESA_KONTAKTA;
        string DATUM_PROMJENE;
        string OPERATER;
    };

    struct maticna_promjena_tel_t {
        unsigned int MATPROM_TEL_ID;
        unsigned int MATPROM_ID;
        unsigned int GIMOVINE_ID;
        string KLASA;
        string TELEFON;
        int B1;
        string PRETPLATA;
        string DOD_USLUGE;
        string TITULA;
        string TIP_ISPRAVE;
        string BROJ_ISPRAVE;
        string TIP_PORB;
        string MBR;
        string TIP_STRANKE;
        string PODTIP_STRANKE;
        string MARKET_SEGMENT;
        string VRSTA_RACUNA;
        string MEDIJ_RACUNA;
        string KRED_KLASA;
        string TIP_OPOMINJANJA;
        string POREZ;
        unsigned int BILL_ID;
        unsigned int CUST_ID;
        unsigned int SERV_ID;
        unsigned int KONT_ID;
        string NAZIV_BILL;
        string ADRESA_BILL;
        string NAZIV_CUST;
        string ADRESA_CUST;
        string NAZIV_SERV;
        string ADRESA_SERV;
        string NAZIV_KONT;
        string ADRESA_KONT;
        string DATUM_PROMJENE;
        string OPERATER;
        string STATUS;
    };

    maticna_promjena_tel_t m_GrupaImovinePromjenaPrije;
    maticna_promjena_tel_t m_GrupaImovinePromjena;

    maticna_promjena_t m_UlogaStrankePromjenaPrije;
    maticna_promjena_t m_UlogaStrankePromjena;

    void popuniPoTelefonskomBroju();
    void popuniGrupuImovine();
    void popuniUlogeGrupeImovine();
    void popuniListePromjena();
    void popuniListePromjenaUlogaStranke();
    void popuniMaticnuPromjenuZaGrupuImovine();
    void popuniMaticnuPromjenuPrijeZaGrupuImovine();
    void popuniMaticnuPromjenuZaUloguStranke();
    void popuniMaticnuPromjenuPrijeZaUloguStranke();
    void clearPromjena();

};

} //Stranka

#endif // FRMSTRANKAZURNAL_H
