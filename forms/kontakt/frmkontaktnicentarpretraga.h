//
//  frmkontaktnicentarpretraga.h
//
//  Author:
//       Tonči Sviličić <tonci.svilicic@in2.hr>
//
//  Copyright (c) 2012 Tonči Sviličić
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
