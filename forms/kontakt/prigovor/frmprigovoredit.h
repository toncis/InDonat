#ifndef FRMPRIGOVOREDIT_H
#define FRMPRIGOVOREDIT_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmPrigovorEdit;
}

namespace Kontakt {

class FrmPrigovorEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorEdit(QWidget *parent = 0);
    ~FrmPrigovorEdit();

private:
    Ui::FrmPrigovorEdit *ui;
};

}
#endif // FRMPRIGOVOREDIT_H
