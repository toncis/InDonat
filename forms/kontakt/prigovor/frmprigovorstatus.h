#ifndef FRMPRIGOVORSTATUS_H
#define FRMPRIGOVORSTATUS_H

#include <QDialog>
#include "donat.h"

namespace Ui {
class FrmPrigovorStatus;
}

namespace Kontakt {

class FrmPrigovorStatus : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorStatus(QWidget *parent = 0);
    ~FrmPrigovorStatus();

private slots:
    void on_btnPotvrda_clicked();

private:
    Ui::FrmPrigovorStatus *ui;
};

}
#endif // FRMPRIGOVORSTATUS_H
