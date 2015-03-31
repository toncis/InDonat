//
//  frmzlonamjernipregled.h
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

#ifndef FRMZLONAMJERNIPREGLED_H
#define FRMZLONAMJERNIPREGLED_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QTableWidget>
#include <QTime>
#include "donat.h"


namespace Ui {
class FrmZlonamjerniPregled;
}

namespace Kontakt {
class FrmZlonamjerniPregled : public QDialog
{
    Q_OBJECT

public:
    explicit FrmZlonamjerniPregled(QWidget *parent = 0);
    ~FrmZlonamjerniPregled();

private slots:
    void on_btnSvi_clicked();

    void on_btnOtvoreni_clicked();

    void on_btnAnaliza_clicked();

    void on_btnPoslanoPoliciji_clicked();

    void on_btnObavijest_2_clicked();

    void on_btnOdustao_clicked();

    void on_btnPodnesak_clicked();

    void on_btnObavijest_clicked();

    void on_btnExcel_clicked();

    void on_btnOtvorenDatumOK_clicked();

    void on_btnAnalizaDatumOK_clicked();

    void on_btnPUpravaDatumOK_clicked();

    void on_btnObavijestDatumOK_clicked();

    void on_btnOdustaoDatumOK_clicked();

    void on_btnDokumentiOK_clicked();

    void on_btnNapomenaOK_clicked();

    void on_grdPrigovori_itemPressed(QTableWidgetItem *item);

private:
    Ui::FrmZlonamjerniPregled *ui;

    int m_iZlonamjerniStatusId;
    unsigned int m_iZlonamjerniPozivId;

    void initForm();
    void clearFormData();
    void popuniZlonamjernePozive();
    void popuniZlonamjerniPoziv(unsigned int iZlonamjerniPozivId);

};

} // namespace Kontakt

#endif // FRMZLONAMJERNIPREGLED_H
