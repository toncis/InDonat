/************************************* Module Header **************************************\
* Module Name:  frmdonatpregled.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT pregled za sporazum form.
*
* For more information see the Books Online and documentation.
* *****************************************************************************************
* All rights reserved.
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
* OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
* FITNESS FOR A PARTICULAR PURPOSE.
* * *****************************************************************************************
* Release History :
*
* VERSION	DESCRIPTION
* 	1.0		Created by Tonci Svilicic
\******************************************************************************************/

#ifndef FRMDONATPREGLED_H
#define FRMDONATPREGLED_H

#include <QtWidgets>
#include <QDialog>
#include <QTreeWidget>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QFormLayout;
class QFrame;
class QPushButton;
class QHBoxLayout;
class QWidget;
class QTreeWidget;
QT_END_NAMESPACE


namespace Sporazumi {

class FrmDonatPregled : public QDialog
{
    Q_OBJECT
public:
    explicit FrmDonatPregled(unsigned int iSporazumId, QWidget *parent = 0);
    ~FrmDonatPregled();

private :

    QFrame *m_fraMain;
    QFrame *m_fraSporazumMain;
    QFrame *m_fraToolbar;
    QFrame *m_fraFlt;
    QFrame *m_fraZatvori;
    QFrame *m_fraSporazum;
    QFrame *m_fraSporazumTree;
    QFrame *m_fraSporazumData;

    QFrame *m_fraToolbarPregled;
    QFrame *m_fraToolbarWwms;
    QFrame *m_fraToolbarDokument;
    QFrame *m_fraToolbarIspis;
    QFrame *m_fraToolbarAdmin;

    // [Search]
    QLineEdit *m_txtFltUpit;
    QPushButton *m_btnTrazi;
    QPushButton *m_btnDokumentTrazi;
    QPushButton *m_btnTelefonTrazi;
    QPushButton *m_btnAssetTrazi;
    QPushButton *m_btnSporazumTrazi;
    QPushButton *m_btnTicketTrazi;
    QPushButton *m_btnKupacTrazi;

    // [Kupac]
    QLineEdit *m_txtKupacId;
    QLineEdit *m_txtKupacNaziv;
    QLineEdit *m_txtKupacAdresa;

    QTreeWidget *m_treeSporazumi;
    QTreeWidget *m_treeSporazumAtributi;

    // [Zahtjev]
    QLineEdit *m_txtKanalProdaje;
    QLineEdit *m_txtUnioKorisnikId;
    QLineEdit *m_txtProdaoKorisnikId;
    QLineEdit *m_txtBrojDokumenta;
    QLineEdit *m_txtDatumSporazuma;
    QLineEdit *m_txtSporazumId;
    QLineEdit *m_txtTicketId;
    // [Order]
    QLineEdit *m_txtStatus;
    QLineEdit *m_txtAktivnost;
    QLineEdit *m_txtOrderId;
    QLineEdit *m_txtPromijena;
    QLineEdit *m_txtTelefon;
    QLineEdit *m_txtAsset;
    QLineEdit *m_txtKlasa;
    QLineEdit *m_txtUgovor;
    QLineEdit *m_txtGeneva;
    QLineEdit *m_txtWwms;
    QLineEdit *m_txtWwmsNapomena;

    // [Toolbar]
    QPushButton *m_btnPregledSporazum;
    QPushButton *m_btnPregledImovina;
    QPushButton *m_btnPregledDetaljno;
    QPushButton *m_btnPregledProcesi;
    QPushButton *m_btnWwmsStatusDonat;
    QPushButton *m_btnWwmsStatusWeb;
    QPushButton *m_btnDokumentNapomena;
    QPushButton *m_btnDokumentDatoteke;
    QPushButton *m_btnDokumentSpis;
    QPushButton *m_btnDokumentJop;
    QPushButton *m_btnDokumentDodijeliJop;
    QPushButton *m_btnDokumentOtpisZaduzenja;
    QPushButton *m_btnDokumentStorno;
    QPushButton *m_btnDokumentPretvori1Kn;
    QPushButton *m_btnIspisDokumenta;
    QPushButton *m_btnAdminUlaznePoruke;
    QPushButton *m_btnAdminKanalProdaje;
    QPushButton *m_btnAdminDatumZahtjeva;
    QPushButton *m_btnAdminStorno;
    QPushButton *m_btnAdminNastavakRealizacije;

    QPushButton *m_btnZatvori;

    unsigned int m_iSporazumId;
    unsigned int m_iGrupaImovineId;
    int m_iTipSporazumaId;
    // Search mode
    enum DonatSearchMode
    {
        TraziPoBrojDokumenta = 1,
        TraziPoTelefonu = 2,
        TraziPoAssetId = 3,
        TraziPoSporazumId = 4,
        TraziPoTicketId = 5,
        TraziPoUlogaStrankeId = 6
    };
    DonatSearchMode m_SearchMode;

    // Filter parameters
    unsigned int m_fltSporazumId;
    unsigned int m_fltKupacId;
    unsigned int m_fltGrupaImovineId;
    string m_fltBrojDokumenta;
    string m_fltTelefonskiBroj;
    string m_fltTicketId;


    void createMainFrame();
    void createSporazumMainFrame();
    void createSearchFrame();
    void createSporazumFrame();
    void createSporazumTree();
    void createSporazumZahtjevFrame();
    void createSporazumOrderFrame();
    void createZatvoriFrame();
    void createToolbarFrame();
    void createToolbarPregledFrame();
    void createToolbarWwmsFrame();
    void createToolbarDokumentFrame();
    void createToolbarIspisFrame();
    void createToolbarAdminFrame();

    void createFormActions();

    void clearFormData();
    void clearSporazumData();
    void popuniZahtjeve();
    void popuniPregledZahtjeva(QTreeWidgetItem *itemTreeStavka);
    void popuniKupca(unsigned int iKupacId);
    void popuniAtribute(string strOrderId);


private slots:
//    void on_grdTicket_itemPressed(QTableWidgetItem* itemTicket);
    void on_btnZatvori_clicked();
    void on_btnTrazi_clicked();
    void on_btnDokumentTrazi_clicked();
    void on_btnTelefonTrazi_clicked();
    void on_btnAssetTrazi_clicked();
    void on_btnSporazumTrazi_clicked();
    void on_btnTicketTrazi_clicked();
    void on_btnKupacTrazi_clicked();

    void on_btnPregledSporazum_clicked();
    void on_btnPregledImovina_clicked();
    void on_btnPregledDetaljno_clicked();
    void on_btnPregledProcesi_clicked();
    void on_btnWwmsStatusDonat_clicked();
    void on_btnWwmsStatusWeb_clicked();
    void on_btnDokumentNapomena_clicked();
    void on_btnDokumentDatoteke_clicked();
    void on_btnDokumentSpis_clicked();
    void on_btnDokumentJop_clicked();
    void on_btnDokumentDodijeliJop_clicked();
    void on_btnDokumentOtpisZaduzenja_clicked();
    void on_btnDokumentStorno_clicked();
    void on_btnDokumentPretvori1Kn_clicked();
    void on_btnIspisDokumenta_clicked();
    void on_btnAdminUlaznePoruke_clicked();
    void on_btnAdminKanalProdaje_clicked();
    void on_btnAdminDatumZahtjeva_clicked();
    void on_btnAdminStorno_clicked();
    void on_btnAdminNastavakRealizacije_clicked();

    void on_treeSporazumi_itemPressed(QTreeWidgetItem*, int);

signals:

public slots:

};

}   // namespace sporazumi

#endif // FRMDONATPREGLED_H
