//
//  frmpregledimovine.cpp
//
//  Author:
//       Tonči Sviličić <tonci.svilicic@in2.hr>
//
//  Copyright (c) 2015 Tonči Sviličić
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

#include "frmpregledn.h"
#include "ui_frmpregledn.h"

#include "itos.h"

#include "forms/kontakt/frmkanalprodajekorisnik.h"


namespace Sporazumi {

// [Class Constructor]
FrmPregledN::FrmPregledN(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPregledN)
{
    ui->setupUi(this);

    ui->fraStavke->setVisible(false);
}

FrmPregledN::~FrmPregledN()
{
    delete ui;
}

// [Private Member Functions]


// [Event Handlers]
void FrmPregledN::on_btnPregledAktivnosti_clicked()
{

}
void FrmPregledN::on_btnPromjenaKanalaProdaje_clicked()
{
    // Show Donat form for user sales channel change
    Kontakt::FrmKanalProdajeKorisnik *frmKanalProdajeKorisnik = new Kontakt::FrmKanalProdajeKorisnik(this);
    frmKanalProdajeKorisnik->exec();
    delete frmKanalProdajeKorisnik;

    ui->btnKorisnikKanal->setText(QString::fromStdString(g_UNIO_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_KORISNIK_NAZ));
}


} // namespace sporazumi


