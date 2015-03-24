#ifndef FRMZLONAMJERNIADD_H
#define FRMZLONAMJERNIADD_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QTime>
#include "donat.h"

namespace Ui {
class FrmZlonamjerniAdd;
}

namespace Kontakt {
class FrmZlonamjerniAdd : public QDialog
{
    Q_OBJECT

public:
    explicit FrmZlonamjerniAdd(QWidget *parent = 0);
    ~FrmZlonamjerniAdd();

private:
    Ui::FrmZlonamjerniAdd *ui;
};

} // namespace Kontakt

#endif // FRMZLONAMJERNIADD_H
