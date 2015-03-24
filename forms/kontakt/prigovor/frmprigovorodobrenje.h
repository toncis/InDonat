#ifndef FRMPRIGOVORODOBRENJE_H
#define FRMPRIGOVORODOBRENJE_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmPrigovorOdobrenje;
}

namespace Kontakt {
class FrmPrigovorOdobrenje : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorOdobrenje(QWidget *parent = 0);
    ~FrmPrigovorOdobrenje();

private:
    Ui::FrmPrigovorOdobrenje *ui;
};

}

#endif // FRMPRIGOVORODOBRENJE_H
