#ifndef FRMZLONAMJERNIMOBADD_H
#define FRMZLONAMJERNIMOBADD_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QTime>
#include "donat.h"


namespace Ui {
class FrmZlonamjerniMobAdd;
}

namespace Kontakt {
class FrmZlonamjerniMobAdd : public QDialog
{
    Q_OBJECT

public:
    explicit FrmZlonamjerniMobAdd(QWidget *parent = 0);
    ~FrmZlonamjerniMobAdd();

private:
    Ui::FrmZlonamjerniMobAdd *ui;
};

} // namespace Kontakt

#endif // FRMZLONAMJERNIMOBADD_H
