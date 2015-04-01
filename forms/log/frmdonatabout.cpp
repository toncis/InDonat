//
//  frmdonatabout.cpp
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
