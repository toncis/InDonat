//
//  frmkontaktnicentarpretraga.cpp
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

#include "frmkontaktnicentarpretraga.h"
#include "ui_frmkontaktnicentarpretraga.h"

namespace Kontakt {

// [Class Constructor]
FrmKontaktniCentarPretraga::FrmKontaktniCentarPretraga(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKontaktniCentarPretraga)
{
    ui->setupUi(this);

    ui->treeStranke->setColumnWidth(0, 240);
    ui->treeStranke->hideColumn(1);
    ui->treeStranke->hideColumn(2);
    ui->treeStranke->hideColumn(3);
    ui->treeStranke->hideColumn(4);
    ui->treeStranke->hideColumn(5);
}

FrmKontaktniCentarPretraga::~FrmKontaktniCentarPretraga()
{
    delete ui;
}

// [Private member Functions]
void FrmKontaktniCentarPretraga::traziDonatKorisnikaPoNazivu()
{
}

// [Event Hnadlers]
void FrmKontaktniCentarPretraga::on_btnSearchByName_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByPhone_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByJmbg_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByOib_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByUlogaStrankeId_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByGrupaImovineId_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByTicketId_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnFilterByCity_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnFilterByStreet_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnTrazi_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnPreuzmiStranku_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnPreuzmiTelefon_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnFizickaOsoba_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnPravnaOsoba_clicked()
{

}

}


