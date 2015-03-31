//
//  frmstrankaadresa.h
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

#ifndef FRMSTRANKAADRESA_H
#define FRMSTRANKAADRESA_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmStrankaAdresa;
}

namespace Stranka {

class FrmStrankaAdresa : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmStrankaAdresa(const unsigned int iAdresaId = 0, QWidget *parent = 0);
    ~FrmStrankaAdresa();
    
private slots:
    void on_btnPotvrda_clicked();

    void on_treeSifre_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmStrankaAdresa *ui;

    unsigned int m_iAdresaId;
    unsigned int m_iStrankaId;
    int m_iTipAdreseId;
    int m_iStatusId;
    unsigned int m_iMjestoId;
    unsigned int m_iUlicaId;
    unsigned int m_iZupanijaId;
    unsigned int m_iRegijaId;
    unsigned int m_iPostaId;


    void popuniAdresu(const unsigned int iAdressaId = 0);
};

} // Stranka Namespace

#endif // FRMSTRANKAADRESA_H
