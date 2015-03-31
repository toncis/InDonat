//
//  frmpregledimovine.h
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

#ifndef FRMPREGLEDIMOVINE_H
#define FRMPREGLEDIMOVINE_H

#include <QDialog>
#include "donat.h"

namespace Ui {
    class FrmPregledImovine;
}

namespace Sporazumi {

class FrmPregledImovine : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPregledImovine(unsigned int iGrupaImovineId, QWidget *parent = 0);
    ~FrmPregledImovine();

private:
    Ui::FrmPregledImovine *ui;

    unsigned int m_iGrupaImovineId;

    void fillImovina(unsigned int iGrupaImovineId);
};


} // namespace sporazumi

#endif // FRMPREGLEDIMOVINE_H
