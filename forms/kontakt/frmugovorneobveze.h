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
