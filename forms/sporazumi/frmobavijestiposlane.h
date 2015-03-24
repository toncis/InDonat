#ifndef FRMOBAVIJESTIPOSLANE_H
#define FRMOBAVIJESTIPOSLANE_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class FrmObavijestiPoslane;
}

namespace Sporazumi {

class FrmObavijestiPoslane : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmObavijestiPoslane(QWidget *parent = 0);
    ~FrmObavijestiPoslane();
    
private slots:
    void on_btnKanalProdaje_clicked();

private:
    Ui::FrmObavijestiPoslane *ui;

    QIcon m_iconCickled;

    // [Private Member Functions]
    void initFormView();

};


}

#endif // FRMOBAVIJESTIPOSLANE_H
