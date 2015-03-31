//
//  frmgrupaimovineatributi.h
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

#ifndef FRMGRUPAIMOVINEATRIBUTI_H
#define FRMGRUPAIMOVINEATRIBUTI_H

#include <QDialog>
#include <QTreeWidget>

#include "donat.h"

namespace Ui {
class FrmGrupaImovineAtributi;
}

namespace Sporazumi {

class FrmGrupaImovineAtributi : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmGrupaImovineAtributi(unsigned int iGrupaImovineId, long long iKupacId, QWidget *parent = 0);
    explicit FrmGrupaImovineAtributi(unsigned int iGrupaImovineId, unsigned int iImovinaId, QWidget *parent = 0);
    explicit FrmGrupaImovineAtributi(unsigned int iGrupaImovineId, QWidget *parent = 0);
    ~FrmGrupaImovineAtributi();
    
private slots:

    void on_btnPotvrda_clicked();
    void on_treeImovina_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeListaVrijesnostiAtributa_itemClicked(QTreeWidgetItem *itemVrijednostAtributa, int column);

private:
    Ui::FrmGrupaImovineAtributi *ui;

    long long m_iKupacId;
    unsigned int m_iGrupaImovineId;
    unsigned int m_iImovinaId;
    int m_iTipVrsteAtributaId;

    unsigned int m_iStavkaId;
    string m_strNazivStavke;

    void popuniGrupeImovine();
    void popuniSveImovine();
    void popuniImovinaAtribute(QTreeWidgetItem *itemImovina);
    void popuniDozvoljeneVrijednostiAtributa();

};

} // Sporazumi

#endif // FRMGRUPAIMOVINEATRIBUTI_H
