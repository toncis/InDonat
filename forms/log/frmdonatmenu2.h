//
//  frmdonatmenu2.h
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


#ifndef FRMDONATMENU2_H
#define FRMDONATMENU2_H

#include <QMainWindow>
#include "wgdonatmenu1.h"
#include "wgdonatmenu2.h"
#include "wgdonatmenu3.h"
#include "wgdonatmenu4.h"
#include <QtWidgets>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QStatusBar;
class QVBoxLayout;
class QHBoxLayout;
class QWidget;
class QLabel;
class QFrame;
class QPushButton;
class QTableWidgetItem;
QT_END_NAMESPACE

namespace Log {

class FrmDonatMenu2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmDonatMenu2(QWidget *parent = 0);
    ~FrmDonatMenu2();

signals:

public slots:

private slots:
    void on_actionPromijenaZaporke_triggered();
    void on_actionAbout_triggered();
    void on_actionMojeRole_triggered();
    void on_cboFltSearchMode_currentIndexChanged(int index);
    void on_cboStrankaImovinaKlase_currentIndexChanged(int index);
    void on_actionDonatTrazi_clicked();
    void on_grdDonatStranke_itemPressed(QTableWidgetItem* itemDonatStranka);
    void on_treeStrankaGrupaImovine_itemPressed(QTreeWidgetItem * itemGrupaImovine, int column = 0);
    void on_treeStrankaImovina_itemPressed(QTreeWidgetItem * itemGrupaImovine, int column = 0);
    void on_btnStrankaPregledZahtjeva_clicked();
    void on_btnStrankaPregledUgovora_clicked();
    void on_btnStrankaUgovorneObveze_clicked();

    // [Dokumenti Donat menu]
    void on_actionDokumentiZahtjevMax23_clicked();
    void on_actionDokumentiCpeOprema_clicked();
    void on_actionPregledSporazumaDetaljno_clicked();
    // [Stranka Donat menu]
    void on_actionFizickaOsoba_clicked();
    void on_actionPravnaOsoba_clicked();
    void on_actionStrankaOcv_clicked();


private:
    // [Actions]
    // [Menu - File]
    QAction *m_actExit;
    // [Menu - Promjena zaporke]
    QAction *m_actPromijenaZaporke;
    // [Menu - Sifarnik]
    QAction *m_actTitula;
    QAction *m_actModemi;
    QAction *m_actKonAgenti;
    QAction *m_actKonTehnologija;
    QAction *m_actKonHelp;
    QAction *m_actKonZdrawko;
    QAction *m_actKonAnkete;
    QAction *m_actKonTht;
    QAction *m_actKonOstalo;
    // [Menu - Odrzavanje]
    QAction *m_actAzurirajRipote;
    QAction *m_actAvayaRegistracija;
    QAction *m_actMojeRole;
    // [Menu - O programu]
    QAction *m_actAbout;
    // [Trazi]
    QAction *m_actDonatTrazi;

    // [Menu]
    QMenu *m_mnuFile;
    QMenu *m_mnuPromijenaZaporke;
    QMenu *m_mnuSifarnik;
    QMenu *m_mnuOdrzavanje;
    QMenu *m_mnuAbout;

    // [Statusbar]
    QLabel *m_lblDonatDate;
    QLabel *m_lblDonatTime;
    QLabel *m_lblDonatDbInfo;
    QLabel *m_lblStatusbarMessage;

    // [0]
    QFrame *m_fraDonatMainFrame;
    QHBoxLayout *m_hboxDonatMainLayout;
    WgDonatMenu1 *m_wgDonatToolBar;
    QFrame *m_fraDonatMenu1;
    // [1]
    QVBoxLayout *m_vboxDonatMenuLayout;
    WgDonatMenu2 *m_wgDonatSearch;
    QFrame *m_fraDonatSearchResult;
    // [2]
    QHBoxLayout *m_hboxDonatSearchResultLayout;
    WgDonatMenu3 *m_wgDonatStranke;
    WgDonatMenu4 *m_wgDonatImovina;


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
    // Donat main customer info
    unsigned int m_iStrankaId;
    long long m_iKupacId;
    unsigned int m_iGrupaImovineId;
    unsigned int m_iGrupaImovineIsStatus;
    unsigned int m_iGrupaImovineIsTip;
    unsigned int m_iImovinaId;
    int m_iImovinaIdStatus;
    string m_strTelefonskiBroj;
    bool m_bPunoGrupaImovine;

//    long long m_iGrupaImovineKupacId;
//    string m_strGrupaImovineKupacFormatiraniNaziv;
//    long long m_iGrupaImovineRacunId;
//    long long m_iGrupaImovineInstalacijaId;
//    string m_strGrupaImovineInstalacijaFormatiraniNaziv;



    // [Member functions]
    void createFrmDonatActions();
    void createFrmDonatMenus();
    void createFrmDonatToolBars();
    void createFrmDonatStatusBar();

    void clearDonatSearchResults();
    void clearDonatStranka();

    // Customer search
    void traziDonatKorisnikaPoNazivu();
    void traziDonatKorisnikaPoBrojuTelefona();
    void traziDonatKorisnikaPoJmbg();
    void traziDonatKorisnikaPoOib();
    void traziDonatKorisnikaPoUlogaStrankeId();
    void traziDonatKorisnikaPoTicketId();
    void traziDonatKorisnikaPoAssetId();
    // Customer data
    void popuniStrankaUlogeStranaka();
    void popuniStrankaZastupnika();
    void popuniStrankaLoyalty();
    void popuniStrankaTarifniStatus();
    void popuniStrankaSveKlase();
    void popuniUlogeStrankeZaTelefon();

	void popuniStrankaAdslStatus();
	void popuniStrankaIptvStatus();
	void popuniStrankaPenali();
	void popuniStrankaPoruke();
	void popuniStrankaPoruku(string strPoruka);

	// [ Grupa imovine ]
	void popuniStrankaGrupeImovine();
	void popuniZaGrupuImovine();
	void popuniSveGrupeImovine();
	void popuniSveGrupeImovineIskljucene();
	void popuniGrupeImovine1(const string strGrupeImovine);
	// [ Imovina ]
	void popuniSveImovine();
	void popuniImovinaAtribute(QTreeWidgetItem *itemImovina);
	void popuniImovinaStatus();

	// General donat functions
	unsigned int vratiBasicAsset(const unsigned int iGrupaImovineId);
	unsigned int vratiAdslAsset(const unsigned int iGrupaImovineId);
	bool getIsGrupaImovineIdMAXadsl(const unsigned int iGrupaImovineId);
	string vratiPovezaniKupci(const unsigned int iKupacId);
	int vratiIndikatorZaprikazUgovorneObveze(const unsigned int iGrupaImovineId, string strTip = string());
	string vratiChurnPhoneRizik(const string strPhoneNumber);
	string vratiUlogeGrupeImovine(const unsigned int iGrupaImovineId);
};

}   // namespace log

#endif // FRMDONATMENU2_H
