#ifndef FRMKONTAKTNICENTARUSER_H
#define FRMKONTAKTNICENTARUSER_H

#include <QDialog>
#include <QTableWidget>
#include "donat.h"

namespace Ui {
class FrmKontaktniCentarUser;
}

namespace Kontakt {

class FrmKontaktniCentarUser : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmKontaktniCentarUser(QWidget *parent = 0, int iTipRole = 0);
    ~FrmKontaktniCentarUser();
    
private slots:
    void on_btnPotvrda_clicked();

    void on_grdKorisnickeGrupe_itemClicked(QTableWidgetItem *item);

private:
    Ui::FrmKontaktniCentarUser *ui;

    int m_iTipRole;
    int m_iRolaTip;
    int m_iGrupaId;
    string m_strGrupaNaziv;

    void popuniGrupe();
};

} // Kontakt

#endif // FRMKONTAKTNICENTARUSER_H
