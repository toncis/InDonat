//
//  frmstrankagrupeimovine.h
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

#ifndef FRMSTRANKAGRUPEIMOVINE_H
#define FRMSTRANKAGRUPEIMOVINE_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "donat.h"

namespace Ui {
class FrmStrankaGrupeImovine;
}

namespace Stranka {
class FrmStrankaGrupeImovine : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmStrankaGrupeImovine(QWidget *parent = 0);
    ~FrmStrankaGrupeImovine();

    unsigned int SelectedGrupaImovineId;
    string SelectedBrojTelefona;
    
private slots:


    void on_btnPrikazi_clicked();
    void on_btnAktivni_clicked();
    void on_btnSuspend_clicked();
    void on_btnNovi_clicked();
    void on_btnNeaktivni_clicked();

    void on_treeKlase_itemPressed(QTreeWidgetItem *item, int column);
    void on_treeAdrese_itemPressed(QTreeWidgetItem *item, int column);
    void on_treeGrupeImovine_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmStrankaGrupeImovine *ui;

    void popuniKlase();
    void popuniAdrese();
    void popuniGrupeImovine();

    string m_strSelectedKlasa;
    string m_strSelectedMjestoId;
    string m_strSelectedUlicaId;


    // Donat main search mode
    enum GrupaImovineStatus
    {
        GrupaImovineOtkazana = -1,
        GrupaImovineNeaktivna = 0,
        GrupaImovineAktivna = 1,
        GrupaImovineNova = 2,
        GrupaImovineUProcesuUkljucenja = 3,
        GrupaImovineUProcesuIskljucenja = 4,
        GrupaImovineSuspendiranNaZahtjevKorisnika = 5,
        GrupaImovineSuspendiranZbogNeplacanja = 6,
        GrupaImovineSuspendiranRadiDugaUObaSmjera = 7,
        GrupaImovineSuspendiranNaZahtjevIZbogNeplacanja = 8,
        GrupaImovineIskljucenNaZahtjevIZbogNeplacanja = 9,
        GrupaImovineUProcesuPromjene = 10,
        GrupaImovineSuspendiranPrijenosNaPrivPretplatnika = 11
    };

    GrupaImovineStatus m_GrupaImovineStatus;

};

} //Stranka

#endif // FRMSTRANKAGRUPEIMOVINE_H
