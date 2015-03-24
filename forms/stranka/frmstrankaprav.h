#ifndef FRMSTRANKAPRAV_H
#define FRMSTRANKAPRAV_H

#include <QDialog>
#include "donat.h"

namespace Ui {
    class FrmStrankaPrav;
}

namespace Stranka {

class FrmStrankaPrav : public QDialog
{
    Q_OBJECT

public:
    explicit FrmStrankaPrav(QWidget *parent = 0);
    explicit FrmStrankaPrav(unsigned int iStrankaId, QWidget *parent = 0);
    ~FrmStrankaPrav();

private:
    Ui::FrmStrankaPrav *ui;

    unsigned int m_iStrankaId;

};

} //Stranka

#endif // FRMSTRANKAPRAV_H
