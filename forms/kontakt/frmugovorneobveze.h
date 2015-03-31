//
//  frmugovorneobveze.h
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

#ifndef FRMUGOVORNEOBVEZE_H
#define FRMUGOVORNEOBVEZE_H

#include <QDialog>
#include "donat.h"

namespace Ui {
    class FrmUgovorneObveze;
}

namespace Kontakt {

class FrmUgovorneObveze : public QDialog
{
    Q_OBJECT

public:
    explicit FrmUgovorneObveze(
        unsigned int iKupacId,
        unsigned int iGrupaImovineId = 0,
        QWidget *parent = 0);

    ~FrmUgovorneObveze();

private slots:
    void on_btnZatvori_clicked();
    void on_btnSveUgovorneObvezeKupca_clicked();
    void on_btnTelefon_clicked();
    void on_btnIspis_clicked();

private:
    Ui::FrmUgovorneObveze *ui;

    unsigned int m_iKupacId;
    unsigned int m_iGrupaImovineId;

    class RowV_GIM_STRUKTURA_SVE {
        public :
            string Tip;
            unsigned int Asset;
            unsigned int GimovineId;
            string TelBroj;
            string Klasa;
    };

    class RowB_HIJERARHIJA {
    public :
        unsigned int KupacId;
        unsigned int ImovinaId;
        int TelPOz;
        int TelBr;
        string TelBroj;
        string TelLinId;
        int SlogStatus;
        unsigned int GrupaImovineId;
        int B1;
        int B2;
        string DatumOd;
        string DatumDo;
    };

    void popuniKupca(unsigned int iKupacId);
    void prikazUgovorneObvezeZaKupca(unsigned int iKupacId);
    void prikazUgovorneObvezeZaGrupuImovine(unsigned int iGrupaImovineId);

};

} // Kontakt

#endif // FRMUGOVORNEOBVEZE_H
