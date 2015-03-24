/************************************* Module Header **************************************\
* Module Name:  frmpregledzahtjeva.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of DONAT main form
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

#ifndef FRMPREGLEDZAHTJEVA_H
#define FRMPREGLEDZAHTJEVA_H

#include <QMainWindow>
#include <QtWidgets>
#include "donat.h"
#include <QTableWidget>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QStatusBar;
class QVBoxLayout;
class QHBoxLayout;
class QWidget;
class QLabel;
class QFrame;
class QGridLayout;
class QPushButton;
class QTableWidgetItem;
QT_END_NAMESPACE


namespace Sporazumi {

class FrmPregledZahtjeva : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmPregledZahtjeva(int iTipDokumentaId, unsigned int iStrankaId, QWidget *parent = 0);
    ~FrmPregledZahtjeva();

signals:

public slots:

private slots:
    void on_cboKlase_currentIndexChanged(int);
    void on_grdZahtjevi_itemPressed(QTableWidgetItem *item);
    void on_btnZatvori_clicked();
    void on_btnDokumentTitleExpand_clicked();
    void on_btnAdminTitleExpand_clicked();
    void on_btnPrivatni_clicked();
    void on_btnKljucni_clicked();
    void on_btnPoslovni_clicked();
    void on_btnDanas_clicked();
    void on_btnOvajTjedan_clicked();
    void on_btnOvajMjesec_clicked();
    void on_btnSvi_clicked();
    void on_btnUtijeku_clicked();
    void on_btnRezerviran_clicked();
    void on_btnStorniran_clicked();
    void on_btnValidacija_clicked();
    void on_btnPojedinacno_clicked();
    void on_btnStorno_clicked();
    void on_btnStornoDonat_clicked();
    void on_btnNastavakRealizacije_clicked();
    void on_btnPretvoriU1Kunu_clicked();
    void on_btnSve_clicked();
    void on_btnNista_clicked();
    void on_btnSporazum_clicked();
    void on_btnImovina_clicked();
    void on_btnStanjaDonat_clicked();
    void on_btnStanjaWwms_clicked();
    void on_btnDetaljno_clicked();
    void on_btnProcesi_clicked();
    void on_btnDisKarta_clicked();
    void on_btnNapomena_clicked();
    void on_btnDatoteke_clicked();
    void on_btnSpis_clicked();
    void on_btnJop_clicked();
    void on_btnDodijeliJop_clicked();
    void on_btnOtpisZaduzenja_clicked();
    void on_btnUlaznePoruke_clicked();
    void on_btnPromijenaKpro_clicked();
    void on_btnDatumZahtjeva_clicked();

    void on_btnKanal_clicked();
    void on_btnbtnMojiDokumenti_clicked();
    void on_btnDokument_clicked();


private:
    // [0]
    QFrame *m_fraMainFrame;
    QFrame *m_fraFltFrame;
    QFrame *m_fraResultsFrame;

    // [ Create Form widgets ]
    // [0]
    void createFltFrame();
    void createResultFrame();

    // [1]
    QPushButton *m_btnPrivatni;
    QPushButton *m_btnKljucni;
    QPushButton *m_btnPoslovni;
    QDateTimeEdit *m_dtDatum;
    QPushButton *m_btnDanas;
    QPushButton *m_btnOvajTjedan;
    QPushButton *m_btnOvajMjesec;
    QPushButton *m_btnSvi;
    QPushButton *m_btnUtijeku;
    QPushButton *m_btnRezerviran;
    QPushButton *m_btnStorniran;
    QPushButton *m_btnValidacija;
    QPushButton *m_btnPojedinacno;
    QPushButton *m_btnStorno;
    QPushButton *m_btnStornoDonat;
    QPushButton *m_btnNastavakRealizacije;
    QPushButton *m_btnPretvoriU1Kunu;

    // [2]
    QComboBox *m_cboKlase;
    QLabel *m_lblMojeKlase;
    QLabel *m_lblMojiDokumenti;

    // [3]
    QTableWidget *m_grdZahtjevi;
    QFrame *m_fraZahtjevToolBox;
    QScrollArea *m_scrZahtjevToolBox;
    QPushButton *m_btnDokument;
    QPushButton *m_btnLista;
    QPushButton *m_btnZatvori;

    // [4]
    QPushButton *m_btnKanal;
    QPushButton *m_btnMojiDokumenti;
    QPushButton *m_btnSve;
    QPushButton *m_btnNista;
    QPushButton *m_btnSporazum;
    QPushButton *m_btnImovina;
    QPushButton *m_btnStanjaDonat;
    QPushButton *m_btnStanjaWwms;
    QPushButton *m_btnDetaljno;
    QPushButton *m_btnProcesi;
    QPushButton *m_btnDisKarta;
    QPushButton *m_btnNapomena;
    QPushButton *m_btnDatoteke;
    QPushButton *m_btnSpis;
    QPushButton *m_btnJop;
    QPushButton *m_btnDodijeliJop;
    QPushButton *m_btnOtpisZaduzenja;
    QPushButton *m_btnUlaznePoruke;
    QPushButton *m_btnPromijenaKpro;
    QPushButton *m_btnDatumZahtjeva;
    QPushButton *m_btnDokumentTitleExpand;
    QFrame *m_fraDokumentToolBox;
    QPushButton *m_btnAdminTitleExpand;
    QFrame *m_fraAdminToolBox;

    void createZahtjevToolBox();
    void createZahtjevToolBoxes();
    // [ All form constucts ]
    void createFormActions();
    void createFormMenus();
    void createFormToolBars();
    void createFormStatusBar();

    // [Private Class Members]
    unsigned int m_iStrankaId;
    long long m_iUlogaStrankeId;
    int m_iTipUlogaStrankeId;

    int m_iTipKanalaProdaje;
    string m_strKanalProdaje;
    int m_iFltLinijaProduktaId;

    int m_iTipDokumenta;

    unsigned int m_iSporazumId;

    // [Private Member Functions]
    void popuniSveKlase();
    void popuniKanalProdaje();
    void popuniZahtjeve();

};

}   // namespace sporazumi

#endif // FRMPREGLEDZAHTJEVA_H
