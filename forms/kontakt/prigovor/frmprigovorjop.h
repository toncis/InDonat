//
//  frmprigovorjop.h
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

#ifndef FRMPRIGOVORJOP_H
#define FRMPRIGOVORJOP_H

#include <QDialog>
#include "donat.h"

namespace Ui {
class FrmPrigovorJop;
}

namespace Kontakt {
class FrmPrigovorJop : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorJop(QWidget *parent = 0);
    ~FrmPrigovorJop();

private slots:
    void on_btnPotvrda_clicked();

private:
    Ui::FrmPrigovorJop *ui;
};

}
#endif // FRMPRIGOVORJOP_H
