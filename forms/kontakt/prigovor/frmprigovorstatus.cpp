//
//  frmprigovorstatus.cpp
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


#include "frmprigovorstatus.h"
#include "ui_frmprigovorstatus.h"

namespace Kontakt {

// [Class Constuctor]
FrmPrigovorStatus::FrmPrigovorStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorStatus)
{
    ui->setupUi(this);
}

FrmPrigovorStatus::~FrmPrigovorStatus()
{
    delete ui;
}

// [Event Handlers]

}

void Kontakt::FrmPrigovorStatus::on_btnPotvrda_clicked()
{

}
