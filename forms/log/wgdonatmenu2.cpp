/************************************* Module Header **************************************\
* Module Name:  wgdonatmenu2.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of wgDonatMenu2 DONAT menu form.
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

#include "wgdonatmenu2.h"

namespace Log {

WgDonatMenu2::WgDonatMenu2(QWidget *parent) :
    QWidget(parent)
{
    m_hboxDonatMenu2 = new QHBoxLayout();
    m_hboxDonatMenu2->setContentsMargins(2, 2, 2, 2);
    m_hboxDonatMenu2->setSpacing(1);
    // [0]
    creatDonatSearchPanel();
    m_hboxDonatMenu2->addWidget(m_fraDonatSearch);
    // [10]
    creatDonatUlogeStranke();
    m_hboxDonatMenu2->addWidget(m_fraDonatUlogeStranke);

//    QSizePolicy fraDonatMenu2SizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    fraDonatMenu2SizePolicy.setHorizontalStretch(0);
//    fraDonatMenu2SizePolicy.setVerticalStretch(0);
//    this->setSizePolicy(fraDonatMenu2SizePolicy);

    setLayout(m_hboxDonatMenu2);

    connect(m_txtDonatSearch,
            SIGNAL(textEdited(const QString &)),
            SLOT(toUpper(const QString &)));
    connect(m_txtDonatSearch,
            SIGNAL(returnPressed()),
            m_btnDonatTrazi,
            SIGNAL(clicked()));
}

void WgDonatMenu2::creatDonatSearchPanel()
{
    m_fraDonatSearch = new QFrame();
    m_fraDonatSearch->setContentsMargins(0, 2, 0, 2);
    m_fraDonatSearch->setFrameShape(QFrame::StyledPanel);
    m_vboxDonatSearch = new QVBoxLayout();
    m_vboxDonatSearch->setContentsMargins(2, 2, 2, 2);
    m_vboxDonatSearch->setSpacing(1);

    createDonatSearchStrankaTitle();

    m_fraDonatSearchFlt = new QFrame();
    m_fraDonatSearchFlt->setContentsMargins(0, 0, 0, 0);
//    m_fraDonatSearchFlt->setFrameShape(QFrame::StyledPanel);
    m_vboxDonatSearchFlt = new QVBoxLayout();
    m_vboxDonatSearchFlt->setContentsMargins(0, 2, 0, 2);
    m_vboxDonatSearchFlt->setSpacing(1);

    createDonatSearchMjestoTitle();
    createDonatSearchAdresaTitle();
    createDonatSearchLine();
    createDonatSearchToolbar();

    m_fraDonatSearchFlt->setLayout(m_vboxDonatSearchFlt);

    m_vboxDonatSearch->addWidget(m_fraDonatSearchFlt);
    m_fraDonatSearch->setLayout(m_vboxDonatSearch);
}

void WgDonatMenu2::createDonatSearchStrankaTitle()
{
    // [0]
    QFrame *fraStrankaSeachTitle = new QFrame();
    fraStrankaSeachTitle->setContentsMargins(0, 0, 0, 0);
    fraStrankaSeachTitle->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxStrankaSeachTitle = new QHBoxLayout();
    hboxStrankaSeachTitle->setContentsMargins(2, 2, 2, 2);
    hboxStrankaSeachTitle->setSpacing(1);

    QLabel *lblStrankaTitle = new QLabel(tr("Stranka"));
//    lblStrankaTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblStrankaTitleSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lblStrankaTitleSizePolicy.setHorizontalStretch(0);
    lblStrankaTitleSizePolicy.setVerticalStretch(0);
    lblStrankaTitle->setSizePolicy(lblStrankaTitleSizePolicy);
    hboxStrankaSeachTitle->addWidget(lblStrankaTitle);

    QCheckBox *chkAktivne = new QCheckBox(tr("Aktivne"));
//    chkAktivne->set(QFrame::StyledPanel);
    chkAktivne->setChecked(TRUE);
    QSizePolicy chkAktivneSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    chkAktivneSizePolicy.setHorizontalStretch(0);
    chkAktivneSizePolicy.setVerticalStretch(0);
    chkAktivne->setSizePolicy(chkAktivneSizePolicy);
    hboxStrankaSeachTitle->addWidget(chkAktivne);

    QCheckBox *chkSveAdrese = new QCheckBox(tr("Sve adrese"));
//    chkSveAdrese->setFrameShape(QFrame::StyledPanel);
    chkSveAdrese->setChecked(TRUE);
    QSizePolicy chkSveAdreseSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    chkSveAdreseSizePolicy.setHorizontalStretch(0);
    chkSveAdreseSizePolicy.setVerticalStretch(0);
    chkSveAdrese->setSizePolicy(chkSveAdreseSizePolicy);
    hboxStrankaSeachTitle->addWidget(chkSveAdrese, 0, Qt::AlignRight);

    fraStrankaSeachTitle->setLayout(hboxStrankaSeachTitle);
    m_vboxDonatSearch->addWidget(fraStrankaSeachTitle);
}

void WgDonatMenu2::createDonatSearchMjestoTitle()
{
    // [1]
    QFrame *fraDonatSearchMjesto = new QFrame();
    fraDonatSearchMjesto->setContentsMargins(0, 0, 0, 0);
//    fraDonatSearchMjesto->setFrameShape(QFrame::StyledPanel);

    QHBoxLayout *hboxMjesta = new QHBoxLayout();
    hboxMjesta->setContentsMargins(2, 2, 2, 2);
    hboxMjesta->setSpacing(1);

    QLabel *lblMjestoTitle = new QLabel(tr("Mjesto :"));
    lblMjestoTitle->setMinimumWidth(60);
    hboxMjesta->addWidget(lblMjestoTitle);

    QLineEdit *txtFltMjesto = new QLineEdit();
    txtFltMjesto->setMinimumWidth(90);
    txtFltMjesto->setMaximumWidth(120);
    hboxMjesta->addWidget(txtFltMjesto);

    QLineEdit *txtMjesto = new QLineEdit();
    txtMjesto->setReadOnly(TRUE);
    txtMjesto->setEnabled(FALSE);
    hboxMjesta->addWidget(txtMjesto);

    fraDonatSearchMjesto->setLayout(hboxMjesta);
    m_vboxDonatSearchFlt->addWidget(fraDonatSearchMjesto);
}

void WgDonatMenu2::createDonatSearchAdresaTitle()
{
    // [1]
    QFrame *fraDonatSearchAdresa = new QFrame();
    fraDonatSearchAdresa->setContentsMargins(0, 0, 0, 0);
//    fraDonatSearchAdresa->setFrameShape(QFrame::StyledPanel);

    QHBoxLayout *hboxAdresa = new QHBoxLayout();
    hboxAdresa->setContentsMargins(2, 2, 2, 2);
    hboxAdresa->setSpacing(1);

    QLabel *lblUlicaTitle = new QLabel(tr("Ulica :"));
    lblUlicaTitle->setMinimumWidth(60);
    hboxAdresa->addWidget(lblUlicaTitle);

    QLineEdit *txtFltUlica = new QLineEdit();
    txtFltUlica->setMinimumWidth(90);
    txtFltUlica->setMaximumWidth(120);
    hboxAdresa->addWidget(txtFltUlica);

    QLineEdit *txtUlica = new QLineEdit();
    txtUlica->setReadOnly(TRUE);
    txtUlica->setEnabled(FALSE);
    hboxAdresa->addWidget(txtUlica);

    fraDonatSearchAdresa->setLayout(hboxAdresa);
    m_vboxDonatSearchFlt->addWidget(fraDonatSearchAdresa);
}

void WgDonatMenu2::createDonatSearchLine()
{
    QFrame *fraMjestoLine = new QFrame();
    fraMjestoLine->setContentsMargins(2, 2, 2, 2);
    fraMjestoLine->setFrameShape(QFrame::StyledPanel);
    fraMjestoLine->setFrameShadow(QFrame::Sunken);
    fraMjestoLine->setMinimumHeight(15);
    m_vboxDonatSearchFlt->addWidget(fraMjestoLine);
}

void WgDonatMenu2::createDonatSearchToolbar()
{
    QFrame *fraStrankaSeachToolbar = new QFrame();
    fraStrankaSeachToolbar->setContentsMargins(0, 0, 0, 0);
//    fraStrankaSeachToolbar->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxStrankaSeachToolbar = new QHBoxLayout();
    hboxStrankaSeachToolbar->setContentsMargins(2, 2, 2, 2);
    hboxStrankaSeachToolbar->setSpacing(1);

    m_cboDonatSearch = new QComboBox();
    m_cboDonatSearch->addItem(tr("Naziv :"));
    m_cboDonatSearch->addItem(tr("Telefon :"));
    m_cboDonatSearch->addItem(tr("JMBG-MB :"));
    m_cboDonatSearch->addItem(tr("OIB :"));
    m_cboDonatSearch->addItem(tr("Uloga stranke Id :"));
    m_cboDonatSearch->addItem(tr("Ticket Id :"));
    m_cboDonatSearch->addItem(tr("Asset Id :"));
    m_cboDonatSearch->addItem(tr("Grupna :"));
    m_cboDonatSearch->addItem(tr("Hijerarhija :"));
    m_cboDonatSearch->setCurrentIndex(0);
    QSizePolicy cboDonatSearchSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    cboDonatSearchSizePolicy.setHorizontalStretch(0);
    cboDonatSearchSizePolicy.setVerticalStretch(0);
    m_cboDonatSearch->setSizePolicy(cboDonatSearchSizePolicy);
    hboxStrankaSeachToolbar->addWidget(m_cboDonatSearch);

    m_txtDonatSearch = new QLineEdit();
    QSizePolicy donatSearchSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    donatSearchSizePolicy.setHorizontalStretch(0);
    donatSearchSizePolicy.setVerticalStretch(0);
    m_txtDonatSearch->setSizePolicy(donatSearchSizePolicy);
    hboxStrankaSeachToolbar->addWidget(m_txtDonatSearch);

    m_btnDonatTrazi = new QPushButton(tr("OK"));
    m_btnDonatTrazi->setMaximumWidth(45);
    QSizePolicy btnDonatTraziSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnDonatTraziSizePolicy.setHorizontalStretch(0);
    btnDonatTraziSizePolicy.setVerticalStretch(0);
    m_btnDonatTrazi->setSizePolicy(btnDonatTraziSizePolicy);
    hboxStrankaSeachToolbar->addWidget(m_btnDonatTrazi);

    m_btnDonatKon = new QPushButton(tr("KON"));
    m_btnDonatKon->setMaximumWidth(45);
    QSizePolicy btnDonatKonSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnDonatKonSizePolicy.setHorizontalStretch(0);
    btnDonatKonSizePolicy.setVerticalStretch(0);
    m_btnDonatKon->setSizePolicy(btnDonatKonSizePolicy);
    hboxStrankaSeachToolbar->addWidget(m_btnDonatKon);

    m_btnDonatFiz = new QPushButton(tr("FIZ"));
    m_btnDonatFiz->setMaximumWidth(45);
    QSizePolicy btnDonatFizSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnDonatFizSizePolicy.setHorizontalStretch(0);
    btnDonatFizSizePolicy.setVerticalStretch(0);
    m_btnDonatFiz->setSizePolicy(btnDonatFizSizePolicy);
    hboxStrankaSeachToolbar->addWidget(m_btnDonatFiz);

    m_btnDonatFir = new QPushButton(tr("FIR"));
    m_btnDonatFir->setMaximumWidth(45);
    QSizePolicy btnDonatFirSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnDonatFirSizePolicy.setHorizontalStretch(0);
    btnDonatFirSizePolicy.setVerticalStretch(0);
    m_btnDonatFir->setSizePolicy(btnDonatFirSizePolicy);
    hboxStrankaSeachToolbar->addWidget(m_btnDonatFir);

    fraStrankaSeachToolbar->setLayout(hboxStrankaSeachToolbar);
    m_vboxDonatSearchFlt->addWidget(fraStrankaSeachToolbar);
}

void WgDonatMenu2::creatDonatUlogeStranke()
{
    m_fraDonatUlogeStranke = new QFrame();
    m_fraDonatUlogeStranke->setContentsMargins(0, 0, 0, 0);
    m_vboxDonatUlogeStranke = new QVBoxLayout();
    m_vboxDonatUlogeStranke->setContentsMargins(0, 0, 0, 0);
    m_vboxDonatUlogeStranke->setSpacing(1);

    // [0]
    QFrame *fraUlogeStrankeTitle = new QFrame();
    fraUlogeStrankeTitle->setContentsMargins(0, 0, 0, 0);
    fraUlogeStrankeTitle->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxUlogeStrankeTitle = new QHBoxLayout();
    hboxUlogeStrankeTitle->setContentsMargins(2, 2, 2, 2);
    hboxUlogeStrankeTitle->setSpacing(1);
    QLabel *lblUlogeTitle = new QLabel(tr("Uloge"));
    hboxUlogeStrankeTitle->addWidget(lblUlogeTitle);
    m_lblOsnoveUlogeTitle = new QLabel();
    m_lblOsnoveUlogeTitle->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxUlogeStrankeTitle->addWidget(m_lblOsnoveUlogeTitle);
    fraUlogeStrankeTitle->setLayout(hboxUlogeStrankeTitle);
    m_vboxDonatUlogeStranke->addWidget(fraUlogeStrankeTitle);
    // [1]
    QFrame *fraUlogeStranke = new QFrame();
    fraUlogeStranke->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hboxUlogeStranke = new QHBoxLayout();
    hboxUlogeStranke->setContentsMargins(2, 2, 2, 2);
    hboxUlogeStranke->setSpacing(1);
    m_lstUlogeStranaka = new QListWidget();
//    m_lstUlogeStranaka->setMinimumWidth(200);
    m_lstUlogeStranaka->setMaximumHeight(120);
    QSizePolicy lstUlogeStranakaSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lstUlogeStranakaSizePolicy.setHorizontalStretch(0);
    lstUlogeStranakaSizePolicy.setVerticalStretch(0);
    m_lstUlogeStranaka->setSizePolicy(lstUlogeStranakaSizePolicy);
    m_lstUlogeStranaka->setWrapping(true);
    hboxUlogeStranke->addWidget(m_lstUlogeStranaka);
    // [2]
    QFrame *fraUlogeStrankeToolbar = new QFrame();
    fraUlogeStrankeToolbar->setContentsMargins(0, 0, 0, 0);
    fraUlogeStrankeToolbar->setFrameShape(QFrame::StyledPanel);
//    QSizePolicy fraUlogeStrankeToolbarSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    fraUlogeStrankeToolbarSizePolicy.setHorizontalStretch(0);
//    fraUlogeStrankeToolbarSizePolicy.setVerticalStretch(0);
//    fraUlogeStrankeToolbar->setSizePolicy(fraUlogeStrankeToolbarSizePolicy);
    QVBoxLayout *vboxUlogeStrankeToolBar = new QVBoxLayout();
    vboxUlogeStrankeToolBar->setContentsMargins(2, 2, 2, 2);
    vboxUlogeStrankeToolBar->setSpacing(1);    QPushButton *btnUloge1 = new QPushButton();
    btnUloge1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/UL_1.gif")));
    btnUloge1->setCursor(Qt::PointingHandCursor);
    btnUloge1->setFlat(TRUE);
    btnUloge1->setToolTip(tr("Promjena na postojećoj ulozi"));
    vboxUlogeStrankeToolBar->addWidget(btnUloge1);
    QPushButton *btnUloge2 = new QPushButton();
    btnUloge2->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/UL_2.gif")));
    btnUloge2->setCursor(Qt::PointingHandCursor);
    btnUloge2->setFlat(TRUE);
    btnUloge2->setToolTip(tr("Dostupne uloge"));
    vboxUlogeStrankeToolBar->addWidget(btnUloge2);
    QPushButton *btnUloge3 = new QPushButton();
    btnUloge3->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/UL_3.gif")));
    btnUloge3->setCursor(Qt::PointingHandCursor);
    btnUloge3->setFlat(TRUE);
    btnUloge3->setToolTip(tr("Nova uloga"));
    vboxUlogeStrankeToolBar->addWidget(btnUloge3);
    fraUlogeStrankeToolbar->setLayout(vboxUlogeStrankeToolBar);
    hboxUlogeStranke->addWidget(fraUlogeStrankeToolbar);

    fraUlogeStranke->setLayout(hboxUlogeStranke);
    m_vboxDonatUlogeStranke->addWidget(fraUlogeStranke);

    m_fraDonatUlogeStranke->setLayout(m_vboxDonatUlogeStranke);
}

void WgDonatMenu2::toUpper(const QString &text)
{
    QLineEdit *le = qobject_cast<QLineEdit *>(sender());
    if(!le) return;
    le->setText(text.toUpper());
}

WgDonatMenu2::~WgDonatMenu2()
{
    m_cboDonatSearch->clear();
}

}   // namespace log
