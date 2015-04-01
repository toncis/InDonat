//
//  frmdonatpregled.cpp
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


#include "frmdonatpregled.h"
#include "frmstavkesporazuma.h"
#include "frmpregledprocesa.h"
#include "frmwwmspregled.h"
#include "frmpregledsporazuma.h"
#include "frmpregledimovine.h"

#include "itos.h"
#include "ocinumber.h"

namespace Sporazumi {

FrmDonatPregled::FrmDonatPregled(unsigned int iSporazumId, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // [0]
    QFrame *fraKupacTitile = new QFrame();
    fraKupacTitile->setContentsMargins(0, 0, 0, 0);
    fraKupacTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    QSizePolicy fraKupacTitileSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraKupacTitileSizePolicy.setHorizontalStretch(0);
    fraKupacTitileSizePolicy.setVerticalStretch(0);
    fraKupacTitile->setSizePolicy(fraKupacTitileSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(2, 2, 0, 2);
    hboxLayout1->setSpacing(1);
    QLabel *lblTicketTitle = new QLabel(tr("KUPAC"));
//    lblTicketTitle->setContentsMargins(0, 2, 0, 2);
    hboxLayout1->addWidget(lblTicketTitle);
    fraKupacTitile->setLayout(hboxLayout1);
    mainLayout->addWidget(fraKupacTitile);
    // [1]
    createMainFrame();
    mainLayout->addWidget(m_fraMain);
    setLayout(mainLayout);

    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT - Pregled statusa"));
//    setMinimumWidth(886);
//    setMinimumHeight(556);

    createFormActions();

    m_iSporazumId = iSporazumId;

    m_fltSporazumId = iSporazumId;
    m_fltKupacId = 0;
    m_fltGrupaImovineId = 0;

    m_SearchMode = TraziPoSporazumId;

    popuniZahtjeve();
}
// [ Create Form ]
void FrmDonatPregled::createMainFrame()
{
    m_fraMain = new QFrame();
    m_fraMain->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *hboxMainFrameLayout = new QHBoxLayout();
    hboxMainFrameLayout->setContentsMargins(0, 0, 0, 0);
    hboxMainFrameLayout->setSpacing(0);

    createSporazumMainFrame();
    hboxMainFrameLayout->addWidget(m_fraSporazumMain);

    createToolbarFrame();
    hboxMainFrameLayout->addWidget(m_fraToolbar);
    m_fraMain->setLayout(hboxMainFrameLayout);
}
void FrmDonatPregled::createSporazumMainFrame()
{
    m_fraSporazumMain = new QFrame();
    m_fraSporazumMain->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vbox1Layout = new QVBoxLayout();
    vbox1Layout->setContentsMargins(0, 0, 0, 0);
    vbox1Layout->setSpacing(0);
    // [0]
    createSearchFrame();
    vbox1Layout->addWidget(m_fraFlt);
    // [1]
    createSporazumFrame();
    vbox1Layout->addWidget(m_fraSporazum);
    // [2]
    createZatvoriFrame();
    vbox1Layout->addWidget(m_fraZatvori);
    m_fraSporazumMain->setLayout(vbox1Layout);
}
void FrmDonatPregled::createSearchFrame()
{
    m_fraFlt = new QFrame();
    m_fraFlt->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vbox2Layout = new QVBoxLayout();
    vbox2Layout->setContentsMargins(0, 0, 0, 0);
    vbox2Layout->setSpacing(0);
    // [0]
    QFrame *fraFltButton = new QFrame();
    fraFltButton->setContentsMargins(0, 0, 0, 0);
    QSizePolicy fraFltButtonSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraFltButtonSizePolicy.setHorizontalStretch(0);
    fraFltButtonSizePolicy.setVerticalStretch(0);
    fraFltButton->setSizePolicy(fraFltButtonSizePolicy);
    QHBoxLayout *hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setContentsMargins(2, 0, 2, 0);
    hboxLayout3->setSpacing(1);
    // [0]
    QLabel *lblUpitTitle = new QLabel(tr("UPIT"));
    lblUpitTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblUpitTitle->setMinimumWidth(80);
    lblUpitTitle->setMaximumWidth(80);
    hboxLayout3->addWidget(lblUpitTitle);
    // [1]
    m_txtFltUpit = new QLineEdit();
//    m_txtFltUpit->setMaxLength(80);
    m_txtFltUpit->setMinimumWidth(80);
//    m_txtFltUpit->setMaximumWidth(140);
//    m_txtFltUpit->setReadOnly(true);
    hboxLayout3->addWidget(m_txtFltUpit);
    // [2]
    m_btnTrazi = new QPushButton(tr("OK"));
    //    m_btnTrazi->setFlat(true);
    m_btnTrazi->setCursor(Qt::PointingHandCursor);
    m_btnTrazi->setMinimumWidth(40);
    m_btnTrazi->setMaximumWidth(40);
    QSizePolicy m_btnTraziSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    m_btnTraziSizePolicy.setHorizontalStretch(0);
    m_btnTraziSizePolicy.setVerticalStretch(0);
    m_btnTrazi->setSizePolicy(m_btnTraziSizePolicy);
    hboxLayout3->addWidget(m_btnTrazi);
    // [3]
    m_btnDokumentTrazi = new QPushButton(tr("DOKUMENT"));
    m_btnDokumentTrazi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/document_text.ico")));
    m_btnDokumentTrazi->setCursor(Qt::PointingHandCursor);
    hboxLayout3->addWidget(m_btnDokumentTrazi);
    // [4]
    m_btnTelefonTrazi = new QPushButton(tr("TELEFON"));
    m_btnTelefonTrazi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/telephone.gif")));
    m_btnTelefonTrazi->setCursor(Qt::PointingHandCursor);
    hboxLayout3->addWidget(m_btnTelefonTrazi);
    // [5]
    m_btnAssetTrazi = new QPushButton(tr("ASSET"));
    m_btnAssetTrazi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/tServer.gif")));
    m_btnAssetTrazi->setCursor(Qt::PointingHandCursor);
    hboxLayout3->addWidget(m_btnAssetTrazi);
    // [6]
    m_btnSporazumTrazi = new QPushButton(tr("SPORAZUM"));
    m_btnSporazumTrazi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/document_text.ico")));
    m_btnSporazumTrazi->setCursor(Qt::PointingHandCursor);
    hboxLayout3->addWidget(m_btnSporazumTrazi);
    // [7]
    m_btnTicketTrazi = new QPushButton(tr("TICKET"));
    m_btnTicketTrazi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/tServer.gif")));
    m_btnTicketTrazi->setCursor(Qt::PointingHandCursor);
    hboxLayout3->addWidget(m_btnTicketTrazi);
    // [8]
    m_btnKupacTrazi = new QPushButton(tr("KUPAC ID"));
    m_btnKupacTrazi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ULOGA_ID_16x16.png")));
    m_btnKupacTrazi->setCursor(Qt::PointingHandCursor);
    hboxLayout3->addWidget(m_btnKupacTrazi);

    fraFltButton->setLayout(hboxLayout3);
    vbox2Layout->addWidget(fraFltButton);
    // [1]
    QFrame *fraLine1 = new QFrame();
    fraLine1->setContentsMargins(2, 1, 2, 1);
    QSizePolicy fraHline1SizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraHline1SizePolicy.setHorizontalStretch(0);
    fraHline1SizePolicy.setVerticalStretch(0);
    fraLine1->setSizePolicy(fraHline1SizePolicy);
    fraLine1->setFrameShape(QFrame::Panel);
    fraLine1->setFrameShadow(QFrame::Raised);
    fraLine1->setMinimumHeight(8);
    vbox2Layout->addWidget(fraLine1);
    // [2]
    QFrame *fraKupacNaziv = new QFrame();
    fraKupacNaziv->setContentsMargins(0, 0, 0, 0);
    QSizePolicy fraKupacNazivSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraKupacNazivSizePolicy.setHorizontalStretch(0);
    fraKupacNazivSizePolicy.setVerticalStretch(0);
    fraKupacNaziv->setSizePolicy(fraKupacNazivSizePolicy);
    QHBoxLayout *hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setContentsMargins(2, 0, 2, 0);
    hboxLayout4->setSpacing(1);
    // [0]
    QLabel *lblKupacIdTitle = new QLabel(tr("KUPAC"));
    lblKupacIdTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblKupacIdTitle->setMinimumWidth(80);
    lblKupacIdTitle->setMaximumWidth(80);
    hboxLayout4->addWidget(lblKupacIdTitle);
    // [1]
    m_txtKupacId = new QLineEdit();
    m_txtKupacId->setMaxLength(120);
    m_txtKupacId->setMaximumWidth(120);
    m_txtKupacId->setReadOnly(true);
    hboxLayout4->addWidget(m_txtKupacId);
    // [2]
    m_txtKupacNaziv = new QLineEdit();
    m_txtKupacNaziv->setReadOnly(true);
    QSizePolicy txtKupacNazivSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    txtKupacNazivSizePolicy.setHorizontalStretch(0);
    txtKupacNazivSizePolicy.setVerticalStretch(0);
    m_txtKupacNaziv->setSizePolicy(txtKupacNazivSizePolicy);
    hboxLayout4->addWidget(m_txtKupacNaziv);

    fraKupacNaziv->setLayout(hboxLayout4);
    vbox2Layout->addWidget(fraKupacNaziv);
    // [3]
    QFrame *fraKupacAdresa = new QFrame();
    fraKupacAdresa->setContentsMargins(0, 0, 0, 0);
    QSizePolicy fraKupacAdresaSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraKupacAdresaSizePolicy.setHorizontalStretch(0);
    fraKupacAdresaSizePolicy.setVerticalStretch(0);
    fraKupacAdresa->setSizePolicy(fraKupacAdresaSizePolicy);
    QHBoxLayout *hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setContentsMargins(2, 0, 2, 0);
    hboxLayout5->setSpacing(1);
    // [0]
    QLabel *lblKupacAdresaTitle = new QLabel(tr("ADRESA"));
    lblKupacAdresaTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblKupacAdresaTitle->setMinimumWidth(80);
    lblKupacAdresaTitle->setMaximumWidth(80);
    hboxLayout5->addWidget(lblKupacAdresaTitle);
    // [2]
    m_txtKupacAdresa = new QLineEdit();
    m_txtKupacAdresa->setReadOnly(true);
    QSizePolicy txtKupacAdresaSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    txtKupacAdresaSizePolicy.setHorizontalStretch(0);
    txtKupacAdresaSizePolicy.setVerticalStretch(0);
    m_txtKupacAdresa->setSizePolicy(txtKupacAdresaSizePolicy);
    hboxLayout5->addWidget(m_txtKupacAdresa);

    fraKupacAdresa->setLayout(hboxLayout5);
    vbox2Layout->addWidget(fraKupacAdresa);

    m_fraFlt->setLayout(vbox2Layout);
}
void FrmDonatPregled::createSporazumFrame()
{
    m_fraSporazum  = new QFrame();
    m_fraSporazum->setContentsMargins(0, 0, 0, 0);
    QSizePolicy fraSporazumSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraSporazumSizePolicy.setHorizontalStretch(0);
    fraSporazumSizePolicy.setVerticalStretch(0);
    m_fraSporazum->setSizePolicy(fraSporazumSizePolicy);

    QHBoxLayout *hbox1Layout = new QHBoxLayout();
    hbox1Layout->setContentsMargins(0, 0, 0, 0);
    hbox1Layout->setSpacing(0);
    // [0]
    m_fraSporazumTree = new QFrame();
    m_fraSporazumTree->setContentsMargins(0, 0, 0, 0);
    createSporazumTree();
    hbox1Layout->addWidget(m_fraSporazumTree);
    // [1]
    m_fraSporazumData = new QFrame();
    m_fraSporazumData->setContentsMargins(0, 0, 0, 0);
    createSporazumZahtjevFrame();
    hbox1Layout->addWidget(m_fraSporazumData);

    m_fraSporazum->setLayout(hbox1Layout);
}
void FrmDonatPregled::createSporazumTree()
{
    QVBoxLayout *vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setContentsMargins(2, 2, 2, 2);
    vboxLayout2->setSpacing(2);
    // [0]
    QLabel *lblListaZahtjevaTitle = new QLabel(tr("LISTA ZAHTJEV"));
    lblListaZahtjevaTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
//    lblListaZahtjevaTitle->setMinimumHeight(m_txtFltUpit->frameSize().height());
    vboxLayout2->addWidget(lblListaZahtjevaTitle);
    // [1]
    m_treeSporazumi = new QTreeWidget();
    m_treeSporazumi->setContentsMargins(4, 4, 0, 0);
    m_treeSporazumi->setFrameShape(QFrame::StyledPanel);
//    m_treeSporazumi->setMinimumWidth(600);
    // Create headers
    QStringList labels1;
    labels1 << "ZAVRŠENOST_IMG" << "AKTIVNOST_IMG" << "NAZIV"
     << "SPORAZUM_ID" << "BROJ_DOK" << "KUPAC_ID" << "GIMOVINE_ID" << "TEL_BROJ" << "KLASA" << "STATUS_PROVISIONING"
     << "STATUS_UGOVARANJE" << "STATUS_BILLING" << "ORDER_ID" << "TICKET_ID" << "DATUM_ZAHTJEVA" << "DATUM_ZADNJE_PROMJENE"
     << "OPERATER" << "PRODAVAC" << "KANAL" << "NAPOMENA_PROVISIONING" << "AKTIVNOST" << "ZAVRSENOST" << "ID"
     << "STATUS_KOMUNIKACIJA_KORISNIKU";
    m_treeSporazumi->setColumnCount(24);
    m_treeSporazumi->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_treeSporazumi->setColumnWidth(0, 60);
    m_treeSporazumi->setColumnWidth(1, 18);
    m_treeSporazumi->hideColumn(3);
    m_treeSporazumi->hideColumn(4);
    m_treeSporazumi->hideColumn(5);
    m_treeSporazumi->hideColumn(6);
    m_treeSporazumi->hideColumn(7);
    m_treeSporazumi->hideColumn(8);
    m_treeSporazumi->hideColumn(9);
    m_treeSporazumi->hideColumn(10);
    m_treeSporazumi->hideColumn(11);
    m_treeSporazumi->hideColumn(12);
    m_treeSporazumi->hideColumn(13);
    m_treeSporazumi->hideColumn(14);
    m_treeSporazumi->hideColumn(15);
    m_treeSporazumi->hideColumn(16);
    m_treeSporazumi->hideColumn(17);
    m_treeSporazumi->hideColumn(18);
    m_treeSporazumi->hideColumn(19);
    m_treeSporazumi->hideColumn(20);
    m_treeSporazumi->hideColumn(21);
    m_treeSporazumi->hideColumn(22);
    m_treeSporazumi->hideColumn(23);
    m_treeSporazumi->setHeaderHidden(true);
    m_treeSporazumi->setAlternatingRowColors(false);
    m_treeSporazumi->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeSporazumi->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_treeSporazumi->setItemsExpandable(true); //QTreeWidgetItem::DontShowIndicatorWhenChildless
    m_treeSporazumi->setRootIsDecorated(true);
    vboxLayout2->addWidget(m_treeSporazumi);
    // [2]
    QLabel *lblAtributiTitle = new QLabel(tr("ATRIBUTI"));
    lblAtributiTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
//    lblAtributiTitle->setMinimumHeight(m_txtFltUpit->frameSize().height());
    vboxLayout2->addWidget(lblAtributiTitle);
    // [3]
    m_treeSporazumAtributi = new QTreeWidget();
    m_treeSporazumAtributi->setContentsMargins(4, 4, 0, 0);
    m_treeSporazumAtributi->setFrameShape(QFrame::StyledPanel);
//    m_treeSporazumAtributi->setMinimumWidth(600);
    // Create headers
    QStringList labels2;
    labels2 << "ATRIBUT";
    m_treeSporazumAtributi->setColumnCount(1);
    m_treeSporazumAtributi->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    m_treeSporazumAtributi->setColumnWidth(0, 1);
    m_treeSporazumAtributi->setHeaderHidden(true);
    m_treeSporazumAtributi->setAlternatingRowColors(false);
    m_treeSporazumAtributi->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeSporazumAtributi->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_treeSporazumAtributi->setItemsExpandable(true); //QTreeWidgetItem::DontShowIndicatorWhenChildless
    m_treeSporazumAtributi->setRootIsDecorated(true);
    vboxLayout2->addWidget(m_treeSporazumAtributi);

    m_fraSporazumTree->setLayout(vboxLayout2);
}
void FrmDonatPregled::createSporazumZahtjevFrame()
{
    QVBoxLayout *vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setContentsMargins(2, 0, 2, 0);
    vboxLayout3->setSpacing(1);
    // [0]
    QFrame *fraSporazumZahtjevTitle = new QFrame();
    fraSporazumZahtjevTitle->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    hboxLayout1->setSpacing(0);
    QLabel *lblZahtjevTitle = new QLabel(tr("ZAHTJEV"));
    lblZahtjevTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
//    lblZahtjevTitle->setMinimumHeight(m_txtFltUpit->frameSize().height());
    hboxLayout1->addWidget(lblZahtjevTitle);
    fraSporazumZahtjevTitle->setLayout(hboxLayout1);
    vboxLayout3->addWidget(fraSporazumZahtjevTitle);
    // [1]
    QFrame *fraKanal  = new QFrame();
    fraKanal->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setContentsMargins(0, 0, 0, 0);
    hboxLayout2->setSpacing(0);
    QLabel *lblKanalTitle = new QLabel(tr("KANAL"));
    lblKanalTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblKanalTitle->setMinimumWidth(90);
    lblKanalTitle->setMaximumWidth(90);
    hboxLayout2->addWidget(lblKanalTitle);
    m_txtKanalProdaje = new QLineEdit();
    m_txtKanalProdaje->setReadOnly(true);
    hboxLayout2->addWidget(m_txtKanalProdaje);
    fraKanal->setLayout(hboxLayout2);
    vboxLayout3->addWidget(fraKanal);
    // [2]
    QFrame *fraKorisnik  = new QFrame();
    fraKorisnik->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setContentsMargins(0, 0, 0, 0);
    hboxLayout3->setSpacing(0);
    QLabel *lblUnioTitile = new QLabel(tr("UNIO"));
    lblUnioTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblUnioTitile->setMinimumWidth(90);
    lblUnioTitile->setMaximumWidth(90);
    hboxLayout3->addWidget(lblUnioTitile);
    m_txtUnioKorisnikId = new QLineEdit();
    m_txtUnioKorisnikId->setReadOnly(true);
    hboxLayout3->addWidget(m_txtUnioKorisnikId);
    QLabel *lblProdaoTitile = new QLabel(tr("PRODAO"));
    lblProdaoTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblProdaoTitile->setMinimumWidth(90);
    lblProdaoTitile->setMaximumWidth(90);
    hboxLayout3->addWidget(lblProdaoTitile);
    m_txtProdaoKorisnikId = new QLineEdit();
    m_txtProdaoKorisnikId->setReadOnly(true);
    hboxLayout3->addWidget(m_txtProdaoKorisnikId);
    fraKorisnik->setLayout(hboxLayout3);
    vboxLayout3->addWidget(fraKorisnik);
    // [3]
    QFrame *fraDokument  = new QFrame();
    fraDokument->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setContentsMargins(0, 0, 0, 0);
    hboxLayout4->setSpacing(0);
    QLabel *lblDokumentTitile = new QLabel(tr("DOKUMENT"));
    lblDokumentTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblDokumentTitile->setMinimumWidth(90);
    lblDokumentTitile->setMaximumWidth(90);
    hboxLayout4->addWidget(lblDokumentTitile);
    m_txtBrojDokumenta = new QLineEdit();
    m_txtBrojDokumenta->setReadOnly(true);
    hboxLayout4->addWidget(m_txtBrojDokumenta);
    QLabel *lblDatumTitile = new QLabel(tr("DATUM"));
    lblDatumTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblDatumTitile->setMinimumWidth(90);
    lblDatumTitile->setMaximumWidth(90);
    hboxLayout4->addWidget(lblDatumTitile);
    m_txtDatumSporazuma = new QLineEdit();
    m_txtDatumSporazuma->setReadOnly(true);
    hboxLayout4->addWidget(m_txtDatumSporazuma);
    fraDokument->setLayout(hboxLayout4);
    vboxLayout3->addWidget(fraDokument);
    // [4]
    QFrame *fraSporazum  = new QFrame();
    fraSporazum->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setContentsMargins(0, 0, 0, 0);
    hboxLayout5->setSpacing(0);
    QLabel *lblSporazumTitile = new QLabel(tr("SPORAZUM"));
    lblSporazumTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblSporazumTitile->setMinimumWidth(90);
    lblSporazumTitile->setMaximumWidth(90);
    hboxLayout5->addWidget(lblSporazumTitile);
    m_txtSporazumId = new QLineEdit();
    m_txtSporazumId->setReadOnly(true);
    hboxLayout5->addWidget(m_txtSporazumId);
    QLabel *lblTicketTitile = new QLabel(tr("TICKET"));
    lblTicketTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblTicketTitile->setMinimumWidth(90);
    lblTicketTitile->setMaximumWidth(90);
    hboxLayout5->addWidget(lblTicketTitile);
    m_txtTicketId = new QLineEdit();
    m_txtTicketId->setReadOnly(true);
    hboxLayout5->addWidget(m_txtTicketId);
    fraSporazum->setLayout(hboxLayout5);
    vboxLayout3->addWidget(fraSporazum);
    // [5]
    QFrame *fraOrderTitle  = new QFrame();
    fraOrderTitle->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setContentsMargins(0, 0, 0, 0);
    hboxLayout6->setSpacing(0);
    QLabel *lblOrderTitle = new QLabel(tr("ORDER"));
    lblOrderTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
//    lblOrderTitle->setMinimumHeight(m_txtFltUpit->frameSize().height());
    hboxLayout6->addWidget(lblOrderTitle);
    fraOrderTitle->setLayout(hboxLayout6);
    vboxLayout3->addWidget(fraOrderTitle);
    // [6]
    QFrame *fraStatus  = new QFrame();
    fraStatus->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setContentsMargins(0, 0, 0, 0);
    hboxLayout7->setSpacing(0);
    QLabel *lblStatusTitile = new QLabel(tr("STATUS"));
    lblStatusTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblStatusTitile->setMinimumWidth(90);
    lblStatusTitile->setMaximumWidth(90);
    hboxLayout7->addWidget(lblStatusTitile);
    m_txtStatus = new QLineEdit();
    m_txtStatus->setReadOnly(true);
    hboxLayout7->addWidget(m_txtStatus);
    QLabel *lblAktivnostTitile = new QLabel(tr("AKTIVNOST"));
    lblAktivnostTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblAktivnostTitile->setMinimumWidth(90);
    lblAktivnostTitile->setMaximumWidth(90);
    hboxLayout7->addWidget(lblAktivnostTitile);
    m_txtAktivnost = new QLineEdit();
    m_txtAktivnost->setReadOnly(true);
    hboxLayout7->addWidget(m_txtAktivnost);
    fraStatus->setLayout(hboxLayout7);
    vboxLayout3->addWidget(fraStatus);
    // [7]
    QFrame *fraOrderId  = new QFrame();
    fraOrderId->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setContentsMargins(0, 0, 0, 0);
    hboxLayout8->setSpacing(0);
    QLabel *lblOrderIdTitile = new QLabel(tr("ORDER ID"));
    lblOrderIdTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblOrderIdTitile->setMinimumWidth(90);
    lblOrderIdTitile->setMaximumWidth(90);
    hboxLayout8->addWidget(lblOrderIdTitile);
    m_txtOrderId = new QLineEdit();
    m_txtOrderId->setReadOnly(true);
    hboxLayout8->addWidget(m_txtOrderId);
    QLabel *lblPromjenaTitile = new QLabel(tr("PROMJENA"));
    lblPromjenaTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblPromjenaTitile->setMinimumWidth(90);
    lblPromjenaTitile->setMaximumWidth(90);
    hboxLayout8->addWidget(lblPromjenaTitile);
    m_txtPromijena = new QLineEdit();
    m_txtPromijena->setReadOnly(true);
    hboxLayout8->addWidget(m_txtPromijena);
    fraOrderId->setLayout(hboxLayout8);
    vboxLayout3->addWidget(fraOrderId);
    // [8]
    QFrame *fraTelefon  = new QFrame();
    fraTelefon->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout9 = new QHBoxLayout();
    hboxLayout9->setContentsMargins(0, 0, 0, 0);
    hboxLayout9->setSpacing(0);
    QLabel *lblTelefonTitile = new QLabel(tr("TELEFON"));
    lblTelefonTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblTelefonTitile->setMinimumWidth(90);
    lblTelefonTitile->setMaximumWidth(90);
    hboxLayout9->addWidget(lblTelefonTitile);
    m_txtTelefon = new QLineEdit();
    m_txtTelefon->setReadOnly(true);
    hboxLayout9->addWidget(m_txtTelefon);
    QLabel *lblAssetTitile = new QLabel(tr("ASSET"));
    lblAssetTitile->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblAssetTitile->setMinimumWidth(90);
    hboxLayout9->addWidget(lblAssetTitile);
    m_txtAsset = new QLineEdit();
    m_txtAsset->setReadOnly(true);
    hboxLayout9->addWidget(m_txtAsset);
    fraTelefon->setLayout(hboxLayout9);
    vboxLayout3->addWidget(fraTelefon);
    // [9]
    QFrame *fraKlasa  = new QFrame();
    fraKlasa->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout10 = new QHBoxLayout();
    hboxLayout10->setContentsMargins(0, 0, 0, 0);
    hboxLayout10->setSpacing(0);
    QLabel *lblKlasaTitle = new QLabel(tr("KLASA"));
    lblKlasaTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblKlasaTitle->setMinimumWidth(90);
    lblKlasaTitle->setMaximumWidth(90);
    hboxLayout10->addWidget(lblKlasaTitle);
    m_txtKlasa = new QLineEdit();
    m_txtKlasa->setReadOnly(true);
    hboxLayout10->addWidget(m_txtKlasa);
    fraKlasa->setLayout(hboxLayout10);
    vboxLayout3->addWidget(fraKlasa);
    // [10]
    QFrame *fraUgovor  = new QFrame();
    fraUgovor->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout11 = new QHBoxLayout();
    hboxLayout11->setContentsMargins(0, 0, 0, 0);
    hboxLayout11->setSpacing(0);
    QLabel *lblUgovorTitle = new QLabel(tr("UGOVOR"));
    lblUgovorTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblUgovorTitle->setMinimumWidth(90);
    lblUgovorTitle->setMaximumWidth(90);
    hboxLayout11->addWidget(lblUgovorTitle);
    m_txtUgovor = new QLineEdit();
    m_txtUgovor->setReadOnly(true);
    hboxLayout11->addWidget(m_txtUgovor);
    fraUgovor->setLayout(hboxLayout11);
    vboxLayout3->addWidget(fraUgovor);
    // [11]
    QFrame *fraGeneva  = new QFrame();
    fraGeneva->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout12 = new QHBoxLayout();
    hboxLayout12->setContentsMargins(0, 0, 0, 0);
    hboxLayout12->setSpacing(0);
    QLabel *lblGenevaTitle = new QLabel(tr("GENEVA"));
    lblGenevaTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblGenevaTitle->setMinimumWidth(90);
    lblGenevaTitle->setMaximumWidth(90);
    hboxLayout12->addWidget(lblGenevaTitle);
    m_txtGeneva = new QLineEdit();
    m_txtGeneva->setMinimumHeight(40);
    m_txtGeneva->setReadOnly(true);
    hboxLayout12->addWidget(m_txtGeneva);
    fraGeneva->setLayout(hboxLayout12);
    vboxLayout3->addWidget(fraGeneva);
    // [12]
    QFrame *fraWwms  = new QFrame();
    fraWwms->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout13 = new QHBoxLayout();
    hboxLayout13->setContentsMargins(0, 0, 0, 0);
    hboxLayout13->setSpacing(0);
    QLabel *lblWwmsTitle = new QLabel(tr("WWMS"));
    lblWwmsTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblWwmsTitle->setMinimumWidth(90);
    lblWwmsTitle->setMaximumWidth(90);
    hboxLayout13->addWidget(lblWwmsTitle);
    m_txtWwms = new QLineEdit();
    m_txtWwms->setMinimumHeight(80);
    m_txtWwms->setReadOnly(true);
    hboxLayout13->addWidget(m_txtWwms);
    fraWwms->setLayout(hboxLayout13);
    vboxLayout3->addWidget(fraWwms);
    // [17]
    QFrame *fraWwmsNapomena  = new QFrame();
    fraWwmsNapomena->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxLayout14 = new QHBoxLayout();
    hboxLayout14->setContentsMargins(0, 0, 0, 0);
    hboxLayout14->setSpacing(0);
    QLabel *lblWwmsNapomenaTitle = new QLabel(tr("WWMS \nNAPOMENA"));
    lblWwmsNapomenaTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    lblWwmsNapomenaTitle->setMinimumWidth(90);
    lblWwmsNapomenaTitle->setMaximumWidth(90);
    hboxLayout14->addWidget(lblWwmsNapomenaTitle);
    m_txtWwmsNapomena = new QLineEdit();
    m_txtWwmsNapomena->setMinimumHeight(80);
    m_txtWwmsNapomena->setReadOnly(true);
    QSizePolicy txtWwmsNapomenaSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    txtWwmsNapomenaSizePolicy.setHorizontalStretch(0);
    txtWwmsNapomenaSizePolicy.setVerticalStretch(0);
    m_txtWwmsNapomena->setSizePolicy(txtWwmsNapomenaSizePolicy);
    hboxLayout14->addWidget(m_txtWwmsNapomena);
    fraWwmsNapomena->setLayout(hboxLayout14);
    vboxLayout3->addWidget(fraWwmsNapomena);

    m_fraSporazumData->setLayout(vboxLayout3);
}
void FrmDonatPregled::createZatvoriFrame()
{
    m_fraZatvori = new QFrame();
    m_fraZatvori->setContentsMargins(0, 0, 0, 0);
    QSizePolicy fraZatvoriSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraZatvoriSizePolicy.setHorizontalStretch(0);
    fraZatvoriSizePolicy.setVerticalStretch(0);
    m_fraZatvori->setSizePolicy(fraZatvoriSizePolicy);

    QHBoxLayout *hbox2Layout = new QHBoxLayout();
    hbox2Layout->setContentsMargins(0, 0, 0, 0);
    hbox2Layout->setSpacing(0);
    hbox2Layout->setAlignment(Qt::AlignRight);

    QLabel *lblEmpty1 = new QLabel(tr(""));
    lblEmpty1->setFrameStyle(QFrame::Panel | QFrame::Raised);
    QSizePolicy lblEmpty1SizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    lblEmpty1SizePolicy.setHorizontalStretch(0);
    lblEmpty1SizePolicy.setVerticalStretch(0);
    lblEmpty1->setSizePolicy(lblEmpty1SizePolicy);
    hbox2Layout->addWidget(lblEmpty1);

    m_btnZatvori = new QPushButton(tr("ZATVORI"));
    m_btnZatvori->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
    m_btnZatvori->setCursor(Qt::PointingHandCursor);
    hbox2Layout->addWidget(m_btnZatvori);


    m_fraZatvori->setLayout(hbox2Layout);
}
void FrmDonatPregled::createToolbarFrame()
{
    m_fraToolbar = new QFrame();
    m_fraToolbar->setContentsMargins(0, 0, 0, 0);
    QSizePolicy fraToolbarSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    fraToolbarSizePolicy.setHorizontalStretch(0);
    fraToolbarSizePolicy.setVerticalStretch(0);
    m_fraToolbar->setSizePolicy(fraToolbarSizePolicy);

    QVBoxLayout *vbox1Layout = new QVBoxLayout();
    vbox1Layout->setContentsMargins(0, 0, 0, 0);
    vbox1Layout->setSpacing(0);
    // [0]
    createToolbarPregledFrame();
    vbox1Layout->addWidget(m_fraToolbarPregled);
    // [1]
    createToolbarWwmsFrame();
    vbox1Layout->addWidget(m_fraToolbarWwms);
    // [2]
    createToolbarDokumentFrame();
    vbox1Layout->addWidget(m_fraToolbarDokument);
    // [3]
    createToolbarIspisFrame();
    vbox1Layout->addWidget(m_fraToolbarIspis);
    // [4]
    createToolbarAdminFrame();
    vbox1Layout->addWidget(m_fraToolbarAdmin);

    m_fraToolbar->setLayout(vbox1Layout);
}
void FrmDonatPregled::createToolbarPregledFrame()
{
    m_fraToolbarPregled = new QFrame();
    m_fraToolbarPregled->setContentsMargins(0, 0, 0, 0);
    m_fraToolbarPregled->setFrameShape(QFrame::StyledPanel);
//    QSizePolicy fraPregledToolBoxSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//    fraPregledToolBoxSizePolicy.setHorizontalStretch(0);
//    fraPregledToolBoxSizePolicy.setVerticalStretch(0);
//    fraPregledToolBox->setSizePolicy(fraPregledToolBoxSizePolicy);
    QVBoxLayout *vboxLayout5 = new QVBoxLayout();
    vboxLayout5->setContentsMargins(0, 1, 0, 1);
    vboxLayout5->setSpacing(1);
    // [1]
    QFrame *fraPregledTitle = new QFrame();
    fraPregledTitle->setContentsMargins(0, 0, 0, 0);
    fraPregledTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraIspisTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraIspisTitleSizePolicy.setHorizontalStretch(0);
    fraIspisTitleSizePolicy.setVerticalStretch(0);
    fraPregledTitle->setSizePolicy(fraIspisTitleSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(4, 0, 0, 0);
    hboxLayout1->setSpacing(1);
    QLabel *lblTitle1 = new QLabel(tr("PREGLED"));
    hboxLayout1->addWidget(lblTitle1);
    QPushButton *btnExpandFrame1 = new QPushButton();
    btnExpandFrame1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame1->setFlat(true);
    btnExpandFrame1->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame1SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame1SizePolicy.setHorizontalStretch(0);
    btnExpandFrame1SizePolicy.setVerticalStretch(0);
    btnExpandFrame1->setSizePolicy(btnExpandFrame1SizePolicy);
    hboxLayout1->addWidget(btnExpandFrame1);
    fraPregledTitle->setLayout(hboxLayout1);
    vboxLayout5->addWidget(fraPregledTitle);
    // [2]
    m_btnPregledSporazum = new QPushButton(tr("SPORAZUM"));
    m_btnPregledSporazum->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnPregledSporazum->setFlat(true);
    m_btnPregledSporazum->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnPregledSporazum);
    m_btnPregledImovina = new QPushButton(tr("IMOVINA"));
    m_btnPregledImovina->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnPregledImovina->setFlat(true);
    m_btnPregledImovina->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnPregledImovina);
    m_btnPregledDetaljno = new QPushButton(tr("DETALJNO"));
    m_btnPregledDetaljno->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnPregledDetaljno->setFlat(true);
    m_btnPregledDetaljno->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnPregledDetaljno);
    m_btnPregledProcesi = new QPushButton(tr("PROCESI"));
    m_btnPregledProcesi->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnPregledProcesi->setFlat(true);
    m_btnPregledProcesi->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnPregledProcesi);
    m_fraToolbarPregled->setLayout(vboxLayout5);
}
void FrmDonatPregled::createToolbarWwmsFrame()
{
    m_fraToolbarWwms = new QFrame();
    m_fraToolbarWwms->setContentsMargins(0, 0, 0, 0);
    m_fraToolbarWwms->setFrameShape(QFrame::StyledPanel);
    //    QSizePolicy fraPregledToolBoxSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    //    fraPregledToolBoxSizePolicy.setHorizontalStretch(0);
    //    fraPregledToolBoxSizePolicy.setVerticalStretch(0);
    //    fraPregledToolBox->setSizePolicy(fraPregledToolBoxSizePolicy);
    QVBoxLayout *vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setContentsMargins(0, 1, 0, 1);
    vboxLayout2->setSpacing(1);
    // [1]
    QFrame *fraWwmsTitle = new QFrame();
    fraWwmsTitle->setContentsMargins(0, 0, 0, 0);
    fraWwmsTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraIspisTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraIspisTitleSizePolicy.setHorizontalStretch(0);
    fraIspisTitleSizePolicy.setVerticalStretch(0);
    fraWwmsTitle->setSizePolicy(fraIspisTitleSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(4, 0, 0, 0);
    hboxLayout1->setSpacing(1);
    QLabel *lblTitle1 = new QLabel(tr("WWMS"));
    hboxLayout1->addWidget(lblTitle1);
    QPushButton *btnExpandFrame1 = new QPushButton();
    btnExpandFrame1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame1->setFlat(true);
    btnExpandFrame1->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame1SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame1SizePolicy.setHorizontalStretch(0);
    btnExpandFrame1SizePolicy.setVerticalStretch(0);
    btnExpandFrame1->setSizePolicy(btnExpandFrame1SizePolicy);
    hboxLayout1->addWidget(btnExpandFrame1);
    fraWwmsTitle->setLayout(hboxLayout1);
    vboxLayout2->addWidget(fraWwmsTitle);
    // [2]
    m_btnWwmsStatusDonat = new QPushButton(tr("STATUS DONAT"));
    m_btnWwmsStatusDonat->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnWwmsStatusDonat->setFlat(true);
    m_btnWwmsStatusDonat->setCursor(Qt::PointingHandCursor);
    vboxLayout2->addWidget(m_btnWwmsStatusDonat);
    m_btnWwmsStatusWeb = new QPushButton(tr("STATUS WWMS"));
    m_btnWwmsStatusWeb->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnWwmsStatusWeb->setFlat(true);
    m_btnWwmsStatusWeb->setCursor(Qt::PointingHandCursor);
    vboxLayout2->addWidget(m_btnWwmsStatusWeb);
    m_fraToolbarWwms->setLayout(vboxLayout2);
}
void FrmDonatPregled::createToolbarDokumentFrame()
{
    m_fraToolbarDokument = new QFrame();
    m_fraToolbarDokument->setContentsMargins(0, 0, 0, 0);
    m_fraToolbarDokument->setFrameShape(QFrame::StyledPanel);
//    QSizePolicy fraPregledToolBoxSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//    fraPregledToolBoxSizePolicy.setHorizontalStretch(0);
//    fraPregledToolBoxSizePolicy.setVerticalStretch(0);
//    fraPregledToolBox->setSizePolicy(fraPregledToolBoxSizePolicy);
    QVBoxLayout *vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setContentsMargins(0, 1, 0, 1);
    vboxLayout3->setSpacing(1);
    // [1]
    QFrame *fraDokumentTitle = new QFrame();
    fraDokumentTitle->setContentsMargins(0, 0, 0, 0);
    fraDokumentTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraIspisTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraIspisTitleSizePolicy.setHorizontalStretch(0);
    fraIspisTitleSizePolicy.setVerticalStretch(0);
    fraDokumentTitle->setSizePolicy(fraIspisTitleSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(4, 0, 0, 0);
    hboxLayout1->setSpacing(1);
    QLabel *lblTitle1 = new QLabel(tr("DOKUMENT"));
    hboxLayout1->addWidget(lblTitle1);
    QPushButton *btnExpandFrame1 = new QPushButton();
    btnExpandFrame1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame1->setFlat(true);
    btnExpandFrame1->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame1SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame1SizePolicy.setHorizontalStretch(0);
    btnExpandFrame1SizePolicy.setVerticalStretch(0);
    btnExpandFrame1->setSizePolicy(btnExpandFrame1SizePolicy);
    hboxLayout1->addWidget(btnExpandFrame1);
    fraDokumentTitle->setLayout(hboxLayout1);
    vboxLayout3->addWidget(fraDokumentTitle);
    // [2]
    m_btnDokumentNapomena = new QPushButton(tr("NAPOMENA"));
    m_btnDokumentNapomena->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokumentNapomena->setFlat(true);
    m_btnDokumentNapomena->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnDokumentNapomena);
    m_btnDokumentDatoteke = new QPushButton(tr("DATOTEKA"));
    m_btnDokumentDatoteke->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokumentDatoteke->setFlat(true);
    m_btnDokumentDatoteke->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnDokumentDatoteke);
    m_btnDokumentSpis = new QPushButton(tr("SPIS"));
    m_btnDokumentSpis->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokumentSpis->setFlat(true);
    m_btnDokumentSpis->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnDokumentSpis);
    m_btnDokumentJop = new QPushButton(tr("JOP"));
    m_btnDokumentJop->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokumentJop->setFlat(true);
    m_btnDokumentJop->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnDokumentJop);
    m_btnDokumentDodijeliJop = new QPushButton(tr("DODIJELI JOP"));
    m_btnDokumentDodijeliJop->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokumentDodijeliJop->setFlat(true);
    m_btnDokumentDodijeliJop->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnDokumentDodijeliJop);
    QFrame *fraLine1 = new QFrame();
    fraLine1->setContentsMargins(2, 0, 2, 0);
    QSizePolicy fraHline1SizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraHline1SizePolicy.setHorizontalStretch(0);
    fraHline1SizePolicy.setVerticalStretch(0);
    fraLine1->setSizePolicy(fraHline1SizePolicy);
    fraLine1->setFrameShape(QFrame::StyledPanel);
    fraLine1->setFrameShadow(QFrame::Sunken);
    fraLine1->setMinimumHeight(2);
    vboxLayout3->addWidget(fraLine1);
    m_btnDokumentOtpisZaduzenja = new QPushButton(tr("OTPIS ZADUŽENJA"));
    m_btnDokumentOtpisZaduzenja->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokumentOtpisZaduzenja->setFlat(true);
    m_btnDokumentOtpisZaduzenja->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnDokumentOtpisZaduzenja);
    m_btnDokumentStorno = new QPushButton(tr("STORNO"));
    m_btnDokumentStorno->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokumentStorno->setFlat(true);
    m_btnDokumentStorno->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnDokumentStorno);
    m_btnDokumentPretvori1Kn = new QPushButton(tr("PRETVORI U 1kn"));
    m_btnDokumentPretvori1Kn->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnDokumentPretvori1Kn->setFlat(true);
    m_btnDokumentPretvori1Kn->setCursor(Qt::PointingHandCursor);
    vboxLayout3->addWidget(m_btnDokumentPretvori1Kn);
    m_fraToolbarDokument->setLayout(vboxLayout3);
}
void FrmDonatPregled::createToolbarIspisFrame()
{
    m_fraToolbarIspis = new QFrame();
    m_fraToolbarIspis->setContentsMargins(0, 0, 0, 0);
    m_fraToolbarIspis->setFrameShape(QFrame::StyledPanel);
    //    QSizePolicy fraPregledToolBoxSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    //    fraPregledToolBoxSizePolicy.setHorizontalStretch(0);
    //    fraPregledToolBoxSizePolicy.setVerticalStretch(0);
    //    fraPregledToolBox->setSizePolicy(fraPregledToolBoxSizePolicy);
    QVBoxLayout *vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setContentsMargins(0, 1, 0, 1);
    vboxLayout4->setSpacing(1);
    // [1]
    QFrame *fraIspisTitle = new QFrame();
    fraIspisTitle->setContentsMargins(0, 0, 0, 0);
    fraIspisTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraIspisTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraIspisTitleSizePolicy.setHorizontalStretch(0);
    fraIspisTitleSizePolicy.setVerticalStretch(0);
    fraIspisTitle->setSizePolicy(fraIspisTitleSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(4, 0, 0, 0);
    hboxLayout1->setSpacing(1);
    QLabel *lblTitle1 = new QLabel(tr("ISPIS"));
    hboxLayout1->addWidget(lblTitle1);
    QPushButton *btnExpandFrame1 = new QPushButton();
    btnExpandFrame1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame1->setFlat(true);
    btnExpandFrame1->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame1SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame1SizePolicy.setHorizontalStretch(0);
    btnExpandFrame1SizePolicy.setVerticalStretch(0);
    btnExpandFrame1->setSizePolicy(btnExpandFrame1SizePolicy);
    hboxLayout1->addWidget(btnExpandFrame1);
    fraIspisTitle->setLayout(hboxLayout1);
    vboxLayout4->addWidget(fraIspisTitle);
    // [2]
    m_btnIspisDokumenta = new QPushButton(tr("DOKUMENT"));
    m_btnIspisDokumenta->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnIspisDokumenta->setFlat(true);
    m_btnIspisDokumenta->setCursor(Qt::PointingHandCursor);
    vboxLayout4->addWidget(m_btnIspisDokumenta);
    m_fraToolbarIspis->setLayout(vboxLayout4);

}
void FrmDonatPregled::createToolbarAdminFrame()
{
    m_fraToolbarAdmin = new QFrame();
    m_fraToolbarAdmin->setContentsMargins(0, 0, 0, 0);
    m_fraToolbarAdmin->setFrameShape(QFrame::StyledPanel);
//    QSizePolicy fraPregledToolBoxSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//    fraPregledToolBoxSizePolicy.setHorizontalStretch(0);
//    fraPregledToolBoxSizePolicy.setVerticalStretch(0);
//    fraPregledToolBox->setSizePolicy(fraPregledToolBoxSizePolicy);
    QVBoxLayout *vboxLayout5 = new QVBoxLayout();
    vboxLayout5->setContentsMargins(0, 1, 0, 1);
    vboxLayout5->setSpacing(1);
//    vboxLayout5->setAlignment(Qt::AlignRight);
    // [1]
    QFrame *fraAdminTitle = new QFrame();
    fraAdminTitle->setContentsMargins(0, 0, 0, 0);
    fraAdminTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
//    fraAdminTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraAdminTitleSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    fraAdminTitleSizePolicy.setHorizontalStretch(0);
    fraAdminTitleSizePolicy.setVerticalStretch(0);
    fraAdminTitle->setSizePolicy(fraAdminTitleSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(4, 0, 0, 0);
    hboxLayout1->setSpacing(1);
    QLabel *lblTitle1 = new QLabel(tr("ADMIN"));
    hboxLayout1->addWidget(lblTitle1);
    QPushButton *btnExpandFrame1 = new QPushButton();
    btnExpandFrame1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuBlueUp.gif")));
    btnExpandFrame1->setFlat(true);
    btnExpandFrame1->setCursor(Qt::PointingHandCursor);
    QSizePolicy btnExpandFrame1SizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnExpandFrame1SizePolicy.setHorizontalStretch(0);
    btnExpandFrame1SizePolicy.setVerticalStretch(0);
    btnExpandFrame1->setSizePolicy(btnExpandFrame1SizePolicy);
    hboxLayout1->addWidget(btnExpandFrame1);
    fraAdminTitle->setLayout(hboxLayout1);
    vboxLayout5->addWidget(fraAdminTitle);
    // [2]
    m_btnAdminUlaznePoruke = new QPushButton(tr("ULAZNE PORUKE"));
    m_btnAdminUlaznePoruke->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnAdminUlaznePoruke->setFlat(true);
    m_btnAdminUlaznePoruke->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnAdminUlaznePoruke);
    m_btnAdminKanalProdaje = new QPushButton(tr("KANAL PRODAJE"));
    m_btnAdminKanalProdaje->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnAdminKanalProdaje->setFlat(true);
    m_btnAdminKanalProdaje->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnAdminKanalProdaje);
    m_btnAdminDatumZahtjeva = new QPushButton(tr("DATUM ZAHTJEVA"));
    m_btnAdminDatumZahtjeva->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnAdminDatumZahtjeva->setFlat(true);
    m_btnAdminDatumZahtjeva->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnAdminDatumZahtjeva);
    QFrame *fraLine1 = new QFrame();
    fraLine1->setContentsMargins(2, 0, 2, 0);
    QSizePolicy fraHline1SizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraHline1SizePolicy.setHorizontalStretch(0);
    fraHline1SizePolicy.setVerticalStretch(0);
    fraLine1->setSizePolicy(fraHline1SizePolicy);
    fraLine1->setFrameShape(QFrame::StyledPanel);
    fraLine1->setFrameShadow(QFrame::Sunken);
    fraLine1->setMinimumHeight(2);
    vboxLayout5->addWidget(fraLine1);
    m_btnAdminStorno = new QPushButton(tr("STORNO"));
    m_btnAdminStorno->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnAdminStorno->setFlat(true);
    m_btnAdminStorno->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnAdminStorno);
    m_btnAdminNastavakRealizacije = new QPushButton(tr("NASTAVAK REALIZ."));
    m_btnAdminNastavakRealizacije->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/dll-icon.jpg")));
    m_btnAdminNastavakRealizacije->setFlat(true);
    m_btnAdminNastavakRealizacije->setCursor(Qt::PointingHandCursor);
    vboxLayout5->addWidget(m_btnAdminNastavakRealizacije);
    m_fraToolbarAdmin->setLayout(vboxLayout5);
}

void FrmDonatPregled::createFormActions()
{
    connect(m_btnZatvori,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnZatvori_clicked()));

    // [Trazi]
    connect(m_btnTrazi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnTrazi_clicked()));
    connect(m_btnDokumentTrazi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentTrazi_clicked()));
    connect(m_btnTelefonTrazi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnTelefonTrazi_clicked()));
    connect(m_btnAssetTrazi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnAssetTrazi_clicked()));
    connect(m_btnSporazumTrazi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnSporazumTrazi_clicked()));
    connect(m_btnTicketTrazi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnTicketTrazi_clicked()));
    connect(m_btnKupacTrazi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnKupacTrazi_clicked()));
    // [Pregled Toolbar]
    connect(m_btnPregledSporazum,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPregledSporazum_clicked()));
    connect(m_btnPregledImovina,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPregledImovina_clicked()));
    connect(m_btnPregledDetaljno,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPregledDetaljno_clicked()));
    connect(m_btnPregledProcesi,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnPregledProcesi_clicked()));
    // [Wwms Toolbar]
    connect(m_btnWwmsStatusDonat,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnWwmsStatusDonat_clicked()));
    connect(m_btnWwmsStatusWeb,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnWwmsStatusWeb_clicked()));
    // [Dokument Toolbar]
    connect(m_btnDokumentNapomena,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentNapomena_clicked()));
    connect(m_btnDokumentDatoteke,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentDatoteke_clicked()));
    connect(m_btnDokumentSpis,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentSpis_clicked()));
    connect(m_btnDokumentJop,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentJop_clicked()));
    connect(m_btnDokumentDodijeliJop,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentDodijeliJop_clicked()));
    connect(m_btnDokumentOtpisZaduzenja,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentOtpisZaduzenja_clicked()));
    connect(m_btnDokumentStorno,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentStorno_clicked()));
    connect(m_btnDokumentPretvori1Kn,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnDokumentPretvori1Kn_clicked()));
    // [Ipis Toolbar]
    connect(m_btnIspisDokumenta,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnIspisDokumenta_clicked()));
    // [Admin Toolbar]
    connect(m_btnAdminUlaznePoruke,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnAdminUlaznePoruke_clicked()));
    connect(m_btnAdminKanalProdaje,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnAdminKanalProdaje_clicked()));
    connect(m_btnAdminDatumZahtjeva,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnAdminDatumZahtjeva_clicked()));
    connect(m_btnAdminStorno,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnAdminStorno_clicked()));
    connect(m_btnAdminNastavakRealizacije,
            SIGNAL(clicked()),
            this,
            SLOT(on_btnAdminNastavakRealizacije_clicked()));

    connect(m_treeSporazumi,
                SIGNAL(itemPressed(QTreeWidgetItem*, int)),
                this,
                SLOT(on_treeSporazumi_itemPressed(QTreeWidgetItem*, int)));

}

// [ Private Member Functions ]
void FrmDonatPregled::clearFormData()
{
//    m_txtFltUpit->clear();
    m_txtKupacId->clear();
    m_txtKupacNaziv->clear();
    m_txtKupacAdresa->clear();
    clearSporazumData();
    m_treeSporazumi->clear();
}

void FrmDonatPregled::clearSporazumData()
{
    m_txtKanalProdaje->clear();
    m_txtUnioKorisnikId->clear();
    m_txtProdaoKorisnikId->clear();
    m_txtBrojDokumenta->clear();
    m_txtDatumSporazuma->clear();
    m_txtSporazumId->clear();
    m_txtTicketId->clear();
    m_txtStatus->clear();
    m_txtAktivnost->clear();
    m_txtOrderId->clear();
    m_txtPromijena->clear();
    m_txtTelefon->clear();
    m_txtAsset->clear();
    m_txtKlasa->clear();
    m_txtUgovor->clear();
    m_txtGeneva->clear();
    m_txtWwms->clear();
    m_txtWwmsNapomena->clear();
    m_treeSporazumAtributi->clear();
}

void FrmDonatPregled::popuniZahtjeve()
{
    string strSqlStatement;
    strSqlStatement.append("BEGIN puni_pregled_zahtjeva(:sporazum_id_par, :kupac_id_par, :broj_dok_par, :gimovine_id_par, :tel_broj_par, :ticket_id_par); END;");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setUInt(1, m_fltSporazumId);
        sqlStatement->setUInt(2, m_fltKupacId);
        sqlStatement->setString(3, m_fltBrojDokumenta);
        sqlStatement->setUInt(4, m_fltGrupaImovineId);
        sqlStatement->setString(5, m_fltTelefonskiBroj);
        sqlStatement->setString(6, m_fltTicketId);
        sqlStatement->executeUpdate();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.erase();
    strSqlStatement.append("SELECT ");
    strSqlStatement.append("  SPORAZUM_ID, ");
    strSqlStatement.append("  NVL(BROJ_DOK, '-'), ");
    strSqlStatement.append("  KUPAC_ID, ");
    strSqlStatement.append("  GIMOVINE_ID, ");
    strSqlStatement.append("  NVL(TEL_BROJ, '0'), ");
    strSqlStatement.append("  NVL(KLASA, 'xxxxx'), ");
    strSqlStatement.append("  STATUS_PROVISIONING, ");
    strSqlStatement.append("  STATUS_UGOVARANJE, ");
    strSqlStatement.append("  STATUS_BILLING, ");
    strSqlStatement.append("  ORDER_ID, ");
    strSqlStatement.append("  TICKET_ID, ");
    strSqlStatement.append("  TO_CHAR(DATUM_ZAHTJEVA, 'DD.MM.YYYY HH:MI:SS'), ");
    strSqlStatement.append("  TO_CHAR(DATUM_ZADNJE_PROMJENE, 'DD.MM.YYYY HH:MI:SS'), ");
    strSqlStatement.append("  OPERATER, ");
    strSqlStatement.append("  PRODAVAC, ");
    strSqlStatement.append("  KANAL, ");
    strSqlStatement.append("  NAPOMENA_PROVISIONING, ");
    strSqlStatement.append("  NVL(AKTIVNOST, 100), ");
    strSqlStatement.append("  NVL(ZAVRSENOST, 100), ");
    strSqlStatement.append("  ID, ");
    strSqlStatement.append("  STATUS_KOMUNIKACIJA_KORISNIKU ");
    strSqlStatement.append("FROM ");
    strSqlStatement.append("  TEMP_PREGLED_ZAHTJEVA ");
    strSqlStatement.append("ORDER BY ");
    strSqlStatement.append("  SPORAZUM_ID DESC, ORDER_ID ");
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listZahtjevi;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            bool bPostoji;
            bPostoji = false;
            int iSporazumLocationInList = 0;
            unsigned int iTraziSporazumId = rs->getUInt(1);

            for(int i = 0; i < listZahtjevi.size(); ++i)
            {
                if(iTraziSporazumId == listZahtjevi.at(i)->text(3).toUInt())
                {
                    bPostoji = true;
                    iSporazumLocationInList = i;
                    break;
                }
            }

            if(bPostoji == false)
            {
                QTreeWidgetItem *itemZahtjev = new QTreeWidgetItem();
                itemZahtjev->setText(2,
                                       QString::fromStdString(rs->getString(12))
                                       % tr(" ... ")
                                       % QString::fromStdString(rs->getString(2)));
                itemZahtjev->setText(3, QString::number(rs->getUInt(1)));
                itemZahtjev->setText(4, QString::fromStdString(rs->getString(2)));
                itemZahtjev->setText(5, QString::number(rs->getUInt(3)));
                itemZahtjev->setText(6, QString::number(rs->getUInt(4)));
                itemZahtjev->setText(7, QString::fromStdString(rs->getString(5)));
                itemZahtjev->setText(8, QString::fromStdString(rs->getString(6)));
                itemZahtjev->setText(9, QString::fromStdString(rs->getString(7)));
                itemZahtjev->setText(10, QString::fromStdString(rs->getString(8)));
                itemZahtjev->setText(11, QString::fromStdString(rs->getString(9)));
                itemZahtjev->setText(12, QString::number(rs->getUInt(10)));
                itemZahtjev->setText(13, QString::number(rs->getUInt(11)));
                itemZahtjev->setText(14, QString::fromStdString(rs->getString(12)));
                itemZahtjev->setText(15, QString::fromStdString(rs->getString(13)));
                itemZahtjev->setText(16, QString::fromStdString(rs->getString(14)));
                itemZahtjev->setText(17, QString::fromStdString(rs->getString(15)));
                itemZahtjev->setText(18, QString::fromStdString(rs->getString(16)));
                itemZahtjev->setText(19, QString::fromStdString(rs->getString(17)));
                itemZahtjev->setText(20, QString::number(rs->getInt(18)));
                itemZahtjev->setText(21, QString::number(rs->getInt(19)));
                itemZahtjev->setText(22, tr("0"));
                itemZahtjev->setText(23, QString::fromStdString(rs->getString(21)));
                listZahtjevi.append(itemZahtjev);
                iSporazumLocationInList = listZahtjevi.count() - 1;

                QTreeWidgetItem *itemZahtjevStavka = new QTreeWidgetItem();
                int iAktivnost, iZavrsenost;
                iAktivnost = rs->getInt(19);
                iZavrsenost = rs->getInt(18);
                switch (iZavrsenost)
                {
                    case 0:
                        itemZahtjevStavka->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zuti.JPG")));
                        break;
                    case 1:
                        itemZahtjevStavka->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                        break;
                    case 2:
                        itemZahtjevStavka->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                        break;
                }
                switch (iAktivnost)
                {
                    case 0:
                        itemZahtjevStavka->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/POP_TEL.GIF")));
                        break;
                    case 1:
                        itemZahtjevStavka->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/UG_TEL.GIF")));
                        break;
                    case 2:
                        itemZahtjevStavka->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ISK_U.GIF")));
                        break;
                }
                itemZahtjevStavka->setText(2,
                                        QString::fromStdString(rs->getString(5))
                                        % tr(" ... ")
                                        % QString::fromStdString(rs->getString(6)));
                itemZahtjevStavka->setText(3, QString::number(rs->getUInt(1)));
                itemZahtjevStavka->setText(4, QString::fromStdString(rs->getString(2)));
                itemZahtjevStavka->setText(5, QString::number(rs->getUInt(3)));
                itemZahtjevStavka->setText(6, QString::number(rs->getUInt(4)));
                itemZahtjevStavka->setText(7, QString::fromStdString(rs->getString(5)));
                itemZahtjevStavka->setText(8, QString::fromStdString(rs->getString(6)));
                itemZahtjevStavka->setText(9, QString::fromStdString(rs->getString(7)));
                itemZahtjevStavka->setText(10, QString::fromStdString(rs->getString(8)));
                itemZahtjevStavka->setText(11, QString::fromStdString(rs->getString(9)));
                itemZahtjevStavka->setText(12, QString::number(rs->getUInt(10)));
                itemZahtjevStavka->setText(13, QString::number(rs->getUInt(11)));
                itemZahtjevStavka->setText(14, QString::fromStdString(rs->getString(12)));
                itemZahtjevStavka->setText(15, QString::fromStdString(rs->getString(13)));
                itemZahtjevStavka->setText(16, QString::fromStdString(rs->getString(14)));
                itemZahtjevStavka->setText(17, QString::fromStdString(rs->getString(15)));
                itemZahtjevStavka->setText(18, QString::fromStdString(rs->getString(16)));
                itemZahtjevStavka->setText(19, QString::fromStdString(rs->getString(17)));
                itemZahtjevStavka->setText(20, QString::number(iAktivnost));
                itemZahtjevStavka->setText(21, QString::number(iZavrsenost));
                itemZahtjevStavka->setText(22, QString::number(rs->getUInt(20)));
                itemZahtjevStavka->setText(23, QString::fromStdString(rs->getString(21)));
                listZahtjevi.append(itemZahtjevStavka);
                listZahtjevi.at(iSporazumLocationInList)->addChild(itemZahtjevStavka);
            }
            else
            {
                 QTreeWidgetItem *itemZahtjevStavka = new QTreeWidgetItem();
                 int iAktivnost, iZavrsenost;
                 iAktivnost = rs->getInt(19);
                 iZavrsenost = rs->getInt(18);
                 switch (iZavrsenost)
                 {
                     case 0:
                         itemZahtjevStavka->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zuti.JPG")));
                         break;
                     case 1:
                         itemZahtjevStavka->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG")));
                         break;
                     case 2:
                         itemZahtjevStavka->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG")));
                         break;
                 }
                 switch (iAktivnost)
                 {
                     case 0:
                         itemZahtjevStavka->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/POP_TEL.GIF")));
                         break;
                     case 1:
                         itemZahtjevStavka->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/UG_TEL.GIF")));
                         break;
                     case 2:
                         itemZahtjevStavka->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ISK_U.GIF")));
                         break;
                 }
                 itemZahtjevStavka->setText(2,
                                         QString::fromStdString(rs->getString(5))
                                         % tr(" ... ")
                                         % QString::fromStdString(rs->getString(6)));
                 itemZahtjevStavka->setText(3, QString::number(rs->getUInt(1)));
                 itemZahtjevStavka->setText(4, QString::fromStdString(rs->getString(2)));
                 itemZahtjevStavka->setText(5, QString::number(rs->getUInt(3)));
                 itemZahtjevStavka->setText(6, QString::number(rs->getUInt(4)));
                 itemZahtjevStavka->setText(7, QString::fromStdString(rs->getString(5)));
                 itemZahtjevStavka->setText(8, QString::fromStdString(rs->getString(6)));
                 itemZahtjevStavka->setText(9, QString::fromStdString(rs->getString(7)));
                 itemZahtjevStavka->setText(10, QString::fromStdString(rs->getString(8)));
                 itemZahtjevStavka->setText(11, QString::fromStdString(rs->getString(9)));
                 itemZahtjevStavka->setText(12, QString::number(rs->getUInt(10)));
                 itemZahtjevStavka->setText(13, QString::number(rs->getUInt(11)));
                 itemZahtjevStavka->setText(14, QString::fromStdString(rs->getString(12)));
                 itemZahtjevStavka->setText(15, QString::fromStdString(rs->getString(13)));
                 itemZahtjevStavka->setText(16, QString::fromStdString(rs->getString(14)));
                 itemZahtjevStavka->setText(17, QString::fromStdString(rs->getString(15)));
                 itemZahtjevStavka->setText(18, QString::fromStdString(rs->getString(16)));
                 itemZahtjevStavka->setText(19, QString::fromStdString(rs->getString(17)));
                 itemZahtjevStavka->setText(20, QString::number(iAktivnost));
                 itemZahtjevStavka->setText(21, QString::number(iZavrsenost));
                 itemZahtjevStavka->setText(22, QString::number(rs->getUInt(20)));
                 itemZahtjevStavka->setText(23, QString::fromStdString(rs->getString(21)));
                 listZahtjevi.append(itemZahtjevStavka);
                 listZahtjevi.at(iSporazumLocationInList)->addChild(itemZahtjevStavka);
             }
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if(!listZahtjevi.empty())
    {
        listZahtjevi.first()->setSelected(true);
        m_treeSporazumi->insertTopLevelItems(0, listZahtjevi);
        m_treeSporazumi->setCurrentItem(listZahtjevi.first());
        m_treeSporazumi->expandAll();

        popuniPregledZahtjeva(listZahtjevi.at(1));
    }
}
void FrmDonatPregled::popuniPregledZahtjeva(QTreeWidgetItem *itemTreeStavka)
{
    clearSporazumData();
    // Fill Data

    m_txtKanalProdaje->setText(itemTreeStavka->text(18));
    m_txtUnioKorisnikId->setText(itemTreeStavka->text(16));
    m_txtProdaoKorisnikId->setText(itemTreeStavka->text(17));
    m_txtBrojDokumenta->setText(itemTreeStavka->text(4));
    m_txtDatumSporazuma->setText(itemTreeStavka->text(14));
    m_txtSporazumId->setText(itemTreeStavka->text(3));
    m_txtTicketId->setText(itemTreeStavka->text(13));

    switch(itemTreeStavka->text(21).toInt())
    {
        case 0:
            m_txtStatus->setText(tr("U TIJEKU"));
            break;
        case 1:
            m_txtStatus->setText(tr("UKLJUČENJE"));
            break;
        case 2:
            m_txtStatus->setText(tr("STORNIRANO"));
            break;
    }
    switch(itemTreeStavka->text(20).toInt())
    {
        case 0:
            m_txtAktivnost->setText(tr("PROMJENA"));
            break;
        case 1:
            m_txtAktivnost->setText(tr("UKLJUČENJE"));
            break;
        case 2:
            m_txtAktivnost->setText(tr("ISKLJUČENJE"));
            break;
    }
    m_txtOrderId->setText(itemTreeStavka->text(12));
    m_txtPromijena->setText(itemTreeStavka->text(15));
    m_txtTelefon->setText(itemTreeStavka->text(7));
    m_txtAsset->setText(itemTreeStavka->text(6));
    m_txtKlasa->setText(itemTreeStavka->text(8));
    m_txtUgovor->setText(itemTreeStavka->text(10));
    m_txtGeneva->setText(itemTreeStavka->text(11));
    m_txtWwms->setText(itemTreeStavka->text(9));
    m_txtWwmsNapomena->setText(itemTreeStavka->text(19));

    m_iGrupaImovineId = m_txtAsset->text().toUInt();
    string strSporazumId;
    strSporazumId = m_txtSporazumId->text().toStdString();
    if(cttl::str2int(m_iSporazumId, strSporazumId) == false)
    {
        return;
    }

    popuniKupca(itemTreeStavka->text(5).toUInt());
    popuniAtribute(itemTreeStavka->text(12).toStdString());
}
void FrmDonatPregled::popuniKupca(unsigned int iKupacId)
{
    m_txtKupacId->setText(QString::number(iKupacId));
    if(iKupacId == 0)
        return;

    string strSqlStatement;
    strSqlStatement.append("SELECT FORMATIRANI_NAZIV, FORMATIRANA_ADRESA FROM HIJERARHIJA_STR_ADRESE3 WHERE ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(iKupacId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_txtKupacNaziv->setText(QString::fromStdString(rs->getString(1)));
            m_txtKupacAdresa->setText(QString::fromStdString(rs->getString(2)));
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}
void FrmDonatPregled::popuniAtribute(string strOrderId)
{
    if(strOrderId.empty() == true)
        return;

    string strSqlStatement;
    strSqlStatement.append("SELECT DISTINCT X.NAME, X.VALUE FROM WWMS_LINEITEMS1 L,WWMS_XA1 X ");
    strSqlStatement.append("WHERE L.ORDER_ID = X.ORDER_ID AND L.MESSAGE_ID = X.MESSAGE_ID AND L.ID = X.ORDERITEMID ");
    strSqlStatement.append("AND L.STATUS = 'F.S. Approved' AND L.ORDER_ID ='");
    strSqlStatement.append(strOrderId);
    strSqlStatement.append("' ORDER BY 1 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listSporazumAtribut;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemSporazumAtribut = new QTreeWidgetItem();
            itemSporazumAtribut->setText(0,
                                    QString::fromStdString(rs->getString(1))
                                    % tr(" ... ")
                                    % QString::fromStdString(rs->getString(2)));
            listSporazumAtribut.append(itemSporazumAtribut);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if(listSporazumAtribut.empty())
    {
        QTreeWidgetItem *itemSporazumAtribut = new QTreeWidgetItem();
        itemSporazumAtribut->setText(0, tr(" NEMA ATRIBUTA "));
        listSporazumAtribut.append(itemSporazumAtribut);
    }

    listSporazumAtribut.first()->setSelected(true);
    m_treeSporazumAtributi->insertTopLevelItems(0, listSporazumAtribut);
    m_treeSporazumAtributi->setCurrentItem(listSporazumAtribut.first());
    m_treeSporazumAtributi->expandAll();
}

// [ Event Handlers ]
void FrmDonatPregled::on_btnZatvori_clicked()
{
    this->close();
}
void FrmDonatPregled::on_btnTrazi_clicked()
{
    if(m_txtFltUpit->text().isEmpty())
    {
        return;
    }

    switch(m_SearchMode)
    {
        case TraziPoBrojDokumenta:
            {
                m_fltSporazumId = 0;
                m_fltKupacId = 0;
                m_fltGrupaImovineId = 0;
                m_fltBrojDokumenta = m_txtFltUpit->text().toStdString();
                m_fltTelefonskiBroj.clear();
                m_fltTicketId.clear();
                clearFormData();
                popuniZahtjeve();
                break;
            }
        case TraziPoTelefonu:
            {
                m_fltSporazumId = 0;
                m_fltKupacId = 0;
                m_fltGrupaImovineId = 0;
                m_fltBrojDokumenta.clear();
                m_fltTelefonskiBroj = m_txtFltUpit->text().toStdString();
                m_fltTicketId.clear();
                clearFormData();
                popuniZahtjeve();
                break;
            }
        case TraziPoAssetId:
            {
                unsigned int iGrupaImovineId;
                string strFltUpit;
                strFltUpit = m_txtFltUpit->text().toStdString();
                if(cttl::str2int(iGrupaImovineId, strFltUpit) == false)
                {
                    return;
                }
                m_fltGrupaImovineId = iGrupaImovineId;
                m_fltSporazumId = 0;
                m_fltKupacId = 0;
                m_fltBrojDokumenta.clear();
                m_fltTelefonskiBroj.clear();
                m_fltTicketId.clear();
                clearFormData();
                popuniZahtjeve();
                break;
            }
        case TraziPoSporazumId:
            {
                unsigned int iSporazumId;
                string strFltUpit;
                strFltUpit = m_txtFltUpit->text().toStdString();
                if(cttl::str2int(iSporazumId, strFltUpit) == false)
                {
                    return;
                }
                m_fltSporazumId = iSporazumId;
                m_fltKupacId = 0;
                m_fltGrupaImovineId = 0;
                m_fltBrojDokumenta.clear();
                m_fltTelefonskiBroj.clear();
                m_fltTicketId.clear();
                clearFormData();
                popuniZahtjeve();
                break;
            }
        case TraziPoTicketId:
            {
                m_fltSporazumId = 0;
                m_fltKupacId = 0;
                m_fltGrupaImovineId = 0;
                m_fltBrojDokumenta.clear();
                m_fltTelefonskiBroj.clear();
                m_fltTicketId = m_txtFltUpit->text().toStdString();
                clearFormData();
                popuniZahtjeve();
                break;
            }
        case TraziPoUlogaStrankeId:
            {
                unsigned int iUlogaStrankeId;
                string strFltUpit;
                strFltUpit = m_txtFltUpit->text().toStdString();
                if(cttl::str2int(iUlogaStrankeId, strFltUpit) == false)
                {
                    return;
                }
                m_fltSporazumId = 0;
                m_fltKupacId = iUlogaStrankeId;
                m_fltGrupaImovineId = 0;
                m_fltBrojDokumenta.clear();
                m_fltTelefonskiBroj.clear();
                m_fltTicketId.clear();
                clearFormData();
                popuniZahtjeve();
                break;
            }
    }
}
void FrmDonatPregled::on_btnDokumentTrazi_clicked()
{
    m_SearchMode = TraziPoBrojDokumenta;
    m_txtFltUpit->setFocus();
}
void FrmDonatPregled::on_btnTelefonTrazi_clicked()
{
    m_SearchMode = TraziPoTelefonu;
    m_txtFltUpit->setFocus();
}
void FrmDonatPregled::on_btnAssetTrazi_clicked()
{
    m_SearchMode = TraziPoAssetId;
    m_txtFltUpit->setFocus();
}
void FrmDonatPregled::on_btnSporazumTrazi_clicked()
{
    m_SearchMode = TraziPoSporazumId;
    m_txtFltUpit->setFocus();
}
void FrmDonatPregled::on_btnTicketTrazi_clicked()
{
    m_SearchMode = TraziPoTicketId;
    m_txtFltUpit->setFocus();
}
void FrmDonatPregled::on_btnKupacTrazi_clicked()
{
    m_SearchMode = TraziPoUlogaStrankeId;
    m_txtFltUpit->setFocus();
}

void FrmDonatPregled::on_btnPregledSporazum_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat stavke sporazuma
    FrmStavkeSporazuma *frmStavkeSporazuma = new FrmStavkeSporazuma(m_iSporazumId, this);
    frmStavkeSporazuma->exec();
    delete frmStavkeSporazuma;
}
void FrmDonatPregled::on_btnPregledImovina_clicked()
{
    if(m_iGrupaImovineId == 0)
        return;

    // Show Donat stavke sporazuma
    FrmPregledImovine *frmPregledImovine = new FrmPregledImovine(m_iGrupaImovineId, this);
    frmPregledImovine->exec();
    delete frmPregledImovine;
}
void FrmDonatPregled::on_btnPregledDetaljno_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat detaljan pregled sporazuma
    FrmPregledSporazuma *frmDetaljanPregledSporazuma = new FrmPregledSporazuma(m_iSporazumId, this);
    frmDetaljanPregledSporazuma->exec();
    delete frmDetaljanPregledSporazuma;
}
void FrmDonatPregled::on_btnPregledProcesi_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat order management processes
    FrmPregledProcesa *frmPregledProcesa = new FrmPregledProcesa(m_iSporazumId, this);
    frmPregledProcesa->exec();
    delete frmPregledProcesa;

}
void FrmDonatPregled::on_btnWwmsStatusDonat_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show Donat - WWMS Ticket status
    FrmWwmsPregled *frmWwmsTicketPregled = new FrmWwmsPregled(m_iSporazumId, 1, this);
    frmWwmsTicketPregled->exec();
    delete frmWwmsTicketPregled;
}
void FrmDonatPregled::on_btnWwmsStatusWeb_clicked()
{
    if(m_iSporazumId == 0)
        return;

    // Show InfoWeb - WWMS Ticket status
}
void FrmDonatPregled::on_btnDokumentNapomena_clicked()
{

}
void FrmDonatPregled::on_btnDokumentDatoteke_clicked()
{

}
void FrmDonatPregled::on_btnDokumentSpis_clicked()
{

}
void FrmDonatPregled::on_btnDokumentJop_clicked()
{

}
void FrmDonatPregled::on_btnDokumentDodijeliJop_clicked()
{

}
void FrmDonatPregled::on_btnDokumentOtpisZaduzenja_clicked()
{

}
void FrmDonatPregled::on_btnDokumentStorno_clicked()
{

}
void FrmDonatPregled::on_btnDokumentPretvori1Kn_clicked()
{

}
void FrmDonatPregled::on_btnIspisDokumenta_clicked()
{

}
void FrmDonatPregled::on_btnAdminUlaznePoruke_clicked()
{

}
void FrmDonatPregled::on_btnAdminKanalProdaje_clicked()
{

}
void FrmDonatPregled::on_btnAdminDatumZahtjeva_clicked()
{

}
void FrmDonatPregled::on_btnAdminStorno_clicked()
{

}
void FrmDonatPregled::on_btnAdminNastavakRealizacije_clicked()
{

}

void FrmDonatPregled::on_treeSporazumi_itemPressed(QTreeWidgetItem* treeItem, int)
{
        popuniPregledZahtjeva(treeItem);
}

FrmDonatPregled::~FrmDonatPregled()
{
    m_treeSporazumi->clear();
    m_treeSporazumAtributi->clear();
}

}   // namespace sporazumi
