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
