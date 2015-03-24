#ifndef FRMKONTAKTNICENTARPRETRAGA_H
#define FRMKONTAKTNICENTARPRETRAGA_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "donat.h"

namespace Ui {
class FrmKontaktniCentarPretraga;
}

namespace Kontakt {

class FrmKontaktniCentarPretraga : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmKontaktniCentarPretraga(QWidget *parent = 0);
    ~FrmKontaktniCentarPretraga();
    
private slots:
    void on_btnSearchByName_clicked();

    void on_btnSearchByPhone_clicked();

    void on_btnSearchByJmbg_clicked();

    void on_btnSearchByOib_clicked();

    void on_btnSearchByUlogaStrankeId_clicked();

    void on_btnSearchByGrupaImovineId_clicked();

    void on_btnSearchByTicketId_clicked();

    void on_btnFilterByCity_clicked();

    void on_btnFilterByStreet_clicked();

    void on_btnTrazi_clicked();

    void on_btnPreuzmiStranku_clicked();

    void on_btnPreuzmiTelefon_clicked();

    void on_btnFizickaOsoba_clicked();

    void on_btnPravnaOsoba_clicked();

private:
    Ui::FrmKontaktniCentarPretraga *ui;

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
        TraziPoHijerahija = 9
    };
    DonatSearchMode m_SearchMode;
    bool m_bSearchAktivneKupce;
    // Donat main customer info
    unsigned int m_iStrankaId;
    long long m_iKupacId;
    unsigned int m_iGrupaImovineId;
    string m_strTelefonskiBroj;
    string m_strTelefonskiBrojKlasa;


    void traziDonatKorisnikaPoNazivu();
    void traziDonatKorisnikaPoBrojuTelefona();
    void traziDonatKorisnikaPoJmbg();
    void traziDonatKorisnikaPoOib();
    void traziDonatKorisnikaPoUlogaStrankeId();
    void traziDonatKorisnikaPoTicketId();
    void traziDonatKorisnikaPoAssetId();

};

} // Kontakt

#endif // FRMKONTAKTNICENTARPRETRAGA_H
