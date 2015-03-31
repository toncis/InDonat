//
//  frmkontaktdokumenti1.h
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

#ifndef FRMKONTAKTDOKUMENTI1_H
#define FRMKONTAKTDOKUMENTI1_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"


namespace Ui {
class FrmKontaktDokumenti1;
}

namespace Kontakt {
class FrmKontaktDokumenti1 : public QDialog
{
    Q_OBJECT

public:
    explicit FrmKontaktDokumenti1(QWidget *parent = 0);
    explicit FrmKontaktDokumenti1(unsigned int iKontaktId, QWidget *parent = 0);
    explicit FrmKontaktDokumenti1(
            unsigned int iKupacId,
            unsigned int iKontaktId,
            unsigned int iKontaktStavkaId,
            int iItemId,
            int iTaskId,
            string strAktivniPrikaz,
            QWidget *parent = 0);
    ~FrmKontaktDokumenti1();

private slots:
    void on_btnPotvrdaOpisa_clicked();

    void on_btnNoviDokument_clicked();

    void on_btnOtvoriDokument_clicked();

    void on_btnUkloniDokument_clicked();

    void on_btnDokumentZaporka_clicked();

    void on_btnKorisnikDokument_clicked();

    void on_btnExcell_clicked();

    void on_btnWord_clicked();

    void on_btnDokumentEmail_clicked();

    void on_treeDokumenti_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmKontaktDokumenti1 *ui;

    QIcon m_iconLozinka;
    QIcon m_iconUser;
    QIcon m_iconTransparent;

    unsigned int m_iKupacId;
    unsigned int m_iKonatktId;
    unsigned int m_iKontaktStavkaId;
    int m_iItemId;
    int m_iTaskId;

    unsigned int m_iFileNo;
    string m_strFileName;
    string m_strFileDescription;
    int m_iFileSize;


    unsigned int GetKontaktKupacId(const unsigned int iKonaktId);
    unsigned int GetKontaktPlanIdSeq();

    void initForm();
    void popuniKupca();
    void popuniKontaktDokumente();
    void popuniKupacDokumente();
    void popuniOpisDokumenta();



};

}

#endif // FRMKONTAKTDOKUMENTI1_H
