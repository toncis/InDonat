//
//  frmsuspenzija.cpp
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

#include "frmsuspenzija.h"
#include "ui_frmsuspenzija.h"

#include "itos.h"

namespace Sporazumi {

// [ Class Constructor ]
FrmSuspenzija::FrmSuspenzija(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSuspenzija)
{
    ui->setupUi(this);
}

FrmSuspenzija::~FrmSuspenzija()
{
    delete ui;
}

// [ Private Member Functions ]
void FrmSuspenzija::initForm()
{
    ui->btnSuspenzija->setEnabled(false);
    ui->btnResuspenzija->setEnabled(false);

    ui->lblStatusBarText2->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));
}


// [ Event Handlers ]
void FrmSuspenzija::on_btnTrazi_clicked()
{

}

void FrmSuspenzija::on_btnTelefon_clicked()
{
    ui->lblFilterEditTitle->setText(tr("TELEFON"));
    ui->txtFilterValue->setFocus();
    m_SearchMode = TraziPoTelefonu;
}

void FrmSuspenzija::on_btnAsset_clicked()
{
    ui->lblFilterEditTitle->setText(tr("ASSET"));
    ui->txtFilterValue->setFocus();
    m_SearchMode = TraziPoAssetId;
}

void FrmSuspenzija::on_btnKupac_clicked()
{
    ui->lblFilterEditTitle->setText(tr("KUPAC"));
    ui->txtFilterValue->setFocus();
    m_SearchMode = TraziPoKupacId;
}

void FrmSuspenzija::on_btnBillingAccount_clicked()
{
    ui->lblFilterEditTitle->setText(tr("RAČUN"));
    ui->txtFilterValue->setFocus();
    m_SearchMode = TraziPoRacunId;
}

void FrmSuspenzija::on_btnSuspenzija_clicked()
{

}

void FrmSuspenzija::on_btnResuspenzija_clicked()
{

}

void FrmSuspenzija::on_btnPotvrda_clicked()
{

}

void FrmSuspenzija::on_btnZatvori_clicked()
{

}

void FrmSuspenzija::on_btnIspisliste_clicked()
{

}

void FrmSuspenzija::on_btnUkloniListu_clicked()
{

}

void FrmSuspenzija::on_btnUkloniStavku_clicked()
{

}

void FrmSuspenzija::on_btnUkloniPlacanje_clicked()
{

}

void FrmSuspenzija::on_pushButton_clicked()
{

}

void FrmSuspenzija::on_treeWidget_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{

}

void FrmSuspenzija::on_treeWidget_2_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{

}

} // namespace sporazumi
