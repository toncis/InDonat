#ifndef FRMMDM2_H
#define FRMMDM2_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"
namespace Ui {
class FrmMdm2;
}

namespace Stranka {

class FrmMdm2 : public QDialog
{
    Q_OBJECT

public:
    explicit FrmMdm2(QWidget *parent = 0);
    ~FrmMdm2();

private:
    Ui::FrmMdm2 *ui;
};

} // Stranka Namespace

#endif // FRMMDM2_H
