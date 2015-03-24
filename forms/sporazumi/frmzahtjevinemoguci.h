#ifndef FRMZAHTJEVINEMOGUCI_H
#define FRMZAHTJEVINEMOGUCI_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class FrmZahtjeviNemoguci;
}

namespace Sporazumi {

class FrmZahtjeviNemoguci : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmZahtjeviNemoguci(QWidget *parent = 0);
    ~FrmZahtjeviNemoguci();
    
private:
    Ui::FrmZahtjeviNemoguci *ui;


    QIcon m_iconCickled;

};

}

#endif // FRMZAHTJEVINEMOGUCI_H
