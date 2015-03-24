#ifndef FRMPRIGOVORADD_H
#define FRMPRIGOVORADD_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"


namespace Ui {
class FrmPrigovorAdd;
}

namespace Kontakt {
class FrmPrigovorAdd : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorAdd(QWidget *parent = 0);
    ~FrmPrigovorAdd();

private:
    Ui::FrmPrigovorAdd *ui;
};

} // namespace Kontakt

#endif // FRMPRIGOVORADD_H
