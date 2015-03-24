#ifndef FRMPRIGOVORPISANORJESENJE_H
#define FRMPRIGOVORPISANORJESENJE_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmPrigovorPisanoRjesenje;
}

namespace Kontakt {

class FrmPrigovorPisanoRjesenje : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorPisanoRjesenje(QWidget *parent = 0);
    ~FrmPrigovorPisanoRjesenje();

private:
    Ui::FrmPrigovorPisanoRjesenje *ui;
};


}
#endif // FRMPRIGOVORPISANORJESENJE_H
