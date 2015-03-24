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
