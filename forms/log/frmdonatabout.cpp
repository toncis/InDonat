/************************************* Module Header **************************************\
* Module Name:  frmdonatabout.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT about form.
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

#include "frmdonatabout.h"

namespace Log {

FrmDonatAbout::FrmDonatAbout()
{
    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("O DONAT-u"));

    createFrame3();
    createFrame2();
    createFrame1();

    // Donat logo image
    m_imgDonat = new QLabel();
//  m_ImgDonat->setObjectName(QString::fromUtf8("m_ImgDonat"));
//  m_ImgDonat->setGeometry(QRect(1, 1, 541, 311));
    m_imgDonat->setPixmap(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/AboutDonat.png")));

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(m_imgDonat);
    mainLayout->addWidget(m_frame1);
    setLayout(mainLayout);
}

void FrmDonatAbout::createFrame1()
{
    m_frame1 = new QFrame();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_frame2);
    layout->addWidget(m_frame3);
    m_frame1->setLayout(layout);
}

void FrmDonatAbout::createFrame2()
{
    // Donat application information
    m_frame2 = new QFrame();
    QVBoxLayout *layout = new QVBoxLayout();
    m_lblApplicationTitle = new QLabel(QCoreApplication::instance()->applicationName());
    m_lblApplicationTitle->setAlignment(Qt::AlignHCenter);
    m_lblApplicationVersion = new QLabel(tr("Version : %1").arg(QCoreApplication::instance()->applicationVersion()));
    m_lblApplicationVersion->setAlignment(Qt::AlignHCenter);
    m_lblApplicationCopyright = new QLabel(tr("Copyright2005 Hrvatski telekom. All rights reserved."));
    m_lblApplicationCopyright->setAlignment(Qt::AlignHCenter);
    m_lblApplicationDesc = new QLabel(tr("Customer Administration and Order Management"));
    m_lblApplicationDesc->setAlignment(Qt::AlignHCenter);
    m_lblApplicationFolder = new QLabel(QCoreApplication::instance()->applicationFilePath());
    m_lblApplicationFolder->setAlignment(Qt::AlignHCenter);
    layout->addWidget(m_lblApplicationTitle);
    layout->addWidget(m_lblApplicationVersion);
    layout->addWidget(m_lblApplicationCopyright);
    layout->addWidget(m_lblApplicationDesc);
    layout->addWidget(m_lblApplicationFolder);
    m_frame2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_frame2->setLayout(layout);
}

void FrmDonatAbout::createFrame3()
{
    // Donat about dialog box buttons
    m_frame3 = new QFrame();
    m_dboxButton = new QDialogButtonBox(QDialogButtonBox::Ok);
    m_dboxButton->setCenterButtons(true);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_dboxButton);
    m_frame3->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
    m_frame3->setLayout(layout);

    // OK button
    connect(m_dboxButton, SIGNAL(accepted()), this, SLOT(accept()));
    // Cancel button
//    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

FrmDonatAbout::~FrmDonatAbout()
{
    m_imgDonat->clear();
}

}   // namespace log
