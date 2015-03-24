#ifndef FRMPREGLEDSPORAZUMA_H
#define FRMPREGLEDSPORAZUMA_H

#include <QDialog>
#include "donat.h"

namespace Ui {
    class FrmPregledSporazuma;
}

namespace Sporazumi {

class FrmPregledSporazuma : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPregledSporazuma(QWidget *parent = 0);
    explicit FrmPregledSporazuma(unsigned int iSporazumId, QWidget *parent = 0);
    explicit FrmPregledSporazuma(string strBrojDokumenta, QWidget *parent = 0);
    ~FrmPregledSporazuma();

private slots:
    void on_m_btnZatvori_clicked();

    void on_m_btnTrazi_clicked();

private:
    Ui::FrmPregledSporazuma *ui;

    string m_strBrojDokumenta;
    unsigned int m_iSporazumId;

    class RowStavkaSporazuma {
        public :
            unsigned int StavkaSporazumaId;
            string Naziv;
            double Kolicina;
            double Iznos1;
            double Iznos2;
    };

    void clearFormData();
    void getSporazum(unsigned int iSporazumId);
    void getSporazum(string strSporazumId);
    void getSporazumStavke(unsigned int iSporazumId);
    void getStanjeUgovora(unsigned int iSporazumId);
    void getStanjeObavijesti(unsigned int iSporazumId);
};


}   // namespace sporazumi

#endif // FRMPREGLEDSPORAZUMA_H
