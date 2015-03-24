#ifndef FRMMDM3_H
#define FRMMDM3_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmMdm3;
}

namespace Stranka {

class FrmMdm3 : public QDialog
{
    Q_OBJECT

public:
    explicit FrmMdm3(QWidget *parent = 0);
    ~FrmMdm3();

private:
    Ui::FrmMdm3 *ui;
};

} // Stranka Namespace

#endif // FRMMDM3_H
