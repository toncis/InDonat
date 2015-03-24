#ifndef FRMPRIGOVORPISMOPOTVRDE_H
#define FRMPRIGOVORPISMOPOTVRDE_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmPrigovorPismoPotvrde;
}

namespace Kontakt {
class FrmPrigovorPismoPotvrde : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorPismoPotvrde(QWidget *parent = 0);
    ~FrmPrigovorPismoPotvrde();

private:
    Ui::FrmPrigovorPismoPotvrde *ui;
};

}

#endif // FRMPRIGOVORPISMOPOTVRDE_H
