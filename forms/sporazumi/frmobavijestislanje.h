#ifndef FRMOBAVIJESTISLANJE_H
#define FRMOBAVIJESTISLANJE_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class FrmObavijestiSlanje;
}

namespace Sporazumi {

class FrmObavijestiSlanje : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmObavijestiSlanje(QWidget *parent = 0);
    ~FrmObavijestiSlanje();
    
private:
    Ui::FrmObavijestiSlanje *ui;

    QIcon m_iconCickled;

};

}

#endif // FRMOBAVIJESTISLANJE_H
