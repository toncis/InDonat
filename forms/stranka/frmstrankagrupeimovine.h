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
