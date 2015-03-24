#ifndef FRMSTRANKAADRESA_H
#define FRMSTRANKAADRESA_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmStrankaAdresa;
}

namespace Stranka {

class FrmStrankaAdresa : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmStrankaAdresa(const unsigned int iAdresaId = 0, QWidget *parent = 0);
    ~FrmStrankaAdresa();
    
private slots:
    void on_btnPotvrda_clicked();

    void on_treeSifre_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmStrankaAdresa *ui;

    unsigned int m_iAdresaId;
    unsigned int m_iStrankaId;
    int m_iTipAdreseId;
    int m_iStatusId;
    unsigned int m_iMjestoId;
    unsigned int m_iUlicaId;
    unsigned int m_iZupanijaId;
    unsigned int m_iRegijaId;
    unsigned int m_iPostaId;


    void popuniAdresu(const unsigned int iAdressaId = 0);
};

} // Stranka Namespace

#endif // FRMSTRANKAADRESA_H
